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
            if(allSenders.find(sender)==allSenders.end()) {
                allSenders.insert(sender);
            }
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

    void rebalance() {
        vector<TransactionChannel> *channels = generateTransactionChannels();
        print(*channels);
        clock_t start,end;
        start = clock();
        vector<TransactionChannel> rebalancedChannels = rebalanceCore(*channels,allSenders.size());
            end = clock();
        print(rebalancedChannels);
        cout<<"total time : "<<end-start<<"ms"<<endl;
    }
    vector<TransactionChannel>& rebalanceCore(vector<TransactionChannel> &channels,int m)
    {
        glp_prob *lp;
        lp = glp_create_prob();
        glp_set_obj_dir(lp, GLP_MAX);

        int n = channels.size();
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
                if (channels[j - 1].get_u() + 1 == i)
                {
                    ar[count] = 1;
                }
                else if (channels[j - 1].get_v() + 1 == i)
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
        return channels;
    }

    void print(vector<TransactionChannel> channels)
    {
        double unbalance = 0;
        for (TransactionChannel x : channels)
        {
            x.print();
            unbalance+=abs((x.get_u_bal()-x.get_v_bal())/(x.get_u_bal()+x.get_v_bal()));
        }
        cout<<"avg of unbalance rate : "<< unbalance/channels.size()<<endl;
    }
};