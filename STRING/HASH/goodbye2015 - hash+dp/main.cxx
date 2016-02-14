#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
const ll base = 107;

#define MAXN 5001
string s;
int N;
ll dp[MAXN][MAXN]; // da qui, con al minimo n cifre

ll molt[MAXN];
ll prefH[MAXN];
ll get(int from, int to)
{
	ll res = prefH[to-1];
	if ( from == 0) return res;
	int len = to-from;
	res =  res- ((prefH[from-1] * molt[len]) % MOD) % MOD;
	while(res < 0) res+= MOD;
	return res;
}
int compare(int a,int b, int c, int d) // a-b è >= a c-d 
{
	if (s[a] != s[c]) return s[a] > s[b];
	if ( get(a,b) == get(c,d))return true;
	int len = b-a;
	int l = 0, h = len; int res = 0;
	while ( l <= h)
	{
		int mid = (l+h)/2;
		if ( get(a,a+mid) == get(c,c+mid))
		{
			res = mid;
			l = mid+1;
		}
		else h = mid-1;
	}
	return s[a+res] >= s[c+res];
	/*
	if( b-a != d-c) {cerr<<"ERRORE!!\n"; return false;}	
	for (int i = a, ii = b; i < b; i++,ii++)
	{
		if ( s[i] == s[ii]) continue;
		return s[i] > s[ii];
	}
	return true; // sono uguali*/
}
ll f(int from, int min_c)
{
	//cerr<<"from: "<<from<<" min_c: "<<min_c<<"\n";
	//if (from == N) return 0;
	if (from + min_c > N) return 0; // >= ?
	if (from + min_c == N) return 1; // perfetto
	int rem_space = N-(from+min_c);
	if (rem_space < min_c) return 1; // prendo tutto
	
	ll & res = dp[from][min_c];
	if ( res != -1) return res;
	
	res = 0;
	
	int to = from+min_c;
	if ( s[to] == '0') return res = (f(from,min_c+1) % MOD); // facciamo partire dopo
	
	int att_len = to-from;
	int next_len = att_len; // +1 ??
	if (to+next_len > N) return 1; // raggiunta len massima di già, tutto il resto con questo
	bool to_add = compare(from,to,to,to+att_len);
	if ( to_add) next_len++;
	res = (res + f(to,next_len)) % MOD;
	res = (res + f(from,min_c+1)) % MOD;
	
	return res;
	
}

int main()
{
	molt[0] = 1;
	for (int i =1; i < MAXN; i++) molt[i] = (molt[i-1]*base) % MOD;
	ios::sync_with_stdio(0);
	cin>>N;
	cin>>s;
	prefH[0] = s[0];
	for (int i = 1; i < N; i++) prefH[i] = (((prefH[i-1] * base) % MOD) + s[i]) % MOD;
	memset(dp,-1,sizeof dp);
	cout<<f(0,1);
	return 0;
}
