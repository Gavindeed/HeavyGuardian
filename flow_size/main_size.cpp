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
#include "CMSketch.h"
#include "size.h"
#define HK_d 1
#define HK_b 1.08
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
    for (int MEM=100; MEM<=1000; MEM+=100)
    {
        for (M=1; (34*8+32*4)*M*HK_d<=MEM*1024*8; M++);
        for (M2=1; 16*M2<=MEM*1024*8; M2++);
        size * o1=new size(M,1000);
        CMSketch * o2= new CMSketch(M2);
        for (int i=1; i<=m; i++)
        {
            string s=ss[i];
            o2->Insert(s);
            o1->Insert(s);
            //if (i%1000000==0) cout<<i<<endl;
        }
        int S10=0;
        for (int i=0; i<M; i++) for (int j=0; j<32; j++) S10+=o1->ext[i][j];
        cout<<M*32<<' '<<S10<<endl;
        double ARE2=0; double AAE2=0; int SS=0;
        for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
        {
            int A=sit->second,AA=o1->Query(sit->first);
            ARE2+=abs(A-AA)/(A+0.0);
            AAE2+=abs(A-AA);
            SS++;
          //  f1[I]=AAE2/SS;
          //  f2[I]=ARE2/SS;
        }
        printf("AAE: %.10f   ARE: %.10f\n",AAE2/SS,ARE2/SS);

        double ARE=0; double AAE=0;
        for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
        {
            int A=sit->second,AA=o2->Query(sit->first);
            ARE+=abs(A-AA)/(A+0.0);
            AAE+=abs(A-AA);
          //  f3[I]=AAE/SS;
          //  f4[I]=ARE/SS;
        }
        printf("AAE: %.10f   ARE: %.10f\n",AAE/SS,ARE/SS);
    }
 // }
  return 0;
    freopen("size_SKEWNESS_change_SKEW.txt","w",stdout);
    puts("SKEWNESS");
    puts("AAE");
    puts("SKEW heavyguarding CMSketch");
    for (int i=1; i<=10; i++)
    {
        printf("%.2f %.10f %.10f\n",i*0.03,f1[i],f3[i]);
    }
    puts("");
    puts("ARE");
    puts("MEM heavyguarding CMSketch");
    for (int i=1; i<=10; i++)
    {
        printf("%.2f %.10f %.10f\n",i*0.03,f2[i],f4[i]);
    }
  //  }
    return 0;
}
