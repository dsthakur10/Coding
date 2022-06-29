/*

Given an array of n positive integers.
Find the sum of maximum sum subsequence of the given array such that the integers in the subsequence are sorted in increasing order.

Examples:

INPUT - {1, 101, 2, 3, 100, 4, 5}
OUTPUT - 106 (1 + 2 + 3 + 100)

INPUT - {3, 4, 5, 10}
OUTPUT - 22 (3 + 4 + 5 + 10)

INPUT - {10, 5, 4, 3}
OUTPUT - 10

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>

static int dp[101];

int maxSumSubseqeunce(std::vector<int> arr, int n, int &maxx);                        // Top-Down memoization
int maxSumSubseqeunce2(std::vector<int> arr);                       // Bottom-Up
int maxSumSubseqeunce3(std::vector<int> arr);

int main()
{
    memset(dp, -1, sizeof(dp));
    std::vector<int> arr;
    int n,x;

    std::cout << "Enter size: \n";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    int maxx = arr[0];
    int lis = maxSumSubseqeunce(arr,n-1,maxx);

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    std::cout << "\n\nTOP-DOWN: Maximum Sum Subsequence = " << maxx;
    std::cout << "\n\n";

    int maxx2 = maxSumSubseqeunce2(arr);
    std::cout << "\n\nBOTTOM-UP: Maximum Sum Subsequence = " << maxx2;

    return 0;

}



int maxSumSubseqeunce(std::vector<int> arr, int n, int &maxx)
{
    if(dp[n] != -1)
        return dp[n];

    if(n == 0)
        return dp[n] = arr[n];

    int temp = 0;
    for(int k=0; k<n; k++)
    {
        int temp2 = (dp[k] != -1) ? dp[k] : maxSumSubseqeunce(arr, k, maxx);

        if(arr[k] < arr[n])
            temp = std::max(temp,temp2);
    }

    dp[n] = temp + arr[n];

    maxx = std::max( maxx, dp[n]);

    return dp[n];
}



int maxSumSubseqeunce2(std::vector<int> arr)
{
    int maxx=arr[0], n = arr.size();
    int dp[n];

    dp[0] = arr[0];

    for(int i=1; i<n; i++)
    {
        int temp = 0;
        for(int j=0; j<i; j++)
        {
            if(arr[j] < arr[i])
                temp = std::max (temp, dp[j]);
        }

        dp[i] = arr[i] + temp;

        maxx = std::max( maxx, dp[i] );
    }

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";
    return maxx;

}
