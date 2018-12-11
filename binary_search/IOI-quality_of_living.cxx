#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 3010
#define TYPES 4

int N,M;
int H,W;

int mat[MAXN][MAXN];
char m[MAXN][MAXN];
int cum[MAXN][MAXN];

int build(int val_target)
{
	for (int  i = 0; i < N; i++)
	for (int j = 0; j < M; j++)
		if ( mat[i][j] < val_target) m[i][j] = -1;
		else if ( mat[i][j] > val_target) m[i][j] = 1;
		else m[i][j] = 0;

	// cumulate
	for (int  i = 0; i < N; i++)
		cum[i+1][1] = m[i][0]+cum[i][1];
	for (int i = 0; i < M; i++)
		cum[1][i+1] = m[0][i]+ cum[1][i];

	for (int  i = 2; i <= N; i++)
		for (int j = 2; j <= M; j++)
			cum[i][j] = m[i-1][j-1] + cum[i-1][j] + cum[i][j-1] -cum[i-1][j-1];
}
int getVal(int r1,int c1, int r2, int c2)
{
	return cum[r2][c2]-cum[r1][c2]-cum[r2][c1]+cum[r1][c1];
}
int getVal(int r,int c)
{
	return getVal(r,c,r+H,c+W);
}
int getMinVal()
{
	int min_val = 2e8;
	for (int i = 0; i <= N-H; i++)
	for (int j = 0; j <= M-W; j++)
		min_val = min(min_val,getVal(i,j));
	return min_val;
}
int main()
{
	ios::sync_with_stdio(0);
	cin>>N>>M;
	cin>>H>>W;
	int low = 2e8,  high = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < M; j++) 
		cin>>mat[i][j], 
		low = min(low,mat[i][j]),
		high = max(high,mat[i][j]);
		
	while (low <= high)
	{
		int mid = (low+high) / 2;
		build(mid);
		int val_min = getMinVal();
		if ( val_min == 0) {cout<<mid; return 0;}
		
		if ( val_min < 0 ) high = mid-1;
		else low = mid+1;
	}
	
	return 0;
}
