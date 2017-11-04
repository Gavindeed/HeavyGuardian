#ifndef _k_ary_H
#define _k_ary_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include "BOBHASH32.h"
#define D 4
using namespace std;
class k_ary
{
private:
    BOBHash32 * bobhash[D+2];
    int tot[D+2][1000005];
    map<string,int> mp;
    set<pair<int,string> > st;
    int M,cnt,K;
public:
    k_ary(int M,int K):M(M),K(K)
    {
        for (int i=0; i<D; i++) bobhash[i]=new BOBHash32(i+1000);
        for (int i=0; i<D; i++) for (int j=0; j<M; j++) tot[i][j]=0;
        mp.clear(); st.clear(); cnt=0;
    }
    void Insert(string A)
    {
        int MIN=1000000000,MAX=0,sum=0;
        for (int i=0; i<D; i++)
        {
            int WZ=(bobhash[i]->run(A.c_str(),A.size()))%M;
            tot[i][WZ]++; MIN=min(MIN,tot[i][WZ]);
        }
        int t=MIN;
        if (mp[A])
        {
            st.erase(make_pair(mp[A],A));
            mp[A]=t;
            st.insert(make_pair(t,A));
        } else
        {
            cnt++;
            mp[A]=t;
            st.insert(make_pair(t,A));
            if (cnt>K)
            {
                pair<int,string> p = *(st.upper_bound(make_pair(0,"")));
                mp.erase(p.second); cnt--;
                st.erase(p);
            }
        }
    }
    pair<string,int> Query(int k)
    {
        if (cnt==0) return make_pair("",-1);
        cnt--;
        set<pair<int,string> >::iterator sit=st.end(); sit--;
        int MIN=1000000000;
        for (int i=0; i<D; i++)
        {
            int WZ=(bobhash[i]->run((sit->second).c_str(),(sit->second).size()))%M;
            MIN=min(MIN,tot[i][WZ]);
        }
        pair<string, int> g = make_pair(sit->second,MIN); st.erase(*sit);
        return g;
    }
};
#endif
