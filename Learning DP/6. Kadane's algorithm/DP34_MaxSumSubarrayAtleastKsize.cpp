/*

Determine the maximum sum from sums of all the contiguous subarrays within a one-dimensional array of numbers with constraint subarray size >= k
Integers can be negative.


Input : arr[] = {-4, -2, 1, -3}  k = 2
Output : -1
The sub array is {-2, 1}

Input : arr[] = {1, 1, 1, 1, 1, 1} k = 3
Output : 6
The sub array is {1, 1, 1, 1, 1, 1}

Input = {-2 -3 4 -1 -2 1 5 -3} k = 5
Output = 7




*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
#include<cstdlib>

static int dp[101];


int maxSumSubarrayAtleastSizeK(std::vector<int> arr, int k);               // Without DP
int maxSumSubarrayAtleastSizeK2(std::vector<int> arr, int k);

int main()
{
    memset(dp, -1, sizeof(dp));
    std::vector<int> arr;
    int n,x,k;

    std::cout << "Enter size: \n";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    std::cout << "\nEnter minimum size for subarray:\n";
    std::cin >> k;

    int maxSum = maxSumSubarrayAtleastSizeK(arr, k);

    std::cout << "\n\nMaxSum Subarray = " << maxSum;
/*
    maxSum = maxSumSubarrayAtleastSizeK2(arr, k);
    std::cout << "\n\nBOTTOM-UP: MaxSum Subarray = " << maxSum;
*/
    return 0;

}




int maxSumSubarrayAtleastSizeK(std::vector<int>arr, int k)
{
    int maxSum;
    int sum = 0;
    int temp = 0;

    int n = arr.size();
    int dp[n];

    for(int i=0; i<n; i++)
    {
        if(i==0)
            dp[i] = arr[i];

        else
            dp[i] = dp[i-1] + arr[i];

        if(dp[i] < 0)
            dp[i] = 0;

        if(i<k)
            sum += arr[i];
    }

    std::cout << "\n";

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";


    maxSum = sum;
    for(int i=k; i<n; i++)
    {
        sum = sum + arr[i] - arr[i-k];              // getting sum of subarray of size=k ending at i
        temp = std::max(sum, sum + dp[i-k]);         // getting the best possible subarray with size>=k ending at i

        maxSum = std::max(maxSum, temp);             // getting the best possible subarray
    }

    return maxSum;
}



int maxSumSubarrayAtleastSizeK2(std::vector<int> arr, int k)
{



}
