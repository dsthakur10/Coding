


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
#include<cmath>
#include<numeric>

static int dp[101];

int kConcatenationMaxSum(std::vector<int>& arr, int k);                 // Overflow

int kConcatenationMaxSum2(std::vector<int>& arr, int k);

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

    std::cout << "Enter K value: ";
    std::cin >> k;

    int maxSum = kConcatenationMaxSum(arr, k);

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    std::cout << "\n\nMaxSum Subarray = " << maxSum;

    //maxSum = kConcatenationMaxSum2(arr);
    //std::cout << "\n\nBOTTOM-UP: MaxSum Subarray = " << maxSum;

    return 0;

}



// May cause heap overflow because of size

int kConcatenationMaxSum(std::vector<int>& arr, int k)
{
    int n = arr.size();
    long long x = k*n;

    long long maxSum = INT_MIN;
    long long sum = 0;

    for(int i=0; i<x; i++)
    {
        if(i==0)
            sum = arr[i];

        else
        {
            sum = sum + arr[i%n];
        }

        if(maxSum < sum)
            maxSum = sum;

        if(sum < 0)
            sum = 0;
    }

    long long ans = maxSum % 1000000007;

    if(ans < 0)
        return 0;

    return ans;
}


/*
3 cases exist:
    1. k=1      --> apply kadane's algo
    2. k=2      --> apply kadane's algo on repeated array (max suffix of 1st arrray  +  max prefix of 2nd array)
    3. k>2
        (a) Total sum of array > 0 --> (result of k=2) + (k-2)*(total sum of array)
        (b) Total sum of array < 0 --> (result of k=2)

    NOTE: if result turns out to be negative --> return 0 (because of modulo, we cannot return negative values)

*/


int kConcatenationMaxSum2(std::vector<int>& arr, int k)
{
    int n = arr.size();
    int64_t total = accumulate (arr.begin(), arr.end(), 0);

    int maxSum = INT_MIN, sum=0;

    for(int i=0; i < n * std::min(k,2); i++)
    {
        sum += arr[i];

        if(maxSum < sum)
            maxSum = sum;

        if(sum < 0)
            sum = 0;
    }

    int result = std::max<int64_t>( {0, maxSum, maxSum + total*std::max(0, k-2)} ) % (int64_t)(pow(10,9) + 7);

    return result;
}
