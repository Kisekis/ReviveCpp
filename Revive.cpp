#include <iostream>
#include "Revive.h"
#define THRESHOLD (float)1 / 2
using namespace osuCrypto;

Revive::Revive()
{
    IOService ios(4);
    Participant A("A", 0, 1213, &ios);
    pars.push_back(A);
    Participant B("B", 1, 1214, &ios);
    pars.push_back(B);
    Participant C("C", 2, 1215, &ios);
    pars.push_back(C);
    Participant D("D", 3, 1215, &ios);
    pars.push_back(D);
    TransactionChannel AB(A, B, 100, 0);
    channels.push_back(AB);
    TransactionChannel BC(B, C, 100, 0);
    channels.push_back(BC);
    TransactionChannel CD(C, D, 100, 0);
    channels.push_back(CD);
    TransactionChannel DA(D, B, 100, 30);
    channels.push_back(DA);
    bool requestSuccess = sendRequest();
    if (requestSuccess)
    {
        print();
        rebalance();
        print();
    }
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
    if ((float)leader.getRecvCount() / pars.size() > THRESHOLD)
    {
        return true;
    }
    return false;
}
void Revive::rebalance()
{
    glp_prob *lp;
    lp = glp_create_prob();
    glp_set_obj_dir(lp, GLP_MAX);

    int n = channels.size();
    int m = pars.size();
    glp_add_rows(lp, m);
    glp_add_cols(lp, n);

    for (int i = 1; i <= m; i++)
    {
    auxiliary_variables_rows:
        glp_set_row_name(lp, i, "y" + i);
        glp_set_row_bnds(lp, i, GLP_FX, 0.0, 0.0);
    }

    for (int i = 1; i <= n; i++)
    {
    variables_columns:
        glp_set_col_name(lp, i, "x" + i);
        glp_set_col_bnds(lp, i, GLP_DB, 0.0, min(+channels[i - 1].getDelta_u_v(), -channels[i - 1].getDelta_v_u()));

    to_maximize:
        if (channels[i - 1].isAgreed())
        {
            glp_set_obj_coef(lp, i, 1);
        }
        else
        {
            glp_set_obj_coef(lp, i, 0);
        }
    }

    int ia[1 + 1000], ja[1 + 1000];
    double ar[1 + 1000];
    int count = 0;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            count = n * (i - 1) + j;
            ia[count] = i;
            ja[count] = j;
            if (channels[j - 1].get_u().getIndex() + 1 == i)
            {
                ar[count] = 1;
            }
            else if (channels[j - 1].get_v().getIndex() + 1 == i)
            {
                ar[count] = -1;
            }
            else
            {
                ar[count] = 0;
            }
        }
    }
    glp_load_matrix(lp, m * n, ia, ja, ar);
calculate:
    glp_simplex(lp, NULL);
output:
    double z, x1, x2;
    z = glp_get_obj_val(lp);
    for (int i = 0; i < n; i++)
    {
        if (channels[i].isAgreed())
        {
            channels[i].setdelta(glp_get_col_prim(lp, i + 1));
            channels[i].update();
        }
    }
}

int main()
{
    Revive simu;
}
