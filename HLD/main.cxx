#include <bits/stdc++.h>

using namespace std;
#define MAXN 100100

vector<int> tree[MAXN];

int chain[MAXN]; // i-esimo nodo è nella catena chain[i]
int head[MAXN]; 
int start[MAXN]; // inizio e fine della catena i-esima
int _end[MAXN];
int c_parent[MAXN]; // catena sopra di questa (-1 se root)
int order[MAXN]; // ordine nell'array dove si farà rmq
int inx_order;
int node_sz[MAXN]; // somma dei suoi figli ( lui compreso ) 
int p[MAXN];
int chainInx;

int t_in[MAXN], t_out[MAXN];
int _time;
// per RMQ o quel si voglia
int start_val[MAXN];
int rmq[MAXN*3];
//1. chiamare dfs_size
//2. chiamare semiSort su ogni nodo
//3. chiamare buildChain su Radice
void clear_all()
{
	p[0] = -1;
	inx_order = 0;
	chainInx = 0;
	_time = 0;
	memset(node_sz,0,sizeof node_sz);
}
int dfs_size(int r){
	t_in[r] = ++_time;
	node_sz[r]++;
	for (int adj:tree[r])
		if (adj != p[r])
			p[adj] = r, node_sz[r] += dfs_size(adj);
	t_out[r] = ++_time;
	return node_sz[r];
}
bool ancestor(int a , int b){ // a è ancestor di b?
	return t_in[a] < t_in[b] && t_out[b] < t_out[a];
}
void semiSort(int node){ //porta il nodo con maggiori successori al posto 0
	if (node_sz[node] == 1) return;
	int best = -1, i = 0;
	for (int adj: tree[node]){
		if (adj == p[node]){i++; continue;}
		if ( best == -1) best = i;
		if (  node_sz[adj] > node_sz[tree[node][best]] )
			best = i;
		i++;
	}
	swap(tree[node][0],tree[node][best]);
}
void buildChain(int root, int p_catena);
void continueMasterChain(int root)
{
	//cerr<<"continuo catena "<<chainInx<<" su "<<root<<"\n";
	int main_chain = chainInx;
	chain[root] = chainInx;
	order[inx_order++] = start_val[root]; 

	if (node_sz[root] == 1){ // è una foglia? finiamo la catena
		_end[chainInx] = inx_order;
		return;
	}
	continueMasterChain(tree[root][0]);
	for (int i = 1; i < tree[root].size(); i++){
		int adj = tree[root][i];
		if (adj == p[root])continue;

		buildChain(adj,main_chain);
	}
}
void buildChain(int root, int p_catena = -1)
{
	chainInx++;
	int main_chain = chainInx;
	c_parent[chainInx]  = p_catena; // catena sopra di questa
	head[chainInx] = root; // testa
	chain[root] = chainInx; // catena di questo nodo
	order[inx_order] = start_val[root]; 
	start[chainInx] = inx_order;
	inx_order++;
	
	//cerr<<"start chain: "<<chainInx<<"\n";
	if (node_sz[root] == 1) // è una foglia? finiamo la catena
	{
		_end[chainInx] = inx_order;
		return;
	}
	continueMasterChain(tree[root][0]); // master chain
	for (int i = 1; i < tree[root].size(); i++){
		int adj = tree[root][i];
		if (adj == p[root])continue;
		buildChain(adj,main_chain);
	}
}

int LCA(int a, int b)
{
	if ( chain[a] == chain[b]) return (t_in[a] < t_in[b] ? a:b);
	if ( ancestor(a,b)) return a;
	if ( ancestor(b,a)) return b;
	// mandiamo su a finchè l'head della sua catena è ancestor di b:
	int t_chain = chain[a];
	int prev_to_chain = a;
	while (!ancestor(head[t_chain],b))
	{	prev_to_chain = head[t_chain];
		t_chain = chain[p[head[t_chain]]];
	}
	// ora si va su da b finchè si trova la catena t_chain
	
	int b_chain = chain[b];
	/*if ( b_chain == t_chain) // già a posto
		return p[prev_to_chain];*/
	
	int prec_rap = b;
	while (b_chain != t_chain){		
		prec_rap = head[b_chain];
		b_chain = chain[p[head[b_chain]]];
	}

	
	if ( ancestor(p[prev_to_chain],b))
		return p[prev_to_chain];
	if ( ancestor(p[prec_rap],a))
		return p[prec_rap];
	return a;
}
int main()
{
	int T;cin>>T;
	int caseN= 1;
	while (T--)
	{
		cout<<"Case "<<caseN++<<":\n";
		int N; cin>>N;
		int n,da,a;
		for (int i = 0; i < N; i++) tree[i].clear();
		for (int i = 0; i < N; i++)
		{	
			cin>>n;
			for (int j = 0; j < n; j++)
				cin>>a, tree[i].push_back(a-1);
		}
		p[0] = -1;
		inx_order = 0;
		chainInx = 0;
		_time = 0;
		memset(node_sz,0,sizeof node_sz);
		
		dfs_size(0);
		
		for(int i = 0; i < N; i++) semiSort(i);
		for(int i = 0; i < N; i++) start_val[i] = i;
		
		
		buildChain(0);
		
		int c; cin>>c;
		for (int i = 0; i < c; i++)
			cin>>da>>a, cout<<LCA(da-1,a-1)+1<<"\n";
		
	}
	/*cerr<<"ordine: \n";
	for (int i = 0; i < inx_order; i++) cerr<<order[i]<<" ";
	cerr<<"\nper catena: \n";
	for (int i = 0; i < inx_order; i++) cerr<<chain[i]<<" ";

	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		cerr<<"LCA("<<i<<","<<j<<") -> "<<LCA(i,j)<<"\n";*/
		
	return 0;
}/*
14
0 1 
0 2
0 3
2 10
2 11
10 13
10 12
3 6
3 5
3 4
4 7
7 9
7 8
*/
