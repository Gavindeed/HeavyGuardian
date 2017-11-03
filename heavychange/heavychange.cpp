#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include "heavychange.h"

using namespace std;

int N = 10000000;
int sID = 8;
double theta = 0.0002;

ifstream fin("caida", ios::in|ios::binary);

map<string, int> dict1;
map<string, int> dict2;

string Read()
{
	char a[32];
	fin.read(a, sID);
	a[sID] = '\0';
	return string(a);
}

int main()
{
	int mem = 200;
	int M = mem / 2 * 1024 / G / (sID + 2);
	heavychange *hg1 = new heavychange(M);
	heavychange *hg2 = new heavychange(M);
	for(int i = 0; i < N; i ++)
	{
		string item = Read();
		dict1[item] ++;
		hg1->Insert(item);
	}
	for(int i = 0; i < N; i ++)
	{
		string item = Read();
		dict2[item] ++;
		hg2->Insert(item);
	}
	map<string, int>::iterator it;
	double aae = 0;
	int count = 0;
	int D = 0;
	map<string, int> diff;
	for(it = dict1.begin(); it != dict1.end(); it ++)
	{
		D += abs(it->second - dict2[it->first]);
		diff.insert(make_pair(it->first, abs(it->second - dict2[it->first])));
		dict2.erase(it->first);
	}
	for(it = dict2.begin(); it != dict2.end(); it ++)
	{
		D += abs(it->second - dict1[it->first]);
		diff.insert(make_pair(it->first, abs(it->second - dict1[it->first])));
	}
	map<string, int> hc;
	for(it = diff.begin(); it != diff.end(); it ++)
	{
		if(it->second > theta * D)
		{
			hc.insert(make_pair(it->first, it->second));
		}
	}
	cout << "D = " << D << " T = " << theta * D << endl;
	map<string, int> hh1, hh2;
	for(int i = 0; i < M; i ++)
	{
		for(int j = 0; j < G; j ++)
		{
			hh1.insert(hg1->Query(i, j));
			hh2.insert(hg2->Query(i, j));
		}
	}
	int sum = 0;
	int cor = 0;
	// D = 0;
	int err = 0;
	map<string, int> esti;
	for(it = hh1.begin(); it != hh1.end(); it ++)
	{
		int d = abs(it->second - hh2[it->first]);
		// D += d;
		esti.insert(make_pair(it->first, d));
		hh2.erase(it->first);
	}
	for(it = hh2.begin(); it != hh2.end(); it ++)
	{
		int d = abs(it->second - hh1[it->first]);
		// D += d;
		esti.insert(make_pair(it->first, d));
	}

	// cout << "D = " << D << " T = " << theta * D << endl;

	for(it = esti.begin(); it != esti.end(); it ++)
	{
		if(it->second > theta * D)
		{
			// cout << it->second << ' ' << diff[it->first] << ' ' << hc[it->first] << endl;
			sum ++;
			if(hc[it->first] != 0)
			{
				cor ++;
			}
			err += abs(diff[it->first] - it->second);
		}
	}

	cout << cor << ' ' << sum << ' ' << hc.size() << ' ' << err << endl;

	cout << "PR = " << (double)cor / sum << endl;
	cout << "RC = " << (double)cor / hc.size() << endl;
	cout << "AAE = " << (double)err / sum << endl;

	return 0;
}
