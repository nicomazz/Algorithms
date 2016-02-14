#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#define MAXT 10000100
int possible[MAXT];
int lp[MAXT];
int main()
{
	freopen("feast.in","r",stdin);
	freopen("feast.out","w",stdout);
	int T,A,B;
	cin>>T>>A>>B;
	possible[0] = true;
	for (int i = 0; i <= T; i++){
		if (!possible[i])continue;
		if (i+A <= T) possible[i+A] = true;
		if (i+B <= T) possible[i+B] = true;
	}
	lp[0] = 0;
	for (int i = 1; i<= T; i++)
	lp[i] = (possible[i] ? i:lp[i-1]);
	
	/*for (int i = 0; i <= 2*T; i++)
	cerr<<lp[i]<<" ";*/
	
	int res = 0;
	for (int i = 0; i <= T; i++)
		if (possible[i])
		{ 
			//cerr<<"verifico per x = "<<i<<" ris -> "<<(i/2 + lp[T-i/2])<<"\n";
			res = max(res,(i/2 + lp[T-i/2]));
		}
	cout<<res;
	
}	
