#ifndef _entropy_H
#define _entropy_H

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
#define fp 17
#define ct 32
using namespace std;
class entropy
{
    private:
        BOBHash32 * bobhash[HK_d+2];
        int M;
    public:
        struct node {int C,FP;} HK[2000005][20];
        int ext[2000005][40];
        double entro;
        entropy(int M,int prm):M(M) {entro=0; for (int i=0; i<HK_d+2; i++) bobhash[i]=new BOBHash32(i+prm);}
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
                    if (HK[Hsh][k].C) entro-=HK[Hsh][k].C*log(HK[Hsh][k].C)/log(2);
                    HK[Hsh][k].C++;
                    if (HK[Hsh][k].C) entro+=HK[Hsh][k].C*log(HK[Hsh][k].C)/log(2);
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
                    if (HK[Hsh][X].C) entro-=HK[Hsh][X].C*log(HK[Hsh][X].C)/log(2);
                    HK[Hsh][X].C--;
                    if (HK[Hsh][X].C>0) entro+=HK[Hsh][X].C*log(HK[Hsh][X].C)/log(2);
                    if (HK[Hsh][X].C<=0)
                    {
                        HK[Hsh][X].FP=FP;
                        HK[Hsh][X].C=1;
                    } else
                    {
                        int p=bobhash[1]->run(x.c_str(),x.size()) % ct;
                        if (ext[Hsh][p]) entro-=ext[Hsh][p]*log(ext[Hsh][p])/log(2);
                        if (ext[Hsh][p]<16) ext[Hsh][p]++;
                        entro+=ext[Hsh][p]*log(ext[Hsh][p])/log(2);
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
                if (HK[Hsh][k].FP==FP) return max(1,HK[Hsh][k].C);
            }
            int p=bobhash[1]->run(x.c_str(),x.size()) % ct;
            //return 1;
            return max(1,ext[Hsh][p]);
        }
};
#endif
