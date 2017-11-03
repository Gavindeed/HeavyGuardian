#ifndef _CM_entropy_H
#define _CM_entropy_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include "BOBHASH32.h"
#define cp_d 4
using namespace std;
class CM_entropy
{
    private:
        int M,sum[2500005];
        BOBHash32 * bobhash[cp_d+2];
    public:
        double entro;
        CM_entropy(int M):M(M) {entro=0;for (int i=0; i<M; i++) sum[i]=0;for (int i=0; i<cp_d; i++) bobhash[i]=new BOBHash32(i+1000);}
        void Insert(string x)
        {
            int MIN=1000000000;
            for (int i=0; i<cp_d; i++)
            {
                int p=bobhash[i]->run(x.c_str(),x.size()) % M;
                MIN=min(MIN,sum[p]); sum[p]++;
            }
            if (MIN) entro-=MIN*log(MIN)/log(2);
            entro+=(MIN+1)*log(MIN+1)/log(2);
        }
        int Query(string x)
        {
            int ans=1000000;
            for (int i=0; i<cp_d; i++)
            {
                int p=bobhash[i]->run(x.c_str(),x.size()) % M;
                ans=min(ans,sum[p]);
            }
            return ans;
        }
};
#endif
