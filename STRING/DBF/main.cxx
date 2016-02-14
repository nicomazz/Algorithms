#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define MAXN 100
#define MAXL 20

int dbf[MAXN][MAXL];

int INX[MAXN];
int R[MAXN];
int tmp_R[MAXN];
struct cmp_pair
{
	int f,s, inx;
	bool operator<(const cmp_pair & b)const
	{
		if ( f != b.f) return f < b.f;
		return s < b.s;
	}
	bool operator== (const cmp_pair & b)const
	{ return f == b.f && s == b.s;}
	bool operator!= (const cmp_pair & b)const
	{return !operator ==(b);}
};
vector<cmp_pair> ts;
void createDbf(string s)
{
	for (int i = 0; i < s.size(); i++)
		dbf[i][0] = s[i];
		
	for (int i = 1; i < MAXL; i++)
	{
		if ((1<<i) >= s.size()) return;
		cerr<<"dbf livello: "<<i<<"\n";
		ts.clear();
		// inserimento pair
		for (int j = 0; j < s.size() - (1<<i); j++)
		{
			//cerr<<"insert "<<dbf[j][i-1]<<" "<<dbf[j+(1<<i)][i-1]<<"\n";
			ts.push_back({dbf[j][i-1], dbf[j+(1<<(i-1))][i-1], j});
		}
		cerr<<"inseriti..\n";
		sort(ts.begin(),ts.end());
		cerr<<"sorted..\n";
		dbf[ts[0].inx][i] = 1;
		for (int j = 1; j < ts.size(); j++)
			dbf[ts[j].inx][i] = dbf[ts[j-1].inx][i] + (ts[j] != ts[j-1] ? 1:0); 
	}
}
vector<int> z_alg(string s)
{
	int n = s.size();
	vector<int> z(n);
	int L = 0,R = 0;
	for (int i = 1; i < n; i++)
	{
		if ( i <= R)
			z[i] = min(z[i-L], R-i+1);
		while ( z[i]+i < n && s[z[i]] == s[z[i]+i])
			z[i]++;
		if ( z[i]+i-1 > R)
		L = i, R = z[i]+i-1;
	
	}
}
int main()
{
	string s = "abbaabbabba";
	createDbf(s);
	
	for (int i = 0; i < 4; i++)
	{
		cerr<<"\n livello "<<i<<": ";
		for (int j = 0; j < s.size()- (1<<i); j++)
			cerr<<dbf[j][i]<<" ";
		
	}
	
}
