#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 100001
#define TYPES 4

#define t1 3  	// 0011
#define t2 12 	// 1100
#define mask 15 // 1111
//int dp[MAXN][1<<4][1<<4];
int N; char val[MAXN];

int different(int p, int c)
{
	int a = p & t1; 		// prec_1
	if ( a == 0) // non c'è precedente
		return 1;
	int b = (p>>2) & t1; 	// prec_2 
	if ( b == 0) // non ce ne sono 2 di precednti
		return  a == c ? 1:2;
	return (a == b? (b==c? 1:2):(b==c || a == c ?2:3));
}
int add_val(int p, int c)
{
	int res = (p<<2)&mask;
	return res + c;
}

int to[300];
int Bdp[2][1<<8];
int main()
{
	ios::sync_with_stdio(0);
	cin>>N;
	to['M'] = 1; to['B'] = 2; to['F'] = 3;
	char c;
	for (int i = 0; i < N; i++)
		cin>>c, val[i] = to[c];
	
	for (int I = N-1; I >= 0; I--)
	{
		int i = I & 1;
		for (int j = 0; j < 1<<8; j++)
		{	char p1 = (j & 15);
			char p2 = (j >>4);
			// al primo:
			int v1 = different(p1,val[I]) + Bdp[i^1][add_val(p1,val[I])|(p2<<4)];
			// al secondo
			int v2 = different(p2,val[I]) + Bdp[i^1][p1|(add_val(p2,val[I])<<4)];
			Bdp[i][j] = max(v1,v2);
		}
	}
	cout<<Bdp[0][0];
	return 0;
}
