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
#include "entropy.h"
using namespace std;
int mm;
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
   //puts("MEM True now ARE");
   freopen("entropy_result.txt","w",stdout);
    for (int MEM=128; MEM<=512; MEM*=2)
    {
        cout<<MEM<<endl;
        double True=0,now=0; map<string,int> XX; XX.clear();
        for (M=1; (32*G+ct*4)*M<=MEM*1024*8; M++);
        entropy * o1=new entropy(M,1000);
        for (int i=1; i<=m; i++)
        {
            string s=ss[i];
            o1->Insert(s);
            int XX2=XX[s]; if (XX2) True-=XX2*log(XX2)/log(2);
            XX[s]++;
            XX2=XX[s]; if (XX2) True+=XX2*log(XX2)/log(2);
            if (i%1000==0) printf("%d %.10f %.10f\n",i,True,o1->entro);
            //if (i%1000000==0) cout<<i<<endl;
        }/*
        double ARE2=0; double AAE2=0; int SS=0;
        for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
        {
            True+=(sit->second)*log(sit->second)/log(2);
            now+=o1->Query(sit->first)*log(o1->Query(sit->first))/log(2);
          //  f1[I]=AAE2/SS;
          //  f2[I]=ARE2/SS;
        }
        printf("%d %.10f %.10f %.10f\n",MEM,True,now,fabs(True-now)/True);*/
    }
 // }
    return 0;
}
