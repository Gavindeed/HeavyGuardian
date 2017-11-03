#ifndef _CMSketch_H
#define _CMSketch_H

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
class CMSketch
{
    private:
        int M,sum[2500005];
        BOBHash32 * bobhash[cp_d+2];
    public:
        CMSketch(int M):M(M) {for (int i=0; i<cp_d; i++) bobhash[i]=new BOBHash32(i+1000);}
        void Insert(string x)
        {
            for (int i=0; i<cp_d; i++)
            {
                int p=bobhash[i]->run(x.c_str(),x.size()) % M;
                sum[p]++;
            }
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
