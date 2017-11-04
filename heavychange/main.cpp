#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include "k_ary.h"
#include "HeavyGuarding.h"
using namespace std;
map <string ,int> B,C,DD,SUM,E,D2,D3,D4;
struct node {string x;int y;} p[10000005];
ifstream fin("u1",ios::in|ios::binary);
char a[105];
int mm;
string Read()
{
    fin.read(a,13);
    a[13]='\0';
    string tmp=a;
    return tmp;
}
string ss[10000005];
int main()
{
    //read
    int m=10000000; double theta=0.0002;
    for (int i=1; i<=m; i++)
    {
        string s=Read(); ss[i]=s;
        if (i<=m/2) B[s]++,SUM[s]++; else C[s]++,SUM[s]--;
    }

    // get the number of distinct flows
    for (map <string,int> :: iterator sit = SUM.begin(); sit!=SUM.end(); sit++) mm+=abs(sit->second);

    // heavychange flows
    int cnt=0;
    for (map <string,int>::iterator sit=B.begin(); sit!=B.end(); sit++)
    if (sit->second - C[sit->first] >= mm*theta)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second - C[sit->first];
    }
    for (map <string,int>::iterator sit=C.begin(); sit!=C.end(); sit++)
    if (sit->second - B[sit->first] >= mm*theta)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second - B[sit->first];
    }
    for (int i=1; i<=cnt; i++) E[p[i].x]=p[i].y;

    //set
    int MEM; cin>>MEM;
    int sk_M,K; double MEM1=MEM-60;  double  MEM2=60;
    for (sk_M=1; 32*sk_M*4<=MEM1*1024*4; sk_M++);
    for (K=1; 432*K<=MEM2*1024*4; K++);
    k_ary *k1; k1=new k_ary(sk_M,K);
    k_ary *k2; k2=new k_ary(sk_M,K);

    int hk_M;
    MEM1=MEM-20;
    for (hk_M=1; 32*hk_M*8<=MEM1*1024*4; hk_M++);
    HeavyGuarding *hg1; hg1=new HeavyGuarding(hk_M,mm*theta,1000);
    HeavyGuarding *hg2; hg2=new HeavyGuarding(hk_M,mm*theta,500);

    //insert
    for (int i=1; i<=m; i++)
	{
		string s=ss[i];
		if (i<=m/2) k1->Insert(s),hg1->Insert(s); else k2->Insert(s),hg2->Insert(s);
	}

	// get the heavychange of k_ary
    DD.clear(); D2.clear();
    for (int i=0; i<K; i++)
      {
          pair<string,int> x=k1->Query(i);
          pair<string,int> y=k2->Query(i);
          DD[x.first]=x.second;
          D2[y.first]=y.second;
      }
    for (map <string,int>::iterator sit=D2.begin(); sit!=D2.end(); sit++) {DD[sit->first]-=sit->second;}

    // caculate PRE, ARE, recall
    int k_ary_right=0; double k_ary_ARE=0;
    int k_ary_report=0;
    for (map <string,int>::iterator sit=DD.begin(); sit!=DD.end(); sit++)
    if (abs(sit->second) >= mm*theta && sit->first!="")
    {
        string k_ary_string=(sit->first); int k_ary_num=abs(sit->second);
        if (k_ary_num<mm*theta) continue;
        k_ary_report++;
        k_ary_ARE+=abs(k_ary_num-abs(SUM[k_ary_string]));
        if (E[k_ary_string]) k_ary_right++;
    }

    // get the heavychange of HeavyGuarding
    DD.clear(); D2.clear();
    for (int i=1; i<=hg1->cnt; i++)
      {
          pair<string,int> x=make_pair(hg1->ans[i],hg1->Query(hg1->ans[i]));
          pair<string,int> y=make_pair(hg1->ans[i],hg2->Query(hg1->ans[i]));
          DD[x.first]=x.second; D2[y.first]=y.second;
      }
    for (int i=1; i<=hg2->cnt; i++)
      {
          pair<string,int> x=make_pair(hg2->ans[i],hg1->Query(hg2->ans[i]));
          pair<string,int> y=make_pair(hg2->ans[i],hg2->Query(hg2->ans[i]));
          DD[x.first]=x.second; D2[y.first]=y.second;
      }
    for (map <string,int>::iterator sit=D2.begin(); sit!=D2.end(); sit++) {DD[sit->first]-=sit->second;}

    // caculate PRE, ARE, recall
    int HeavyGuarding_right=0; double HeavyGuarding_ARE=0;
    int HeavyGuarding_report=0;
    for (map <string,int>::iterator sit=DD.begin(); sit!=DD.end(); sit++)
    if (abs(sit->second) >= mm*theta && sit->first!="")
    {
        string HeavyGuarding_string=(sit->first); int HeavyGuarding_num=abs(sit->second);
        if (HeavyGuarding_num<mm*theta) continue;
        HeavyGuarding_report++;
        HeavyGuarding_ARE+=abs(HeavyGuarding_num-abs(SUM[HeavyGuarding_string]));
        if (E[HeavyGuarding_string]) HeavyGuarding_right++;
    }
    return 0;
}
