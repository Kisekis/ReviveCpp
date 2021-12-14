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

public:
    Revive();

    void start();

    bool sendRequest();

    int genLeader();
};
