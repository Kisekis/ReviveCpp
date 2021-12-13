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

    void rebalance();

    bool sendRequest();

    void print()
    {
        for (TransactionChannel x : channels)
        {
            x.print();
        }
    }
    int genLeader();
};
