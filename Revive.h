#pragma once
#include <vector>
#include "Participant.h"
#include "TransactionChannel.h"
using namespace std;
using namespace oc;

class Revive
{
private:
    vector<Participant> pars;
    vector<TransactionChannel> channels;

public:
    Revive();

    vector<Participant> getParticipants() { return pars; }

    void initialize();

    void rebalance();

    bool sendRequest();


    void print()
    {
        double unbalance = 0;
        for (TransactionChannel x : channels)
        {
            x.print();
            unbalance+=abs((x.get_u_bal()-x.get_v_bal())/(x.get_u_bal()+x.get_v_bal()));
        }
        cout<<"avg of unbalance rate : "<< unbalance/channels.size()<<endl;
    }
    int genLeader();
};
