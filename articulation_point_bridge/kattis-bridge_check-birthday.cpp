#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef vector<pi> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 10100

int n, m;
vector<int> graph[MAXN];
int num[MAXN], low[MAXN];
int p[MAXN];
int att;

set<pi> bridge;
void find_bridge(int i) {
   num[i] = low[i] = ++att;
   for (auto& adj : graph[i]) {
      if (num[adj] == 0) {
         p[adj] = i;
         find_bridge(adj);
         if (num[i] < low[adj]) bridge.insert({min(i, adj), max(i, adj)});
         low[i] = min(low[i], low[adj]);
      } else if (p[i] != adj)
         low[i] = min(low[i], num[adj]);
   }
}
int main() {
   int P, C;

   while (cin >> P >> C && (P != 0 || C != 0)) {
      for (int i = 0; i < P; i++)
         graph[i].clear();

      for (int i = 0; i < C; i++) {
         int f, t;
         cin >> f >> t;
         graph[f].push_back(t);
         graph[t].push_back(f);
      }
      bridge.clear();
      memset(num, 0, sizeof num);
      memset(low, 0, sizeof low);
      memset(p, -1, sizeof p);
      att = 0;
      for (int i = 0; i < P; i++)
         if (num[i] == 0) find_bridge(i);

      if (bridge.size() == 0)
         cout << "No\n";
      else
         cout << "Yes\n";
   }
   return 0;
}

