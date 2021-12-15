#include "TransactionChannel.h"
TransactionChannel::TransactionChannel(int u, int v, double u_bal, double v_bal)
        : p(vector<int>({u, v})){
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
}

