#pragma once
#include <cryptoTools/Common/config.h>
#include <cryptoTools/Common/Defines.h>
#include <cryptoTools/Network/Channel.h>
#include <cryptoTools/Network/Session.h>
#include <cryptoTools/Network/IOService.h>
#include "glpk.h"
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

public:
    Participant(string _name, int _index, int _port, IOService *_ios)
        : name(_name), index(_index), isLeader(false), port(_port), ios(_ios){};

    string getName() { return name; };

    int getIndex() { return index; };

    bool getIsLeader() { return isLeader; };
    void setLeader() { isLeader = !isLeader; };

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
        channel.send(string("request"));
        channel.close();
    }
    void recvRequest()
    {
        string msg;
        channel.recv(msg);
        cout << msg << endl;
        if (msg == "request")
        {
            recvCount++;
        }
        channel.close();
    }
    int getPort() { return port; }
    int getRecvCount() { return recvCount; }
};