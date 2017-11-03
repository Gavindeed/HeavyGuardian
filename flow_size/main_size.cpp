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
#include "HeavyGuarding.h"
#define HK_d 1
#define HK_b 1.08
using namespace std;
ifstream fin("u1",ios::in|ios::binary);
char a[105];
int CM_M,HG_M;
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
    int num=0;
    for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++) num++;

    //set
    int MEM; cin>>MEM;
    for (HG_M=1; (34*G+ct*4)*HG_M<=MEM*1024*8; HG_M++);
    for (CM_M=1; 16*CM_M<=MEM*1024*8; CM_M++);
    HeavyGuarding * HG=new HeavyGuarding(HG_M,1000);
    CMSketch * CM= new CMSketch(CM_M);

    //insert
    for (int i=1; i<=m; i++)
    {
        string s=ss[i];
        CM->Insert(s);
        HG->Insert(s);
    }

    //Query
    double HG_ARE=0,HG_AAE=0,CM_ARE,CM_AAE;
    for (map<string,int> :: iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        int A=sit->second,AA=HG->Query(sit->first);
        HG_ARE+=abs(A-AA)/(A+0.0);
        HG_AAE+=abs(A-AA);

        AA=CM->Query(sit->first);
        CM_ARE+=abs(A-AA)/(A+0.0);
        CM_AAE+=abs(A-AA);
    }
    return 0;
}
