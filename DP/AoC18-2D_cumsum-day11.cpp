#include <bits/stdc++.h>
//g++    -std=c++11 -o main main.cxx  -Wno-deprecated-declarations
using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 310 
const int SERIAL = 9435;

int val(int x, int y){
	int rack_id = x+10;
	int power_level = rack_id*y;
	power_level += SERIAL;
	power_level *= rack_id;
	power_level = (power_level /100 )% 10;
	power_level-= 5;
	return power_level;

}
/**
 * START CUM_SUM
 * */
int N=301,M=301;
int H,W;

ll m[MAXN][MAXN];
ll cum[MAXN][MAXN];

void build()
{
	// cumulate
	for (int  i = 0; i < N; i++)
		cum[i+1][1] = m[i][0]+cum[i][1];
	for (int i = 0; i < M; i++)
		cum[1][i+1] = m[0][i]+ cum[1][i];

	for (int  i = 2; i <= N; i++)
		for (int j = 2; j <= M; j++)
			cum[i][j] = m[i-1][j-1] + cum[i-1][j] + cum[i][j-1] -cum[i-1][j-1];
}
ll getVal(int r1,int c1, int r2, int c2)
{
	return cum[r2][c2]-cum[r1][c2]-cum[r2][c1]+cum[r1][c1];
}
ll getVal(int r,int c,int sz)
{
	return getVal(r,c,r+sz,c+sz);
}
/**
 *	END_CUM_SUM
 * */
int main()
{
	ios::sync_with_stdio(0);

	for (int i = 1; i <= 300; i++)
		for (int j = 1; j <= 300; j++){
			m[i][j] = val(i,j);
		}
	build();
	ll max_value = -2e8; ll max_x,max_y,best_sz;

	for (int x = 1; x <= 300; x++){
		for (int y = 1; y <= 300; y++){
			for (int sz = 1; sz <= 300-max(x,y)+1; sz++){
				ll att_sum = getVal(x,y,sz);
				if (att_sum > max_value){
					max_value = att_sum;
					max_x = x; max_y = y;
					best_sz = sz;
				}
			}
		}
	}
	cout<<"best_power: "<<max_value<<"\n";
	cout<<max_x<<","<<max_y<<","<<best_sz<<endl;
	return 0;
}
//20,41
//236,270,11

