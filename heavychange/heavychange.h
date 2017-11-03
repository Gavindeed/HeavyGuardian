#ifndef _heavychange_H
#define _heavychange_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHash32.h"
// #include "BOBHASH64.h"
#define HK_d 1
#define MAX_MEM 1000000
#define HK_b 1.08
#define G 8
#define rep(i,a,n) for(int i=a;i<=n;i++)
using namespace std;
class heavychange
{
    private:
        struct node {int C; string FP;} HK[MAX_MEM][G+2];
        BOBHash32 * bobhash[HK_d+5];
        int M2;
    public:
        heavychange(int M2):M2(M2) {for (int i=0; i<HK_d; i++) bobhash[i]=new BOBHash32(i+1005);}
        void clear()
        {
            for (int i=0; i<MAX_MEM; i++)
                for (int j=0; j<G; j++) HK[i][j].C=0,HK[i][j].FP="";
        }
        unsigned long long Hash(int j,string ST)
        {
            return (bobhash[j]->run(ST.c_str(),ST.size()));
        }
        void Insert(string x)
        {
            unsigned long long Hsh=Hash(0,x) % M2;
            bool FLAG=false;
            for (int k=0; k<G; k++)
            {
                if (HK[Hsh][k].FP==x)
                {
                    HK[Hsh][k].C++;
                    FLAG=true;
                }
            }
            if (!FLAG)
            {
                int MIN=1000000000,X=0;
                for (int k=0; k<G; k++)
                    if (HK[Hsh][k].C<MIN) MIN=HK[Hsh][k].C,X=k;
                if (HK[Hsh][X].C<=50 && !(rand()%int(pow(HK_b,HK[Hsh][X].C))))
                {
                    HK[Hsh][X].C--;
                    if (HK[Hsh][X].C<=0)
                    {
                        HK[Hsh][X].FP=x;
                        HK[Hsh][X].C=1;
                    }
                }
            }
        }
        pair<string ,int> Query(int i,int j)
        {
         //   cout<<q[k].y<<' '<<p<<endl;
            return make_pair(HK[i][j].FP,HK[i][j].C);
        }
};
#endif
