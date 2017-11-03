#ifndef _HG_entropy_H
#define _HG_entropy_H

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
class HG_entropy
{
    private:
        BOBHash32 * bobhash;
        int M;
    public:
        struct node {int C,FP;} HK[2000005][20];
        int ext[2000005][40];
        double entro;
        HG_entropy(int M,int prm):M(M) {entro=0; bobhash=new BOBHash32(prm);}
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
                        int p=Hsh % ct;
                        if (ext[Hsh][p]) entro-=ext[Hsh][p]*log(ext[Hsh][p])/log(2);
                        if (ext[Hsh][p]<16) ext[Hsh][p]++;
                        entro+=ext[Hsh][p]*log(ext[Hsh][p])/log(2);
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
