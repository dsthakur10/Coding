#include<bits/stdc++.h>
using namespace std;

int solve(int i, vector<int> &a, int mod, int d, unordered_map<int, unordered_map<int, int>> &mp) {

    if(i == a.size())
    {
        // if the mod till now is d then return 1 else return 0.
        if(mod == d)
            return 1;
        return 0;
    }

    //memoization condition.
    if(mp.find(1) != mp.end() and mp[i].find(mod) != mp[i].end())   return mp[i][mod];

    //including the number
    int x = a[i] * solve(i+1, a, abs((mod*a[i]))%10, d, mp);

    // excluding the number
    int y = solve(i+1, a, mod, d, mp);

    //storing the value and returning the ans.
    return mp[i][mod] = max(x, y);

}


int main()
{
    // taking input n is size of vector and d is digit used to check the mod.
    int n, d;
    cin>>n>>d;
    vector<int> a(n);
    for(int i=0;i<n;i++) cin>>a[i];

    // map is used because the mod initial value is -1 and that can't be a index in vector.
    unordered_map<int, unordered_map<int, int>> mp;

    // calling the function to solve
    cout<<solve(0, a, -1, d, mp);
}
