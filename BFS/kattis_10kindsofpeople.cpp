#include <bits/stdc++.h>
//g++    -std=c++11 -o main main.cxx  -Wno-deprecated-declarations
using namespace std;
typedef pair<int, int> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 1010
vector<string> mat;
int color[MAXN][MAXN];
int att_color;
int dr[] = {-1,0,1,0};
int dc[] = {0,1,0,-1};
int R,C;
void  bfs(int st_r,int st_c){
	if (color[st_r][st_c] != 0) return;
	att_color++;
	char allowed = mat[st_r][st_c];

	queue<pi> coda;
	coda.push({st_r,st_c});

	while (!coda.empty()){
		pi att = coda.front(); coda.pop();
		int r = att.first, c = att.second;
		if (r < 0 || r >= R || c < 0 || c >= C) continue; 
		if (mat[r][c] != allowed) continue;
		if (color[r][c] == att_color) continue;
		color[r][c] = att_color;

		for (int i = 0; i < 4; i++)
			coda.push({r+dr[i],c+dc[i]});
	}
}
int main()
{
	ios::sync_with_stdio(0);
	cin >>R>>C;
	mat.resize(R);
	for (auto & s: mat)
		cin>>s;
	int N; cin >> N;
	while (N--){
		int st_r,st_c,end_r,end_c;
		cin>>st_r>>st_c>>end_r>>end_c;
		st_r--,st_c--,end_r--,end_c--;
		bfs(st_r,st_c);
		if (color[st_r][st_c] == color[end_r][end_c]){
			if (mat[st_r][st_c] == '0') cout<<"binary"<<endl;
			else cout<<"decimal"<<endl;
		} else cout<<"neither"<<endl;
	}

	return 0;
}
