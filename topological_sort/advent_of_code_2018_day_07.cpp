#include <iostream>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define MAXN 300

vector<char> gg[MAXN];  
int entranti[MAXN];
bool presents[MAXN];
const int WORKER_N = 5;
const int WAITING_T = 60;


struct worker_t{
	int id, finish_time;
	char working_on;
	bool operator<(const worker_t & b) const{
		return finish_time >= b.finish_time;
	}
};

void topo_sort(){
	priority_queue<char> coda; // completition_time, char

	for (char c = 'A' ; c <= 'Z'; c++)
		if (entranti[c] == 0 && presents[c])
			coda.push(-c);
		
	vector<worker_t> workers;	
	for (int i = 0; i < WORKER_N; i++) workers.push_back({i,(int)2e8,0});
	
	int to_output = 0;
	for (int c = 'A'; c <= 'Z'; c++) if (presents[c]) to_output++;
	int outputted = 0;
	int att_time = 0;

	
	while (outputted < to_output){

		for (worker_t & w: workers)
			if (w.finish_time < att_time && w.working_on != 0){
				char comp = w.working_on;
				cout<<comp; outputted++;
				for (char dest: gg[comp]){
					entranti[dest]--;
					if (entranti[dest] == 0) 
						coda.push(-dest);
				}
				w.working_on = 0;
			}

		for (worker_t & w : workers)
			if (w.working_on == 0 && !coda.empty()){
				w.working_on = -coda.top(); coda.pop();
				w.finish_time = att_time + WAITING_T + (w.working_on-'A'+1)-1 ;
			}	
		att_time++;

	}
	cout<<endl<<"time: "<<att_time-1<<endl;
}
int main(){
	char before, after;
	while (cin>>before>>after){
		presents[before] = presents[after] = true;
		gg[before].push_back(after);
		entranti[after]++;
	}
	
	topo_sort();
	return 0;
}
