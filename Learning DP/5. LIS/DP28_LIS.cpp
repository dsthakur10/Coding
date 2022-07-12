/*

Longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence such that
all elements of the subsequence are sorted in increasing order

eg.
INPUT : {10, 22, 9, 33, 21, 50, 41, 60, 80}

OUTPUT : 6
LIS is {10, 22, 33, 50, 60, 80}.

Input: arr[] = {3, 10, 2, 1, 20}

Output: Length of LIS = 3
The longest increasing subsequence is 3, 10, 20

Input: arr[] = {3, 2}

Output: Length of LIS = 1
The longest increasing subsequences are {3} and {2}

Input: arr[] = {50, 3, 10, 7, 40, 80}

Output: Length of LIS = 4
The longest increasing subsequence is {3, 7, 40, 80}

Input: arr[] = {4, 10, 4, 3, 8, 9}

Output: Length of LIS = 3

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>

static int dp[101];

// Normal DP --> O(n^2)
int LIS(std::vector<int> arr, int n, int &maxx);                        // Top-Down memoization
int LIS2(std::vector<int> arr);                                         // Bottom-Up

// Binary Search + DP --> O(nlogn)
int LIS3(std::vector<int> arr);

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

    int maxx = 1;
    int lis = LIS(arr,n-1,maxx);

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    std::cout << "\n\nTOP-DOWN: LIS = " << maxx;

    std::cout << "\n\n";
    int maxx2 = LIS2(arr);
    std::cout << "\n\nBOTTOM-UP: LIS = " << maxx2;

    return 0;
}



int LIS(std::vector<int> arr, int n, int &maxx)
{
    if(dp[n] != -1)
        return dp[n];

    if(n == 0)
    {
        dp[n] = 1;
        return dp[n];
    }

    int dp[n] = 1;

    for(int k=n-1; k>=0; k--)
    {

    /*
    // WRONG ANSWER

        if(arr[k] < arr[n])
            dp[n] = max(dp[n], 1 + LIS(arr, k, maxx));
    */

        int temp = (dp[k] != -1) ? dp[k] : LIS(arr , k, maxx);

        if(arr[k] < arr[n])
            dp[n] = max(dp[n], 1 + temp);

    }

    maxx = max(maxx, dp[n]);

    return dp[n];
}



// BOTTOM-UP approach

int maxLen = 1;
int LIS2(vector<int>& nums) {

    int n = nums.size();
    int dp[n];

    for(int i=0; i<n; i++)
    {
        dp[i] = 1;

        for(int j=0; j<i; j++)
        {
            if(nums[j] < nums[i])
                dp[i] = max(dp[i], 1 + dp[j]);
        }

        maxLen = max(maxLen, dp[i]);
    }

    return maxLen;
}



// Binary Search + DP
