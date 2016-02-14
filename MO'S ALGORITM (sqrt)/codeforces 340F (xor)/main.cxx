#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define MAXN 	200100
#define MAXNi 	10000100 // ATTENZIONE A IMPOSTARE QUESTO! CI HO PERSO UN ORA
#define SP 	1000

int v[MAXN];
struct q_t
{	int l, r, i;
	bool operator<(const q_t & b) const{	
		return ( l/SP == b.l/SP ? r<b.r : l<b.l);
	}
};
q_t q[MAXN];
int sum[MAXNi];
ll res;
int k;
ll ans[MAXN];
void add(ll val)
{	res += sum[val^k];
	sum[val]++;
}
void remove(ll val)
{	sum[val]--;
	res -= sum[val^k];
}
int main()
{	ios::sync_with_stdio(0);
	int N,T; cin>>N>>T>>k;
	for (int i = 1; i <= N; i++)cin>>v[i], v[i] ^= v[i-1];
	for (int i = 0; i < T; i++) cin>>q[i].l>>q[i].r, q[i].i = i;
	sort(q, q+T);
	int l = 0 , r = 0;
	sum[0] = 1;
	for (int i = 0; i < T; i++)
	{
		int da  = q[i].l-1;
		int a = q[i].r;
		while ( r < a) add(v[++r]);
		while ( r > a) remove(v[r--]);
		while ( l < da) remove(v[l++]);
		while ( l > da) add(v[--l]);
	
		ans[q[i].i] = res;
	}
	for (int i = 0; i < T; i++) cout<<ans[i]<<"\n";
	
}
