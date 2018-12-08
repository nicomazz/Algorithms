#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 200100
struct arc_t
{
	int from,to;
	int cost;
	int inx;
	bool operator<(const arc_t & b) const
	{	return cost < b.cost;}
};
vector<arc_t> tree[MAXN];
vector<arc_t> arcs;
vector<arc_t> MST[MAXN];
ll p[MAXN][20];
ll max_p[MAXN][20];
int t_in[MAXN];
int t_out[MAXN];
int t_att;
int N,M;

int dsu[MAXN];
int Find(int n){ return dsu[n] == n? n: dsu[n] = Find(dsu[n]);}
int same(int a,int b) {return Find(a) == Find(b);}
int Union(int a,int b) {dsu[Find(a)] = dsu[Find(b)];}

bool in_mst[MAXN];
ll compute_MST()
{
	ll sum = 0;
	for (arc_t & arc: arcs)
	{
		int a = arc.from;
		int b = arc.to;
		if ( same(a,b)) continue;
		Union(a,b);
		MST[a].push_back({a,b,arc.cost});
		MST[b].push_back({b,a,arc.cost});
		in_mst[arc.inx] = true;
		sum += arc.cost;
	}
	return sum;
}
void build_structure()
{
	for (int i = 1; i < 20; i++)
	for (int j = 0; j < N; j++)
		p[j][i] = p[p[j][i-1]][i-1];
		
	for (int i = 1; i < 20; i++)
	for (int j = 0; j < N; j++)
		max_p[j][i] = max(max_p[j][i-1], max_p[p[j][i-1]][i-1]);
}
bool ancestor(int a,int b){ // a è un parente in alto di b?
	return t_in[a] < t_in[b] && t_out[b] < t_out[a];
}
int LCA(int a, int b)
{
	if ( ancestor(a,b)) return a;
	if ( ancestor(b,a)) return b;
	
	// mandiamo su a il più possibile
	for (int i = 19; i >= 0; i--)
	{
		if ( p[a][i] == -1) continue;
		if ( !ancestor(p[a][i],b))
			a = p[a][i];
	}
	return p[a][0];
}
void dfs(int att)
{
	t_in[att] = t_att++;
	for (arc_t & arc: MST[att])
		if ( arc.to != p[att][0])
			p[arc.to][0] = att,
			max_p[arc.to][0] = arc.cost,
			dfs(arc.to);
	t_out[att] = t_att++;
}
int max_in_path(int a, int lca) // a stà giu
{
	ll resp = -1;
	// mandiamo su a il più possibile
	for (int i = 19; i >= 0; i--)
	{
		if ( p[a][i] == -1) continue;
		if ( !ancestor(p[a][i],lca))
			resp = max(resp,max_p[a][i]),
			a = p[a][i];
	}	
	return resp;
}
ll _ris[MAXN];
int main()
{
	ios::sync_with_stdio(0);
	cin>>N>>M;
	int da,a,c;
	for (int i = 0; i < M; i++)
	{
		cin>>da>>a>>c;
		da--;
		a--;
		tree[da].push_back({da,a,c});
		tree[a].push_back({a,da,c});
		arcs.push_back({da,a,c,i});
	}
	sort(arcs.begin(),arcs.end());
	for (int i = 0; i < N; i++) dsu[i] = i;
	ll mst_sum = compute_MST();
	
	p[0][0] = -1;
	dfs(0);
	build_structure();
	
	for (arc_t arc : arcs)
	{
		if ( in_mst[arc.inx]) 
			_ris[arc.inx] = mst_sum;
		else 
		{ // troviamo quello che ha somma maggiore da a a b
			int a = arc.from;
			int b = arc.to;
			int lca = LCA(a,b);
			int max_edge = max(max_in_path(a,lca),max_in_path(b,lca));
			_ris[arc.inx] = mst_sum+arc.cost-max_edge;
		}
	}
	for (int i = 0; i < M; i++)
		cout<<_ris[i]<<"\n";
	
	return 0;
}
