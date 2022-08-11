/*

We can merge two adjacent numbers into one and the cost of merging the two numbers is equal to the sum of two values.
The task is to find the total minimum cost of merging all the numbers.

*/

#include<iostream>
#include<vector>
#include<cstring>
#include<climits>
#include<numeric>

using namespace std;

vector<vector<int>> dp;

int mergeElements(vector<int>& arr, int i, int j, vector<int>& prefixSum);

int main()
{
    //vector<int> arr = {6, 4, 4, 6};
    vector<int> arr = {3, 2, 4, 1};

    dp = vector<vector<int>> (100, vector<int> (100, -1));

    int n = arr.size();
    vector<int> prefixSum(n+1, 0);

    for(int i=1; i<=n; i++)
        prefixSum[i] = prefixSum[i-1] + arr[i-1];

    int x = mergeElements(arr, 0, n-1, prefixSum);
    cout << x;
}


int mergeElements(vector<int>& arr, int i, int j, vector<int>& prefixSum)
{
    if(i > j)
        return INT_MAX;

    if(dp[i][j] != -1)
        return dp[i][j];

    if(i == j)
        return dp[i][i] = 0;

    int minCost = INT_MAX;
    int sum = prefixSum[j+1] - prefixSum[i];

    for(int k=i; k<j; k++)
        minCost = min(minCost, mergeElements(arr, i, k, prefixSum) + mergeElements(arr, k+1, j, prefixSum) + sum);

    return dp[i][j] = minCost;
}
