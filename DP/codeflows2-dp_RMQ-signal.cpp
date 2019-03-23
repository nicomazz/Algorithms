#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef long long ll;

#define MAXN 20010000

vector<ll> W;
vector<pi> ranges;
vector<ll> dp;
vector<ll> tree;
bool visited[MAXN];
int N;

void build(int l, int r, int inx) {
   if (visited[inx]) return;
   if (l == r - 1) {
      tree[inx] = dp[l] + W[l];
      visited[inx] = true;
      return;
   }
   int mid = (l + r) / 2;
   build(l, mid, inx * 2);
   build(mid, r, inx * 2 + 1);
   tree[inx] = min(tree[inx * 2], tree[inx * 2 + 1]);
   visited[inx] = true;
}

// tl: target left, tr: target right, l-r: actual left and right
// min value for W[i]+dp[i] in the range [l,r)
ll getMin(int tl, int tr, int l = 0, int r = N, int inx = 1) { 

   // outside
   if (tr <= l || tl >= r)
      return LLONG_MAX;

   // inside
   if (tl <= l && tr >= r) {
      if (visited[inx] == false)
         build(l, r, inx);
      return tree[inx];
   }

   int mid = (l + r) / 2;
   return min(getMin(tl, tr, l, mid, inx * 2), getMin(tl, tr, mid, r, inx * 2 + 1));
}

// cost to send from 0 and receive in i
ll f(int i) {
   if (i == 0) return 0;
   if (dp[i] != 0) return dp[i];
   // RMQ on interval
   ll best_res = getMin(ranges[i].first, ranges[i].second + 1);
   return dp[i] = best_res;
}

int main() {
   ios::sync_with_stdio(0);
   int T;
   cin >> T;
   while (T--) {

      // offices
      cin >> N;
      W.resize(N); tree.resize(N * 10); ranges.resize(N); dp.resize(N);
      memset(visited, 0, sizeof visited); dp.clear(); 

      for (int i = 0; i < N - 1; i++) cin >> W[i];
      for (int i = 1; i < N; i++) {
         cin >> ranges[i].first >> ranges[i].second;
         ranges[i].first--; ranges[i].second--;
      }
     
      for (int i = 1; i < N; i++) 
         cout << f(i) << " ";
      
      cout << "\n";
   }
   return 0;
}

