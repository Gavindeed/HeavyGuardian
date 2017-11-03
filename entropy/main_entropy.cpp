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
#include "CM_entropy.h"
#include "HG_entropy.h"
using namespace std;
ifstream fin("000",ios::in|ios::binary);
char a[105];
int HG_M,CM_M;
string Read()
{
    fin.read(a,8);
    a[8]='\0';
    string tmp=a;
    return tmp;
}
string ss[10000005];
double ansT[100005],anse[100005];
int main()
{
    // read
    int m=6000000;
    fin.close();
    char Filename[32];
    sprintf(Filename,"caida");
    fin.open(Filename,ios::in|ios::binary);
    for (int i=1; i<=2000000; i++) ss[i]=Read();
    fin.close();
    sprintf(Filename,"caida2");
    fin.open(Filename,ios::in|ios::binary);
    for (int i=2000001; i<=4000000; i++) ss[i]=Read();
    fin.close();
    sprintf(Filename,"caida39");
    fin.open(Filename,ios::in|ios::binary);
    for (int i=4000001; i<=6000000; i++) ss[i]=Read();

    //set
    int MEM=512;
    double True=0;
    for (CM_M=1; 16*CM_M<=MEM*1024*8; CM_M++);
    CM_entropy * CM=new CM_entropy(CM_M);
    for (HG_M=1; (32*G+ct*4)*HG_M<=MEM*1024*8; HG_M++);
    HG_entropy * HG=new HG_entropy(HG_M,1000);
    map<string,int> XX; XX.clear();

    //insert
    for (int i=1; i<=6000000; i++)
    {
        string s=ss[i];
        CM->Insert(s); HG->Insert(s);
        int P=XX[s];
        if (P) True-=P*log(P)/log(2);
        XX[s]++;
        P=XX[s];
        True+=P*log(P)/log(2);
    }
    printf("%.10f %.10f %.10f\n",True,CM->entro,HG->entro);
    return 0;
}
