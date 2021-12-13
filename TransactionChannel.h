#pragma once
#include "Participant.h"
#include <vector>
using namespace std;
class TransactionChannel
{
private:
    vector<int> p;
    double u_bal;
    double v_bal;

    double Delta_u_v;
    double Delta_v_u;

    double delta = 0;

    bool Agreed = false;

public:
    TransactionChannel(int u, int v, double u_bal, double v_bal)
        : p(vector<int>({u, v}))
    {
        this->u_bal = u_bal;
        this->v_bal = v_bal;
        this->Delta_u_v = 0.5 * (u_bal + v_bal) - u_bal;
        this->Delta_v_u = 0.5 * (u_bal + v_bal) - v_bal;

        if (Delta_u_v * Delta_v_u < 0)
        {

            Agreed = true;
            if (Delta_u_v < 0)
            {
                reverse(p.begin(), p.end());
                double temp = Delta_u_v;
                Delta_u_v = Delta_v_u;
                Delta_v_u = temp;

                temp = this->u_bal;
                this->u_bal = this->v_bal;
                this->v_bal = temp;
            }
        }
        else
        {
            Delta_u_v = 0;
            Delta_v_u = 0;
        }
    };

    bool isAgreed()
    {
        return this->Agreed;
    }

    void print()
    {
        cout << 'p'+to_string(p[0]) << " : " << u_bal << " " << 'p'+to_string(p[1]) << " : " << v_bal << endl;
    }

    void setdelta(double delta)
    {
        this->delta = delta;
    }
    void update()
    {
        u_bal += delta;
        v_bal -= delta;
    }
    double getDelta_u_v()
    {
        return Delta_u_v;
    }
    double getDelta_v_u()
    {
        return Delta_v_u;
    }

    int get_u()
    {
        return p[0];
    }
    int get_v()
    {
        return p[1];
    }
    double get_u_bal() {
        return u_bal;
    }
    double get_v_bal() {
        return v_bal;
    }
};