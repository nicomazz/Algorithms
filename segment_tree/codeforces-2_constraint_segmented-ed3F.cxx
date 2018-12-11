#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 200100
int n,m;
struct frog_t{int pos;ll l; int inx;
	bool operator<(const frog_t & b)const 
	{return pos < b.pos;}
};
struct mosc_t{int pos; ll size;
	bool operator<(const mosc_t & b)const 
	{return pos < b.pos;}
};

frog_t frogs[MAXN];
int eaten[MAXN];
int l_final[MAXN];
multiset<mosc_t> moscs;
/**
 * tree
 * */
ll max_dx[MAXN*3]; // massimo a destra per il range
ll arr(int inx) {return frogs[inx].pos+frogs[inx].l;}
void build(int a= 0, int b= n, int inx = 1)
{
	if ( b == a+1){
		max_dx[inx] = a;return;}
	int mid = (a+b) / 2;
	build(a,mid,inx*2);
	build(mid,b,inx*2+1);
	if ( arr(max_dx[inx*2]) > arr(max_dx[inx*2+1]))
		max_dx[inx] = max_dx[inx*2];
	else max_dx[inx] = max_dx[inx*2+1];
}
//prima bisogna modificare frogs[a].l
void update(int a, int from = 0, int to = n, int inx = 1)
{
	if ( a < from || a >= to) return;
	if ( from == to-1) return;
	int mid = (from+to) / 2;
	update(a,from,mid,inx*2);
	update(a,mid,to,inx*2+1);
	if ( arr(max_dx[inx*2]) > arr(max_dx[inx*2+1]))
		max_dx[inx] = max_dx[inx*2];
	else max_dx[inx] = max_dx[inx*2+1];
}
// da 0 a max_to, indice con arr(inx) >= mag_di
int query(int mag_di, int t_from, int t_to, int from = 0, int to= n, int inx = 1)
{
	if ( to <= from) return -1;
	if ( arr(max_dx[inx]) < mag_di)return -1;
	// non interseca
	if ( t_from >= to || from >= t_to) return -1;
	if (from == to-1) return max_dx[inx];
	int mid = (from+to) / 2;
	if ( arr(max_dx[inx*2]) >= mag_di)
		return query(mag_di,t_from,t_to,from,mid,inx*2);
	if ( arr(max_dx[inx*2+1]) >= mag_di)
		return query(mag_di,t_from,t_to,mid,to,inx*2+1);
	return -1;
}

/**
 * fine tree
 * */
 
void eateateat(int inx)
{
	bool one = true;
	while (one)
	{
		mosc_t dummy = {frogs[inx].pos,-1};
		ll to_add = 0;
		one = false;
		while (true){
			multiset<mosc_t>::iterator it = moscs.lower_bound(dummy);
			if (it != moscs.end() && it->pos <= frogs[inx].pos+frogs[inx].l)
				to_add += it->size;
			else break;
			one = true;
			moscs.erase(it);
			eaten[frogs[inx].inx]++;
		}
		frogs[inx].l += to_add;
		update(inx);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin>>n>>m;
	for (int i = 0; i < n; i++)
		cin>>frogs[i].pos>>frogs[i].l, frogs[i].inx = i;
	sort(frogs,frogs+n);
	mosc_t tmp;
	build();
	for (int i = 0; i < m; i++)
	{
		cin>>tmp.pos>>tmp.size;
		frog_t dummy = {tmp.pos};
		int fino_inx = upper_bound(frogs,frogs+n,dummy)-frogs;
		//più a sx che può mangiare:
		int inx_piu_sx = query(tmp.pos,0,fino_inx);
		//cerr<<"inx_piu_sx = "<<inx_piu_sx<<"\n";
		if (inx_piu_sx == -1){
			moscs.insert(tmp);
			continue;
		}
		//mangiamola
		eaten[frogs[inx_piu_sx].inx]++;
		frogs[inx_piu_sx].l += tmp.size;
		update(inx_piu_sx);
		eateateat(inx_piu_sx);
	}
	for (int i = 0; i < n; i++)
		l_final[frogs[i].inx] = frogs[i].l;
	
	for (int i = 0; i < n; i++)
		cout<<eaten[i]<<" "<<l_final[i]<<"\n";
	
	return 0;
}
