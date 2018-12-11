#include <bits/stdc++.h>
//g++    -std=c++11 -o main main.cxx  -Wno-deprecated-declarations
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 10100
struct arc_t {
   int to, w;
};

int dist[MAXN];
vector<arc_t> gr[MAXN];

void sssp(int start) {
   priority_queue<pi> coda;
   coda.push({0, start});
   memset(dist, -1, sizeof dist);
   dist[start] = 0;
   while (!coda.empty()) {
      pi att = coda.top();
      coda.pop();
      int node = att.second;
      int d = -att.first;
      if (dist[node] < d) continue;
      for (arc_t& a : gr[node]) {
         int new_dist = (d + a.w);
         if (dist[a.to] == -1 || dist[a.to] > new_dist) {
            dist[a.to] = new_dist;
            coda.push({-new_dist, a.to});
         }
      }
   }
}
int main() {
   ios::sync_with_stdio(0);
   int N, M, Q, S;
   while (cin >> N >> M >> Q >> S && N != 0) {
      for (int i = 0; i < MAXN; i++) gr[i].clear();
      int f, t, w;
      for (int i = 0; i < M; i++) {
         cin >> f >> t >> w;
         gr[f].push_back({t, w});
      }
      sssp(S);

      for (int i = 0; i < Q; i++) {
         cin >> t;
         if (dist[t] == -1)
            cout << "Impossible";
         else
            cout << dist[t];
         cout << "\n";
      }
      cout << "\n";
   }

   return 0;
}
