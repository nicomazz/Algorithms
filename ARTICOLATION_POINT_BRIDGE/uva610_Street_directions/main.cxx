#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<pi> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 1010

int n,m;
set<int> graph[MAXN];
int art_point[MAXN];
int num[MAXN], low[MAXN];
int p[MAXN];
int att;
int at_root;
int child_root;

set<pi> bridge;
void find_art_bridge(int i)
{
	num[i] = low[i] = ++att;
	for (auto & adj : graph[i])
	{
		if (num[adj] == 0)
		{
			p[adj] = i;
			if ( i == at_root) child_root++;

			find_art_bridge(adj);
			if ( num[i] < low[adj]) bridge.insert({min(i,adj),max(i,adj)});
			if ( low[adj]  >= num[i] ) // va solo giù
				art_point[i]++;
			low[i] = min(low[i],low[adj]);
		}
		else if (p[i] != adj)
			low[i] = min(low[i],num[adj]);
	}
}

bool isBridge(int from, int to){
	return bridge.find({min(from,to),max(from,to)}) != bridge.end();
}
bool vis[MAXN];
vector<pi> street;
void dfs(int at)
{
	if (vis[at]) return;
	vis[at] = true;
	for (int adj:graph[at])
		{
			street.push_back({at,adj});
			graph[adj].erase(at);
			dfs(adj);
		}
}
int main()
{
	cin>>n>>m;
	int caseN = 1;
	while (n != 0 && m != 0)
	{
		int from,to;
		for (int i = 0; i < n; i++) graph[i].clear();
		for (int i = 0; i < m; i++)
		{
			cin>>from>>to;
			from--; to--;
			graph[from].insert(to);
			graph[to].insert(from);
		}
		
		bridge.clear();
		memset(num,0,sizeof num);
		memset(low,0,sizeof low);
		memset(p,-1,sizeof p);
		memset(vis,0,sizeof vis);
		att = 0;
		street.clear();
		for (int i = 0; i < n; i++)
			if (num[i] == 0)
			{	at_root = i;
				child_root = 0;
				find_art_bridge(i);
				if ( child_root> 1) art_point[i] = true;
			}
		
		
		set<pi>res;
		
		for (pi i: bridge)
			res.insert({i.first+1,i.second+1}),
			res.insert({i.second+1,i.first+1});
		
		
		for (pi i: bridge){
			graph[i.first].erase(i.second);
			graph[i.second].erase(i.first);
		}
		for (int i = 0; i < n; i++)
			if (art_point[i]) dfs(i);
			
		for (pi i: street)
			res.insert({i.first+1,i.second+1});

		cout<<caseN++<<"\n\n";
		for (pi i: res)
			cout<<i.first<<" "<<i.second<<"\n";
			
		cout<<"#\n";
		cin>>n>>m;
	}
}
