#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<int> z_alg(string  s)
{
    vector<int> z(s.size());

    int L = 0, R = 0; int n = s.size();
    for (int i = 1; i < n; i++)
    {
        if (i <= R)
            z[i] = min(z[i-L], R-i+1);
        while ( z[i] < n && s[z[i]] == s[z[i]+i])
            z[i]++;
        if ( z[i]+i-1 > R)
        { L = i, R = z[i] + i-1;}
    }
    return move(z);
}






















vector<int> z_alg(string s)
{
    int n = s.size();
    vector<int> z(n);
    int L = 0, R = 0;
    for (int i = 1; i < n; i++)
    {
        if ( i <= R)
            z[i] = min(z[i-L],R-i+1);
        while (z[i]+i < n && s[z[i]] == s[z[i]+i]) z[i]++;
        if ( z[i]+i-1 > R)
            L = i, R = z[i]+i-1;
    }
}
int main()
{
    vector<int> v = z_alg("abababab");
    for(int a:v) cout<<a<<" ";
    return 0;
}
