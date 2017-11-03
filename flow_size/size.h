#ifndef _size_H
#define _size_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHASH32.h"
#include "BOBHASH64.h"
#define HK_d 1
#define HK_b 1.08
#define G 8
#define fp 16
#define ct 32
using namespace std;
class size
{
    private:
        BOBHash32 * bobhash[HK_d+2];
        int M;
    public:
        struct node {int C,FP;} HK[1000005][20];
        int ext[1000005][40];
        size(int M,int prm):M(M) {for (int i=0; i<HK_d+2; i++) bobhash[i]=new BOBHash32(i+prm);}
        void Insert(string x)
        {
            int FP=(bobhash[0]->run(x.c_str(),x.size())) % (1<<fp);
            bool FLAG=false;
            int Hsh=(bobhash[0]->run(x.c_str(),x.size()))%M;
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
                        int p=bobhash[1]->run(x.c_str(),x.size()) % ct;
                        if (ext[Hsh][p]<16) ext[Hsh][p]++;
                    }
                }
            }
        }
        int Query(string x)
        {
            int FP=(bobhash[0]->run(x.c_str(),x.size()))  % (1<<fp);
            int Hsh=(bobhash[0]->run(x.c_str(),x.size()))%M;
            for (int k=0; k<G; k++)
            {
                int c=HK[Hsh][k].C;
                if (HK[Hsh][k].FP==FP) return HK[Hsh][k].C;
            }
            int p=bobhash[1]->run(x.c_str(),x.size()) % ct;
            return ext[Hsh][p];
        }
};
#endif
