#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <list>

using namespace std;
#define MAXN 500

long long points[MAXN];

//circular list implementation
void advance(list<int> &l,list<int>::iterator & it){
	it++;
	if(it == l.end()) it = l.begin();
}
void decrement(list<int> & l, list<int>::iterator & it){
	if (it == l.begin())
		it = l.end();	
	it--;
}
int main(){

	int P = 426, L = 72058*100;
	list<int> l;
	l.push_back(0);
	auto iter = l.begin();
	int inx = 0;
	for (int i = 1; i < L; i++){
		if (i % 23 == 0){
			points[(i-1)%P] += i;
			for (int j = 0; j < 7; j++) decrement(l,iter);
			points[(i-1)%P] += *iter;
			iter = l.erase(iter);
			continue;
		}
		advance(l,iter); advance(l,iter);
		l.insert(iter,i);
		decrement(l,iter);	
	}

	long long max_points = 0;
	for (int i = 0; i < P; i++){
		max_points = max(max_points, points[i]);
	}
	cout<<"=>"<<max_points<<endl;
	return 0;
	//part1: 424112
	//part2: 3487352628
}
