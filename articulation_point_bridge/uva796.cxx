#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<pi> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 10100

int n,m;
vector<int> graph[MAXN];
int num[MAXN], low[MAXN];
int p[MAXN];
int att;

int N;

set<pi> bridge;
void find_bridge(int i)
{
	num[i] = low[i] = ++att;
	for (auto & adj : graph[i])
	{
		if (num[adj] == 0)
		{
			p[adj] = i;
			find_bridge(adj);
			if ( num[i] < low[adj]) bridge.insert({min(i,adj),max(i,adj)});
			low[i] = min(low[i],low[adj]);
		}
		else if (p[i] != adj)
			low[i] = min(low[i],num[adj]);
	}
}
int main()
{
	while (cin>>N)
	{
		char dummy;
		for (int i = 0; i <N; i++)
		{
			int n; cin>>n;
			cin>>dummy;
			int num; cin>>num;
			cin>>dummy;
			graph[n].resize(num);
			for(auto& adj:graph[n]) cin>>adj;
		}
		bridge.clear();
		memset(num,0,sizeof num);
		memset(low,0,sizeof low);
		memset(p,-1,sizeof p);
		att = 0;
		for (int i = 0; i < N; i++)
			if (num[i] == 0)find_bridge(i);
		
		cout<<bridge.size()<<" critical links\n";
		for (pi i: bridge)
			cout<<i.first<<" - "<<i.second<<"\n";
		cout<<"\n";
	}
}
