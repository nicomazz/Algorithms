#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define MAXN 100010

const int base = 107;
const ll MOD = 1000000007;
ll molt[MAXN];
string ss[20];
bool deleted[20];
int _N;
int gr[20][20];

int dp[1<<20][20];
bool look[1<<20][20];

int travel(int bitmask, int last) // 1 da fare
{

    if ( bitmask == 0) return 0;
    //if ( look[bitmask][last]) return dp[bitmask][last];
    look[bitmask][last] = true;
    int res = 2e8;
    for (int i = 0; i < _N; i++)
        if (i != last && (bitmask & (1<<i)))
            res = min(res,(int) ( ss[i].size() + gr[last][i] + travel(bitmask & (~(1<<i)),i)));
    return dp[bitmask][last] = res;
}
void unisci(int ia, int ib)
{
    if (deleted[ia] || deleted[ib]) return;
    string & a = ss[ia];
    string & b = ss[ib];
    //cerr<<"a: "<<a<<" b: "<<b<<"\n";
    int m = min(a.size(),b.size());

    ll h1 = 0, h2 = 0;

    int Max_match = 0;
    for (int i = 0; i < m; i++)
    {
        h1 = (h1 + a[a.size()-1-i] * molt[i]) % MOD;
        h2 = (((h2*base) % MOD) + b[i]) % MOD;
        if ( h1 == h2) Max_match = i+1;
    }
//cerr<<"match: "<<Max_match<<"\n";
    if (Max_match == m) // una dentro l'altra, o uguali
    {
        if (b.size() == m) deleted[ib] = true;
        else deleted[ia] = true;
        return;
    }
    gr[ia][ib] = -(Max_match);
}
int resolve(int N)
{
    molt[0] = 1;
    for (int i = 1; i < MAXN; i++)
        molt[i] = (molt[i-1]*base) % MOD;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        if ( i != j)
            unisci(i,j);

    int start_bitmask = 0;
    for (int i = 0; i < N; i++)
        if(!deleted[i])
            start_bitmask |= (1<<i);


    _N = N;

    int minim = 2e8;
    for (int i = 0; i < N; i++) if (!deleted[i]) minim = min(minim,(int)(ss[i].size() + travel(start_bitmask & (~(1<<i)),i)));
    return minim;
}
int main()
{
  int N; cin>>N;
  for (int i = 0; i < N; i++)
        cin>>ss[i];
cout<<resolve(N);
  return 0;
}
