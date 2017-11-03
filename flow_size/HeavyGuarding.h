#ifndef _HeavyGuarding_H
#define _HeavyGuarding_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHASH32.h"
#include "BOBHASH64.h"
#define HK_b 1.08
#define G 8
#define ct 32  // the number of cold items for each bucket
using namespace std;
class HeavyGuarding
{
    private:
        BOBHash32 * bobhash;
        int M;
    public:
        struct node {int C,FP;} HK[1000005][20];
        int ext[1000005][40];
        HeavyGuarding(int M,int prm):M(M) {bobhash=new BOBHash32(prm);}
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
                    FLAG=true;
                    break;
                }
                if (FLAG) break;
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
                    } else
                    {
                        int p=Hsh % ct;
                        if (ext[Hsh][p]<16) ext[Hsh][p]++;
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
                if (HK[Hsh][k].FP==FP) return max(1,HK[Hsh][k].C);
            }
            int p=Hsh % ct;
            return max(1,ext[Hsh][p]);
        }
};
#endif
