#include <bits/stdc++.h>

using namespace std;

#define MAXN 2000010

typedef pair<long long, long long> pii;
typedef pair<int,pii> piii;
typedef vector<int> vii;
typedef priority_queue<int,vii,greater<int> > priority_min_first;
typedef priority_queue<float,vii,greater<float> > priority_min_first_f;
typedef  long long ll;

struct fenwick {
	ll v[MAXN];
	int size;
	fenwick(int size){
		this->size = size;
		memset(v,0,sizeof v);
	}
	
	void update(int pos, ll dt){
		for (int i = pos; i < size; i += i & (-i))
			v[i]+= dt;
	}
	ll get_0_to(int x){
		ll sum = 0;
		for (int i = x; i ; i -= i& (-i))
			sum+= v[i];
		return sum;
	}
	ll get(int from, int to){ // estremi inclusi!
		return get_0_to(to) - get_0_to(from-1);
	}
};

fenwick andata(MAXN);
fenwick andata_count(MAXN);
fenwick ritorno(MAXN);
fenwick ritorno_count(MAXN);
set<pii> fly[MAXN][2]; // sescond == cost, first == day
#define ANDATA 0
#define RITORNO 1
int N,M,K;
int MAX_DAY;

struct rit_fly_t{
	int _day, _cost, to;
};
vector<rit_fly_t> rit_fly;

int transform_day(int day){
	return (MAX_DAY+1)-day;
}

void addFly(int from, int to, int day, int cost){
	if (to == 0)
		fly[from][ANDATA].insert({day,cost});
	else 
		rit_fly.push_back({day,cost,to});
	MAX_DAY = max(MAX_DAY, day);
}
#define cost second 
#define  day first

void elaborateAndataFly(){
	for (int city = 1; city <= N; city++){
		pii min_fly = {0,0};
		for ( auto   aFly : fly[city][ANDATA]){
			if (min_fly.day == 0){
				min_fly = aFly;
				andata.update(aFly.day,aFly.cost);
				andata_count.update(aFly.day,1);
				continue;
			}
			if (aFly.cost < min_fly.cost){
				andata.update(aFly.day,-min_fly.cost);
				andata.update(aFly.day,aFly.cost);
				min_fly = aFly;
			}
		}
	}
}
void elaborateRitornoFly(){
	for (rit_fly_t & aFly: rit_fly){
		fly[aFly.to][RITORNO].insert({transform_day(aFly._day),aFly._cost});
	}
	for (int city = 1; city <= N; city++){
		pii min_fly = {0,2e8};
		for ( auto   aFly : fly[city][RITORNO]){
			if (min_fly.day == 0){
				min_fly = aFly;
				ritorno.update(aFly.day,aFly.cost);
				ritorno_count.update(aFly.day,1);
				continue;
			}
			if (aFly.cost < min_fly.cost){
				ritorno.update(aFly.day,-min_fly.cost);
				ritorno.update(aFly.day,aFly.cost);
				min_fly = aFly;
			}
		}
	}
}
#undef cost
#undef day

void testfenwick(){
	cout<<"Testing fenwick..";
	fenwick to_test(10);
	for (int i = 1; i < 10; i++)
		to_test.update(i,1);
	for (int i = 1; i < 10; i++){
		cout<<to_test.get(1,i)<<"\n";
	}
}
int nearReturn(int andataDay){
	return andataDay +K+1;
}
int isPossible(int day){
	int nr = nearReturn(day);
	int tranf = transform_day(nr);
	return andata_count.get_0_to(day) == N && 
	ritorno_count.get_0_to(tranf) == N;
}
ll getAndataCost(int day){
	return andata.get_0_to(day);
}
ll getRitornoCost(int day){ // ritorno partendo questo giorno
	int nr = nearReturn(day);
	int tranf = transform_day(nr);
	return ritorno.get_0_to(tranf);
}
int main(int argc, const char * argv[])
{    
	ios::sync_with_stdio(0);

   // freopen("input.txt","r",stdin);
	cin>>N>>M>>K;
	for (int i = 0; i < M; i++){
		int d,f,t,c;
		cin>>d>>f>>t>>c;
		addFly(f,t,d,c);
	}
	elaborateAndataFly();
	elaborateRitornoFly();
	int max_andata_day = MAX_DAY-K-1;
	ll min_cost = 2e15;
	for (int i = 1; i <= max_andata_day; i++){
		if (isPossible(i)){
			ll costo = getAndataCost(i)+getRitornoCost(i);
    		//cout<<"costo per andare al giorno "<<i<<"\n";
			if (costo < min_cost){
				min_cost = costo;
			}
		}
	}
	if (min_cost == 2e15) cout<<-1;
	else cout<<min_cost;

	return 0;
}

