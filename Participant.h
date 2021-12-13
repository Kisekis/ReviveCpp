#pragma once
#include <cryptoTools/Common/config.h>
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Network/Session.h>
#include <cryptoTools/Network/IOService.h>
#include "glpk.h"
#include "TransactionChannel.h"
#include <map>
using namespace std;
using namespace oc;
class Participant
{
private:
    string name;
    int index;
    bool isLeader;
    string ip = string("127.0.0.1");
    int port;
    IOService *ios;
    Channel channel;
    int recvCount{0};
    map<pair<int,int>,double> paymentChannel;

public:
    Participant(string _name, int _index, int _port, IOService *_ios)
        : name(_name), index(_index), isLeader(false), port(_port), ios(_ios){};

    string getName() { return name; };

    int getIndex() { return index; };

    bool getIsLeader() { return isLeader; };
    void setLeader() { isLeader = !isLeader; };

    void addPaymentChannel(pair<pair<int,int>,double> c) {
        this->paymentChannel.insert(pair<pair<int,int>,double>({c.first.first,c.first.second},c.second));
    }

    void connect()
    {
        Session server(*ios, ip + ':' + to_string(this->port), SessionMode::Server);
        channel = server.addChannel();
    }

    void connectTo(int port)
    {
        Session client(*ios, ip + ':' + to_string(port), SessionMode::Client);
        channel = client.addChannel();
    }
    void sendRequest()
    {
        vector<int> p;
        if(paymentChannel.size()>0) {
            p.push_back(paymentChannel.begin()->first.first);
            for(auto tc : paymentChannel) {
                p.push_back(tc.first.second);
                p.push_back(tc.second);
            }
            channel.send(p);
            channel.close();
        }

    }
    void recvRequest()
    {
        vector<int> p;
        channel.recv(p);
        if(p.size()>0) {
            int sender = p[0];
            for(int i = 1;i<p.size()-1;i=i+2) {
                paymentChannel.insert(pair<pair<int,int>,double>({sender,p[i]},p[i+1]));
            }
        }
        recvCount++;
        channel.close();
    }
    vector<TransactionChannel>* generateTransactionChannels() {
        vector<TransactionChannel>* v = new vector<TransactionChannel>();
        while(!paymentChannel.empty()) {
            auto a = paymentChannel.begin();
            auto b = paymentChannel.find(pair<int,int>(a->first.second,a->first.first));
            if(b!=paymentChannel.end()) {
                TransactionChannel p(a->first.first,a->first.second,a->second,b->second);
                v->push_back(p);
                paymentChannel.erase(b);
            }
            paymentChannel.erase(a);
        }
        return v;
    }
    int getPort() { return port; }
    int getRecvCount() { return recvCount; }
};