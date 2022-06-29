/*

Determine the minimum sum from sums of all the contiguous subarrays within a one-dimensional array of numbers.
Integers can be negative.

eg:
INPUT = {3 -4 2 -3 -1 7 -5}

OUTPUT = -6 (-4+2-3-1)

INPUT = {-2 1 -3 4 -1 2 1 -5 4}

OUTPUT = -5 (-5)

INPUT = {-3 -4 -1 -4 -1}

OUTPUT = -13 (-3-4-1-4-1)

INPUT = {7 7 7 2 6 10}

OUTPUT = 2 (2)

*/



#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>

static int dp[101];

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

/*
    int maxSum = kadane(arr);

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    std::cout << "\n\nMaxSum Subarray = " << maxSum;

    maxSum = kadane2(arr);
    std::cout << "\n\nBOTTOM-UP: MaxSum Subarray = " << maxSum;

    std::cout << "\n------------------";
*/

    int start = 0, end = 0;
    int minSum = kadane3(arr, start, end);

    std::cout << "\n\nSTART = " << start << " END = " << end;
    std::cout << "\nMinSum Subarray = " << minSum;

    std::cout << "\n------------------";

    start = 0, end = 0;
    minSum = kadane4(arr, start, end);

    std::cout << "\n\nSTART = " << start << " END = " << end;
    std::cout << "\nBOTTOM-UP: MinSum Subarray = " << minSum;

}



int kadane3(std::vector<int> arr, int &start, int &end)
{
    int n = arr.size();
    int cur = 0;
    int pre;
    int minSum = INT_MAX;

    for(int i=0; i<n; i++)
    {
        pre = cur;
        cur += arr[i];

        if(minSum > cur)
        {
            minSum = cur;
            end = i;

            if(pre == 0)
                start = i;
        }

        if(cur > 0)
            cur = 0;

    }

    return minSum;
}



int kadane4(std::vector<int> arr, int &start, int &end)
{
    int n = arr.size();
    int dp[n];


    int minSum = INT_MAX;
    int index = 0;

    for(int i=0; i<n; i++)
    {
        if(i == 0)
            dp[i] = arr[i];

        else
            dp[i] = dp[i-1] + arr[i];

        if(minSum > dp[i])
        {
            minSum = dp[i];
            end = i;
            start = index;
        }

        if(dp[i] > 0)
        {
            dp[i] = 0;
            index = i+1;
        }

    }

    return minSum;
}
