#include <iostream>
#include <cstring>
#define MAXN 81

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;
const int base = 107;
ll molt[MAXN];
ll pref_hash[MAXN];

string s;
void build_pref_hash(){
	pref_hash[0] = s[0];
	for (int i = 1; i < s.size(); i++) pref_hash[i] = (pref_hash[i-1]*base +s[i]) % MOD;
}
ll getHash(int from, int to) //[from,to[
{
	if ( from == 0) return pref_hash[to-1];
	return ((pref_hash[to-1] + MOD*2) - (pref_hash[from-1]*molt[to-from] % MOD)) % MOD;
}

int simple_cmp[MAXN][MAXN];
int simple_compress(int from, int to)
{
	int & res = simple_cmp[from][to];
	if ( res != -1) return res;
	int len = to-from;
	for (int i = 1; i <= len/2; i++) // gruppi di i carateri ripetuti?
	{
		if ( len % i) continue;
		int n_gruppi = len / i;
		ll h_target = getHash(from,from+i);
		bool ok = true;
		for (int j = 1; j < n_gruppi; j++){
			if ( getHash(from+i*j,from+i*j+i) != h_target)
			{ok = false; break;}
		}
		if ( ok == true) return res = i;
	}
	return res = to-from;
}
int dp[MAXN][MAXN];
int f(int from, int to)
{
	int & res = dp[from][to];
	if (res != -1) return res;

	if ( to == from+1) return res = 1; // un carattere
	res = simple_compress(from,to);
	if ( res != to-from) // c'è una periodicità
		return res = min(res,f(from,from+res));
	//if ( to == from+2) return res; // 2 caratteri
	res = 2e8;
	for (int i = from+1; i < to; i++)
		res = min(res,f(from,i)+f(i,to));

	return res;
}
int main()
{
	molt[0] = 1;
	for (int i = 1; i < MAXN; i++)
		molt[i] = (molt[i-1] * base) % MOD;
	while (true)
	{
		cin>>s;
		if ( s == "*") return 0;
		memset(dp,-1,sizeof dp);
		memset(simple_cmp,-1,sizeof simple_cmp);
		build_pref_hash();
		/*for (int i = 1; i < s.size(); i++)
			if ( getHash(0,i) == getHash(i,s.size()))
				cerr<<"mid: "<<i<<"\n";
			*/
		//cout<<simple_compress(0,s.size())<<"\n";
		cout<<f(0,s.size())<<"\n";
	}
	return 0;
}
