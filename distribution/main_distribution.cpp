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
#include "distribution.h"
using namespace std;
int mm,True[100005],now[100005];
double f1[1005],f2[1005],f3[1005],f4[1005];
ifstream fin("000",ios::in|ios::binary);
ofstream fout("webpage.txt",ios::out);
char a[105];
string ans[10005],ANS[10005];
int cnt,M,CNT,M2;
BOBHash32 * bobhash[HK_d+2];
string Read()
{
    fin.read(a,13);
    //for (int i=0; i<4; i++) if (a[i]==0) a[i]=255;
    a[13]='\0';
    string tmp=a;
    return tmp;
}
string ss[10000005];
map <string ,int> B,C;
int main()
{
   // freopen("b.out","w",stdout);
    for (int i=0; i<HK_d; i++) bobhash[i]=new BOBHash32(i+1000);
    int m=10000000;// double theta=0.0002; mm=int(m*theta);
  //  freopen("SKEWNESS.txt","w",stdout);
  //  puts("SKEW PRE SKEW ARE SKEW recall");
  //  for (int I=1; I<=10; I++)
  //  {
  //for (int I=1; I<=10; I++)
  //{
    fin.close();
    char Filename[32];
  //  if (I<=3) sprintf(Filename,"00%d.dat",I*3); else
  //    sprintf(Filename,"0%d.dat",I*3);
   sprintf(Filename,"u1");
    fin.open(Filename,ios::in|ios::binary);
    B.clear();
    for (int i=1; i<=m; i++) {ss[i]=Read(); B[ss[i]]++;}
    //cout<<SS<<endl;
   // puts("start");
   freopen("distribution.txt","w",stdout);
    for (int MEM=128; MEM<=512; MEM*=2)
    {
        for (M=1; (32*G+ct*4)*M+32768*16<=MEM*1024*8; M++);
        distribution * o1=new distribution(M,1000);
        for (int i=1; i<=m; i++)
        {
            string s=ss[i];
            o1->Insert(s);
            //if (i%1000000==0) cout<<i<<endl;
        }
        double ARE2=0; double AAE2=0; int SS=0;
        for (int i=1; i<32768; i++) True[i]=now[i]=0;
        for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
        {
            //cout<<sit->second<<' '<<o1->Query(sit->first)<<endl;
            True[sit->second]++;
            now[o1->Query(sit->first)]++;
          //  True+=(sit->second)*log(sit->second)/log(2);
          //  now+=o1->Query(sit->first)*log(o1->Query(sit->first))/log(2);
          //  f1[I]=AAE2/SS;
          //  f2[I]=ARE2/SS;
        }
        cout<<MEM<<endl;
        for (int i=1; i<32768; i++) cout<<i<<' '<<True[i]<<' '<<now[i]<<endl;
        cout<<endl;
    }
 // }
    return 0;
}
