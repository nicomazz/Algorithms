#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 210;

vector<pair<int,int>> rooms;
int N,K;
int dp[MAXN][MAXN][3];

int f(int row = 0, int to_close = K, int prec = 0){
	int rem_row = N-row;
	if (to_close > rem_row) 
		return -2e8;
	
	if (row == N) return 0;

	int & res = dp[row][to_close][prec];
	if (res != 0) return res;

	if (to_close == 0)
		return res = rooms[row].first+rooms[row].second + f(row+1,0,0);

	int best_result = 0;
	//no actions
	best_result = max(best_result, f(row+1,to_close,0)+rooms[row].first+rooms[row].second);
	if (prec != 2) //close left
	  	best_result = max(best_result, f(row+1,to_close-1,1)+rooms[row].second);	
	if (prec != 1) // close right
		best_result = max(best_result, f(row+1,to_close-1,2)+rooms[row].first);

	return res = best_result;	
}

int main(){
	cin>>N>>K;
	rooms.resize(N);
	for (auto & i: rooms) 
		cin>>i.first>>i.second;

	cout<<f();	
	return 0;
}
