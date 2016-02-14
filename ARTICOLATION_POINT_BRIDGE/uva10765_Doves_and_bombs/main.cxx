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
int art_point[MAXN];
int num[MAXN], low[MAXN];
int p[MAXN];
int att;
int child_root;
void find_art_point(int i)
{
	num[i] = low[i] = ++att;
	for (auto& adj: graph[i])
	{
		if ( adj == p[i])continue;
		if ( num[adj] == 0) // mai visitato
		{
			if ( i == 0) child_root++;
			p[adj] = i; find_art_point(adj);
			if ( low[adj]  >= num[i] ) // va solo giù
				art_point[i]++;
			low[i] = min(low[i],low[adj]);
		}
		else // già visitato
			low[i] = min(low[i],num[adj]);
	}
}
struct res_t
{
	int n,p;
	bool operator<(const res_t & b)const
	{
			if (b.p == p) return n < b.n;
			return b.p < p;
	}
};
int main()
{	ios::sync_with_stdio(0);

	cin>>n>>m;
	while ( n != 0 && m != 0)
	{
		for (int i = 0; i < n; i++) graph[i].clear();
		
		int a,b;cin>>a>>b;
		while ( a != -1)
		{
			graph[a].push_back(b);
			graph[b].push_back(a);
			cin>>a>>b;
		}
		memset(num,0,sizeof num);
		memset(low,0,sizeof low);
		memset(p,-1,sizeof p);
		memset(art_point,0,sizeof art_point);
		att = 0;
		child_root = 0;
		
		find_art_point(0);
		art_point[0] = child_root-1;
		
		vector<res_t> result;
		for (int i = 0; i < n; i++)
			result.push_back({i,art_point[i]+1});
		
		sort(result.begin(),result.end());
		
		for (int i = 0; i < m; i++)
			cout<<result[i].n<<" "<<result[i].p<<"\n";
		cout<<"\n";
			
		cin>>n>>m;
	}
}
