#ifndef _HeavyGuarding_H
#define _HeavyGuarding_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHash32.h"
#include "BOBHash64.h"
#define G 8
#define HK_b 1.08
using namespace std;
class HeavyGuarding
{
    private:
        struct node {int C; unsigned int FP;} HK[1000005][G+2];
        BOBHash32 * bobhash;
        int M,p;
    public:
        int cnt;
        string ans[1005];
        void ADD(string x) {ans[++cnt]=x;}
        HeavyGuarding(int M,int p,int prm):M(M),p(p) {cnt=0; bobhash=new BOBHash32(prm);}
        void Insert(string x)
        {
            unsigned int H=bobhash->run(x.c_str(),x.size());
            unsigned int FP=(H>>16),Hsh=H % M;
            bool FLAG=false;
            for (int k=0; k<G; k++)
            {
                int c=HK[Hsh][k].C;
                if (HK[Hsh][k].FP==FP)
                {
                    HK[Hsh][k].C++;
                    if (HK[Hsh][k].C==p) ADD(x);
                    FLAG=true;
                    break;
                }
            }
            if (!FLAG)
            {
                int X,MIN=1000000000;
                for (int k=0; k<G; k++)
                {
                    int c=HK[Hsh][k].C;
                    if (c<MIN) {MIN=c; X=k;}
                }
                if (!(rand()%int(pow(HK_b,HK[Hsh][X].C))))
                {
                    HK[Hsh][X].C--;
                    if (HK[Hsh][X].C<=0)
                    {
                        HK[Hsh][X].FP=FP;
                        HK[Hsh][X].C=1;
                    }
                }
            }
        }
        int Query(string x)
        {
            unsigned int H=bobhash->run(x.c_str(),x.size());
            unsigned int FP=(H>>16),Hsh=H % M;
            for (int k=0; k<G; k++)
            {
                int c=HK[Hsh][k].C;
                if (HK[Hsh][k].FP==FP) return HK[Hsh][k].C;
            }
            return 0;
        }
};
#endif
