#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <fstream>
#include <map>
#include "BOBHASH32.h"
#include "BOBHASH64.h"
#include "HG_distribution.h"
#include "CMSketch.h"
using namespace std;
int True[100005],HG_now[100005],CM_now[100005];
ifstream fin("u1",ios::in|ios::binary);
char a[105];
int HG_M,CM_M;
string Read()
{
    fin.read(a,13);
    a[13]='\0';
    string tmp=a;
    return tmp;
}
string ss[10000005];
map <string ,int> B,C;
int main()
{
    //read
    int m=10000000;
    B.clear();
    for (int i=1; i<=m; i++) {ss[i]=Read(); B[ss[i]]++;}

    //set
    int MEM=512;
    for (HG_M=1; (32*G+ct*4)*HG_M+32768*16<=MEM*1024*8; HG_M++);
    HG_distribution * HG=new HG_distribution(HG_M,1000);
    for (CM_M=1; 16*CM_M+32768*16<=MEM*1024*8; CM_M++);
    CMSketch * CM=new CMSketch(CM_M);

    //Insert
    for (int i=1; i<=m; i++)
    {
        string s=ss[i];
        HG->Insert(s);
        CM->Insert(s);
    }

    //answer
    for (int i=1; i<32768; i++) True[i]=HG_now[i]=CM_now[i]=0;
    for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        True[sit->second]++;
        HG_now[HG->Query(sit->first)]++;
        CM_now[CM->Query(sit->first)]++;
    }
    return 0;
}
