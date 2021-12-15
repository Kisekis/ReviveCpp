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
    unordered_set<int> allSenders;

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

    //if this participant is a leader, call this method to connect to others
    void connect()
    {
        Session server(*ios, ip + ':' + to_string(this->port), SessionMode::Server);
        channel = server.addChannel();
    }

    //if this participant is not a leader, call this method to connect to leader
    void connectTo(int port)
    {
        Session client(*ios, ip + ':' + to_string(port), SessionMode::Client);
        channel = client.addChannel();
    }

    //if this participant is not a leader, call this method to send all balance to leader.
    void sendRequest();

    //if this participant is a leader, call this method to receive balance from other participants.
    void recvRequest();

    vector<TransactionChannel>* generateTransactionChannels();

    int getPort() { return port; }

    int getRecvCount() { return recvCount; }

    //call rebalanceCore method, compute rebalance time
    void rebalance();

    //solve linear programming
    static vector<TransactionChannel>& rebalanceCore(vector<TransactionChannel> &channels,int m);

    //print channels, including balance of both sides and avg of unbalanced rate.
    static void print(vector<TransactionChannel> channels);
};