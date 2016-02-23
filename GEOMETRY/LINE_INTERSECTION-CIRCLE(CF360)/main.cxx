#include <bits/stdc++.h>

using namespace std;
typedef pair<double, double> pi;
typedef pair<int,pi> pii;
typedef vector<int> vi;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD = 1e9 + 7;

#define MAXN 200100
#define _PI 3.14159265358979323846

double N,R;
double degree;

struct line_t{ 
	double m, q;
	line_t(){}
	line_t(pi p1,pi p2)
	{
		if ( p1.first > p2.first) swap(p1,p2);
		m = (p2.second-p1.second) /(p2.first-p1.first);
		q = (p1.second - m*p1.first);
	}
	pi intersection(line_t & l2)
	{
		double x = (l2.q-q)/(m-l2.m);
		double y = l2.m * x + l2.q;
		return {x,y};
	}
};
pi coordinate_point(int i)
{
	double x = sin(degree * i) * R;
	double y = cos(degree * i) * R;
	return {x,y};
}
double distance( pi a, pi b)
{
	double dx = abs(b.first-a.first);
	double dy = abs(b.second-a.second);
	return sqrt(dx*dx + dy*dy);
}
int main()
{
	ios::sync_with_stdio(0);
	
	cin>>N>>R;
	degree = _PI * 2 / N;
	cout.precision(20);
	/*for (int i = 0; i < N; i++)
	{
		pi cp = coordinate_point(i);
	//	cout<<cp.first<<","<<cp.second<<"\n";
	}*/
	pi a = coordinate_point(0);
	pi b = coordinate_point(N/2);
	pi a1 = coordinate_point(1);
	pi b1 = coordinate_point(N/2+2);
	
	line_t l1(a,b), l2(a1,b1);
	//cerr<<"l1 m q: "<<l1.m<<" "<<l1.q<<"\n";
	pi intersection = l1.intersection(l2); // vertice del triangolo
	//cerr<<"intersection: "<<intersection.first<<" "<<intersection.second<<"\n";
	line_t base (a,a1); // base triangolo
	line_t perp; 
	perp.q = 0;
	perp.m = (intersection.second /intersection.first);
	//cerr<<" perp: m: "<<perp.m<<" q: "<<perp.q<<"\n";

	pi base_cad = perp.intersection(base);
	
	double h_triangle = distance(intersection,base_cad);
	double b_triangle = distance(a,a1);
	
	double area_triangle = (b_triangle * h_triangle) / 2;
	
	double areaAllCircle = (R*R*_PI);
	double sector = areaAllCircle / N;
	
	double h_big_t = distance({0,0},base_cad);
	double big_t_area = (h_big_t * b_triangle) /2;
	double cord_area = sector-big_t_area;
	
	double single_part = cord_area + area_triangle;
	
	double result = areaAllCircle-  single_part * N;
	
	cout.precision(30);
	cout<<result;
	return 0;
}
