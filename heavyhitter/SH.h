#ifndef _SH_H
#define _SH_H

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include "BOBHash32.h"
#define D 4
#define sh_M 1000000
using namespace std;
class SH
{
private:
    BOBHash32 * bobhash[D+2];
    int tot[D+2][sh_M+2];
    map<string,int> mp;
    set<pair<int,string> > st;
    int M2,K,p,cnt;
public:
    SH(int M2,int K,int p):M2(M2),K(K),p(p)
    {
        for (int i=0; i<D; i++) bobhash[i]=new BOBHash32(i+1000);
        for (int i=0; i<D; i++) for (int j=0; j<M2; j++) tot[i][j]=0;
        mp.clear(); st.clear(); cnt=0;
    }
    void Insert(string A)
    {
        int MIN=1000000000;
        for (int i=0; i<D; i++)
        {
            int WZ=(bobhash[i]->run(A.c_str(),A.size()))%M2;
            tot[i][WZ]++;
            MIN=min(MIN,tot[i][WZ]);
        }
        if (mp[A])
        {
            st.erase(make_pair(mp[A],A));
            mp[A]=MIN;
            st.insert(make_pair(MIN,A));
        } else
        {
            cnt++;
            mp[A]=MIN;
            st.insert(make_pair(MIN,A));
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
        set<pair<int,string> >::iterator sit=st.end();
        sit--;
        pair<string, int> g = make_pair(sit->second,sit->first); st.erase(*sit);
        if (g.second>=p) return g; else return make_pair("",-1);
    }
};
#endif
