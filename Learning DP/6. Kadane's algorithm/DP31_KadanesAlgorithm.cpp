/*

Determine the maximum sum from sums of all the contiguous subarrays within a one-dimensional array of numbers.
Integers can be negative.

eg:
INPUT = {-2 -3 4 -1 -2 1 5 -3}

OUTPUT = 7 (4-1-2+1+5)

INPUT = {-2 1 -3 4 -1 2 1 -5 4}

OUTPUT = 6 (4-1-2+1)

INPUT = {-3 -4 5 -1 2 -4 6 -1}

OUTPUT = 8 (5-1+2-4+6)

INPUT = {-7 -7 -7 -2 -6 -10}

OUTPUT = -2

*/

#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>

static int dp[101];

                                // 2 loops
int kadane(std::vector<int>);               // Without DP
int kadane2(std::vector<int>);

                                // 1 loop

int kadane3(std::vector<int>, int &start, int &end);               // Without DP
int kadane4(std::vector<int>, int &start, int &end);


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

    int maxSum = kadane(arr);

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    std::cout << "\n\nMaxSum Subarray = " << maxSum;

    maxSum = kadane2(arr);
    std::cout << "\n\nBOTTOM-UP: MaxSum Subarray = " << maxSum;

    std::cout << "\n------------------";

    int start = 0, end = 0;
    maxSum = kadane3(arr, start, end);

    std::cout << "\n\nSTART = " << start << " END = " << end;
    std::cout << "\nMaxSum Subarray = " << maxSum;

    std::cout << "\n------------------";

    start = 0, end = 0;
    maxSum = kadane4(arr, start, end);

    std::cout << "\n\nSTART = " << start << " END = " << end;
    std::cout << "\nBOTTOM-UP: MaxSum Subarray = " << maxSum;

}



int kadane(std::vector<int> arr)
{
    int n = arr.size();
    int cur = 0;
    int maxSum = 0;

    for(int i=0; i<n; i++)
    {
        cur += arr[i];

        if(cur < 0)
            cur = 0;

        if(maxSum < cur)
            maxSum = cur;
    }

    if(maxSum == 0)
    {
        maxSum = INT_MIN;
        for(int i=0; i<n; i++)
            maxSum = std::max(maxSum, arr[i]);
    }

    return maxSum;
}



int kadane2(std::vector<int> arr)
{
    int n = arr.size();
    int dp[n];

    dp[0] = (arr[0] < 0) ? 0 : arr[0];
    int maxSum = dp[0];

    for(int i=1; i<n; i++)
    {
        dp[i] = dp[i-1] + arr[i];

        if(dp[i] < 0)
            dp[i] = 0;

        if(maxSum < dp[i])
            maxSum = dp[i];
    }

    if(maxSum == 0)
    {
        maxSum = INT_MIN;
        for(int i=0; i<n; i++)
            maxSum = std::max(maxSum, arr[i]);
    }

    return maxSum;
}



int kadane3(std::vector<int> arr, int &start, int &end)
{
    int n = arr.size();
    int cur = 0;
    int pre;
    int maxSum = INT_MIN;

    for(int i=0; i<n; i++)
    {
        pre = cur;
        cur += arr[i];

        if(maxSum < cur)
        {
            maxSum = cur;
            end = i;

            if(pre == 0)
                start = i;
        }

        if(cur < 0)
            cur = 0;

    }

    return maxSum;
}



int kadane4(std::vector<int> arr, int &start, int &end)
{
    int n = arr.size();
    int dp[n];


    int maxSum = INT_MIN;
    int index = 0;

    for(int i=0; i<n; i++)
    {
        if(i == 0)
            dp[i] = arr[i];

        else
            dp[i] = dp[i-1] + arr[i];

        if(maxSum < dp[i])
        {
            maxSum = dp[i];
            end = i;
            start = index;
        }

        if(dp[i] < 0)
        {
            dp[i] = 0;
            index = i+1;
        }

    }

    return maxSum;
}
