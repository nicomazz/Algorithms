#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;


/*
 * inizio HASHER
 * */
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;
ll base = 107;
#define MAXN_H 100100
struct stringH{
	static ll molt[MAXN_H]; static bool init;
	string s;
	vector<ll> pref; // HASH PREFISSO
	stringH(string _s){s = _s; build_hash();};
	void build_hash(){
		if (!init) build_molt();
		pref.resize(s.size()); pref[0] = s[0];
		for (int i = 1; i < s.size(); i++) pref[i] = (((pref[i-1] * base) % MOD) + s[i]) % MOD;
	}
	ll get(int from, int to){
		ll res = pref[to-1]; if ( from == 0) return res;
		res =  res+MOD*2- ((pref[from-1] * molt[to-from]) % MOD) % MOD;
		return res % MOD;
	}
	int longest_common_pre(stringH & b){
		int l = 0, h = min(b.s.size(), s.size());
		while (l < h){
			int mid = (l+h)/2;
			if ( get(0,mid) == b.get(0,mid))
				l = mid;
			else h = mid-1;}
		return l;
	}
	void build_molt(){
		init = true;
		molt[0] = 1;
		for (int i =1; i < MAXN_H; i++) molt[i] = (molt[i-1]*base) % MOD;
	}
};
bool stringH::init = false;
ll stringH::molt[] = {};
/**
 * FINE HASHER
 */
 
 
int main()
{
	stringH a("ciaociao");
	cout<<a.get(0,4)<<" "<<a.get(4,8);
	return 0;
}
