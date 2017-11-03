#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <fstream>
#include "ssummary.h"
#include "HeavyGuarding.h"
#include "spacesaving.h"
#include "SH.h"
#include <iomanip>
#include <time.h>
using namespace std;
map <string ,int> B,C;
string ss2[10000005];
struct node {string x;int y;} p[10000005];
ifstream fin("u1",ios::in|ios::binary);
char a[105];
string Read()
{
    fin.read(a,13);
    a[13]='\0';
    string tmp=a;
    return tmp;
}
int cmp(node i,node j) {return i.y>j.y;}
int main()
{
    int m=10000000; double theta=0.0002;

    // the real heavyhitter
    B.clear(); C.clear();
    for (int i=1; i<=m; i++)
    {
        ss2[i]=Read();
        B[ss2[i]]++;
    }
    int cnt=0;
    for (map <string,int>::iterator sit=B.begin(); sit!=B.end(); sit++)
    {
        p[++cnt].x=sit->first;
        p[cnt].y=sit->second;
    }
    sort(p+1,p+cnt+1,cmp);
    int num=0; // the number of the real heavyhitter
    for (int i=1; i<=cnt; i++) if (p[i].y>=int(m*theta)) num++,C[p[i].x]=p[i].y; else break;

    // configuration
    int MEM; cin>>MEM;

    int sk_M,sk_K;
    for (sk_M=1; 32*sk_M*4<=(MEM-30)*1024*8; sk_M++);
    for (sk_K=1; 432*sk_K<=30*1024*8; sk_K++);
    SH *sh; sh=new SH(sk_M,sk_K,int(m*theta));
    // sketch+heap.  (MEM-30) KB for sketch, 30 KB for heap.

    int hk_M;
    for (hk_M=1; 32*hk_M*8<=(MEM-10)*1024*8; hk_M++);
    HeavyGuarding *hg=new HeavyGuarding(hk_M,int(m*theta),1000);
    // 10 KB for auxiliary list, (MEM-10) KB for HeavyGuarding

    int SS_M;
    for (SS_M=1; 432*SS_M<=MEM*1024*8; SS_M++);
    spacesaving *ss; ss=new spacesaving(SS_M,int(m*theta));
    // spacesaving

    // Insert
    for (int i=1; i<=m; i++)
	{
		string s=ss2[i];
		sh->Insert(s);
		hg->Insert(s);
		ss->Insert(s);
	}
	ss->work();

    // Calculate
    int ss_sum=0; double ss_ARE=0; int ss_ht=SS_M;
    for (int i=0; i<SS_M; i++)
    {
        string ss_string; int ss_num;
        ss_string=(ss->Query(i)).first; ss_num=(ss->Query(i)).second;
        if (ss_num==-1) {ss_ht=i; break;} // ss_ht means the number of heavyhitter for SpaceSaving
        ss_ARE+=abs(B[ss_string]-ss_num)/(B[ss_string]+0.0);
        if (C[ss_string]) ss_sum++; // how much is right
    }
    printf("SpaceSaving:\nARE: %.10f\nPRE: %.10f\nRecall: %.10f\n",ss_ARE/ss_ht,ss_sum/(ss_ht+0.0),ss_sum/(num+0.0));
    // SpaceSaving

    int hg_sum=0; double hg_ARE=0; int hg_ht=hg->cnt;
    for (int i=1; i<=hg->cnt; i++)
    {
        string hg_string; int hg_num;
        hg_string=hg->ans[i]; hg_num=(hg->Query(hg_string));
        hg_ARE+=abs(B[hg_string]-hg_num)/(B[hg_string]+0.0);
        if (C[hg_string]) hg_sum++;
    }
    printf("HeavyGuarding:\nARE: %.10f\nPRE: %.10f\nRecall: %.10f\n",hg_ARE/hg_ht,hg_sum/(hg_ht+0.0),hg_sum/(num+0.0));
    // HeavyGuarding

    int sh_sum=0; double sh_ARE=0; int sh_ht=sk_K;
    for (int i=0; i<sk_K; i++)
    {
        string sh_string; int sh_num;
        pair<string,int> pp=sh->Query(i);
        sh_string=pp.first; sh_num=pp.second;
        if (sh_num==-1) {sh_ht=i; break;}
        sh_ARE+=abs(B[sh_string]-sh_num)/(B[sh_string]+0.0);
        if (C[sh_string]) sh_sum++;
    }
    printf("Sketch+heap:\nARE: %.10f\nPRE: %.10f\nRecall: %.10f\n",sh_ARE/sh_ht,sh_sum/(sh_ht+0.0),sh_sum/(num+0.0));
    return 0;
}
