#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
ll dist[1010][1010][2][4];
int mat[1010][1010];
int _R,_C;
#define out(_r,_c) ( _r < 0 || _c < 0 || _r >= _R || _c >= _C)
int dr[] = {-1,0,0,1}, dc[] = {0,-1,1,0};
bool purpleMove(int r, int c, int dir )
{
	int nxt_r = r+dr[dir];
	int nxt_c = c+dc[dir];
	return !( out(nxt_r,nxt_c) || mat[nxt_r][nxt_c] == 0 || mat[nxt_r][nxt_c] == 3 );
}
struct state_t{
	int r,c;
	bool smell;
	int dist,dir;
};
int bfs()
{
	queue<state_t> coda;
	coda.push({0,0,0,0});
	while (!coda.empty())
	{
		int r = coda.front().r; int c = coda.front().c;
		bool smell = coda.front().smell;
		int d = coda.front().dist; int dir = coda.front().dir;
		coda.pop();
		if (out(r,c))continue;
		if ( r == _R-1 && c == _C-1) return d;
		if (mat[r][c] == 0) continue; // celle rosse
		else if (mat[r][c] == 3 && !smell) continue; // celle blu
		else if (mat[r][c] == 2) smell = true; // celle orange
		else if (mat[r][c] == 4) {// se riusciamo andiamo avanti
			if (purpleMove(r,c,dir)){
				coda.push({r+dr[dir],c+dc[dir],0,d+1,dir});
				continue;
			} smell = false;}
		if ( dist[r][c][smell][0] == -1) dist[r][c][smell][0] = d;
		else if ( dist[r][c][smell][0] <= d) continue;
		dist[r][c][smell][0] = d;
		
		for (int i = 0; i < 4; i++) coda.push({r+dr[i],c+dc[i],smell,d+1,i});
	} return -1;
}
int main(){
	freopen("dream.in","r",stdin);
	freopen("dream.out","w",stdout);
	ios::sync_with_stdio(false);
	memset(dist,-1,sizeof dist);
	cin>>_R>>_C;
	for (int i = 0; i < _R; i++)
	for (int j = 0; j < _C; j++)
		cin>>mat[i][j];
	cout<<bfs();
}
