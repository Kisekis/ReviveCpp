#include <iostream>
#include "Revive.h"
#define THRESHOLD (float)1 / 2
using namespace osuCrypto;

const pair<pair<int,int>, double> graph[] = {
        {{0,1},100},
        {{0,2},0},
        {{0,2},0},
        {{1,0},0},
        {{1,2},100},
        {{2,3},100},
        {{2,1},20},
        {{3,0},100},
        {{3,2},0},
        {{0,3},40},

};


Revive::Revive()
{
    start();
}

void Revive::start() {
    IOService ios(4);
    //createParticipants
    for(auto tc : graph) {
        int index = tc.first.first;
        if(pars.size()<index+1) {
            Participant p("p"+to_string(index),index,1213+index,&ios);
            pars.push_back(p);
        }
        pars[index].addPaymentChannel(tc);
    }
    sendRequest();
}

int Revive::genLeader()
{
    for (Participant p : pars)
    {
        if (p.getIsLeader())
        {
            p.setLeader();
            int next = (p.getIndex() + 1) % pars.size();
            pars[next].setLeader();
            return next;
        }
    }
    pars[0].setLeader();
    return 0;
}

bool Revive::sendRequest()
{
    int leaderIndex = genLeader();
    int leaderPort = pars[leaderIndex].getPort();
    Participant leader = pars[leaderIndex];
    for (Participant p : pars)
    {
        if (!p.getIsLeader())
        {
            leader.connect();
            p.connectTo(leaderPort);
            p.sendRequest();
            leader.recvRequest();
        }
    }
    if ((float)leader.getRecvCount() / pars.size() < THRESHOLD)
    {
        return false;
    }

    leader.rebalance();
    return true;
}

int main()
{
    Revive simu;
}
