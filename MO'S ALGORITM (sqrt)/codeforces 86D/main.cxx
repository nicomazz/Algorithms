#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
typedef unsigned long long ull;

const ll MOD = 1e9 + 7;

#define from first
#define to second
#define MAXN 	200100
#define MAXNi 	1000100
#define split 	2000

ull v[MAXN];
struct q_t
{
	pi q;
	int inx;
	bool operator<(const q_t & b) const
	{	int start_a = q.first / split;
		int start_b = b.q.first / split;
		if ( start_a == start_b ) return q.second < b.q.second;
		return start_a < start_b;
	}
};
q_t querys[MAXN];
ll cnt[MAXNi];
ll power;
// -(val*cnt^2) + (val*(cnt+1)^2)
// -val*cnt*cnt + val*(cnt+1)*(cnt+1)
// val(-(cnt*cnt)+(cnt+1)*(cnt+1))
// val(-2*cnt + 1)

void up(int val,int dt )
{
	power += val*(2*cnt[val]*dt+1);
	cnt[val]+= dt;
}

ll ans[MAXN];
int main()
{
	ios::sync_with_stdio(0);
	int N,T;
	cin>>N>>T;
	for (int i = 0; i < N; i++) cin>>v[i];
	for (int i = 0; i < T; i++) cin>>querys[i].q.from>>querys[i].q.to, querys[i].q.from--, querys[i].q.to--, querys[i].inx = i;
	sort(querys, querys+T);
	//[a,b)
	int _l = 1, _r = 0;
	for (int i = 0; i < T; i++)
	{
		int da  = querys[i].q.from;
		int a = querys[i].q.to;
		
		while (_l < da) up(v[_l++], -1);
		while (_l > da) up(v[--_l], 1);
		while (_r < a) 	up(v[++_r], 1);
		while (_r > a) 	up(v[_r--], -1);
		
		ans[querys[i].inx] = power;
	}
	for (int i = 0; i < T; i++) cout<<ans[i]<<"\n";
	
}
