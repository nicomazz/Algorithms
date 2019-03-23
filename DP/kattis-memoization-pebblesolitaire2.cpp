#include <bits/stdc++.h>
//g++    -std=c++11 -o main main.cxx  -Wno-deprecated-declarations
using namespace std;
typedef pair<int, int> pi;
typedef pair<int, pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 200100

int memo[1<<24];

const int N = 23;

int bit(int n, int i){
	return n & (1<<i);
}
int set_bit(int n, int i, int s){
	if (s)
		return n | (1<<i);
	return n & ~(1<<i);
}
int cnt_bit(int n){
	int cnt = 0;
	for (int i = 0; i < N; i++)
		if (bit(n,i)) cnt++;
	return cnt;
}
int min_res(int att){
	int & res = memo[att];
	if (res != -1) return res;

	int best_res = cnt_bit(att);
	for (int i = 0; i < N-2; i++){
		if (bit(att,i) && bit(att,i+1) && !bit(att,i+2)){
			int next = att;
			next = set_bit(next,i,0);
			next = set_bit(next,i+1,0);
			next = set_bit(next,i+2,1);
			best_res = min(best_res, min_res(next));
		}
		
		if (bit(att,i+2) && bit(att,i+1) && !bit(att,i)){
			int next = att;
			next = set_bit(next,i,1);
			next = set_bit(next,i+1,0);
			next = set_bit(next,i+2,0);
			best_res = min(best_res, min_res(next));
		}
	}
	return res = best_res;

}
int main() {
   ios::sync_with_stdio(0);
   int N;
   cin >> N;
	memset(memo,-1,sizeof memo);
   for (int n = 0; n < N; n++) {
      string s;
      cin >> s;

		int att = 0;
		for (int i = 0; i < s.size(); i++)
			if (s[i] == 'o')
				att |= (1<<i);

		cout<<min_res(att)<<"\n";

   }
   return 0;
}
