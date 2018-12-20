#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 200100

struct el_t {
   int c, t;
   bool operator<(const el_t& b) const {
      return t < b.t;
   }
};
el_t v[MAXN];
int N, T;
int dp[MAXN][50];
int f(int i, int t) {
   if (i > N) return 0;
   int& res = dp[i][t];
   if (res != -1) return res;
   if (t > v[i].t)
      return res = f(i + 1, t);

   return res = max(v[i].c + f(i + 1, t + 1), f(i + 1, t));
}
int main() {
   ios::sync_with_stdio(0);
   cin >> N >> T;
	memset(dp,-1,sizeof dp);
   
	for (int i = 0; i < N; i++)
      cin >> v[i].c >> v[i].t;

   sort(v, v + N);

   cout << f(0, 0);

   return 0;
}
