/*
Given an array arr[0 … n-1] containing n positive integers, a subsequence of arr[] is called Bitonic if it is first increasing, then decreasing.
TAsk is to return the length of the longest bitonic subsequence.

NOTE:
    - A sequence, sorted in increasing order is considered Bitonic with the decreasing part as empty.
    - Similarly, decreasing order sequence is considered Bitonic with the increasing part as empty.

Input arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
Output: 6           (A Longest Bitonic Subsequence of length 6 is 1, 2, 10, 4, 2, 1)

Input arr[] = {12, 11, 40, 5, 3, 1}
Output: 5           (A Longest Bitonic Subsequence of length 5 is 12, 11, 5, 3, 1)

Input arr[] = {80, 60, 30, 40, 20, 10}
Output: 5           (A Longest Bitonic Subsequence of length 5 is 80, 60, 30, 20, 10)

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>

static int lis[1001];
static int lds[1001];

int LIS(std::vector<int> arr, int n, int &maxx);
int LIS2(std::vector<int> arr);

int LDS(std::vector<int> arr, int n, int &maxx);
int LDS2(std::vector<int> arr);

int LBS(std::vector<int> arr);
int LBS2(std::vector<int> arr);


int main()
{
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
    int maxx1 = 1;
    LIS(arr, n-1, maxx1);

    std::cout<< "\n\nLIS = ";
    for(int i=0; i<n; i++)
        std::cout << lis[i] << " ";

    std::cout << "\n\nTOP-DOWN: LIS = " << maxx1;

    int maxx2 = 1;
    LDS(arr, 0, maxx2);

    std::cout<< "\n\nLDS = ";
    for(int i=0; i<n; i++)
        std::cout << lds[i] << " ";

    std::cout << "\n\nTOP-DOWN: LDS = " << maxx2;

    std::cout << "\n\n";
    maxx1 = LIS2(arr);
    std::cout << "\n\nBOTTOM-UP: LIS = " << maxx1;

    std::cout << "\n\n";
    maxx2 = LDS2(arr);
    std::cout << "\n\nBOTTOM-UP: LDS = " << maxx2;

*/

    std::cout << "\n\nTOP-DOWN: LBS = " << LBS(arr);
    std::cout << "\n\nBOTTOM-UP: LBS = " << LBS2(arr);

    return 0;
}



int LBS(std::vector<int> arr)
{
    memset(lis, -1, sizeof(lis));
    memset(lds, -1, sizeof(lds));

    int maxx1 = 1, maxx2 = 1;

    LDS(arr, 0, maxx1);
    LIS(arr, arr.size()-1, maxx2);

    int maxx = INT_MIN;

    for(int i=0; i<arr.size(); i++)
    {
        int temp = lis[i] + lds[i];
        maxx = std::max(temp, maxx);
    }

    return maxx-1;
}


int LBS2(std::vector<int> arr)
{
    int n = arr.size();

    int lis[n], lds[n];

    lis[0] = 1;
    lds[n-1] = 1;

    for(int i=1; i<n; i++)
    {
        lis[i] = 0;

        for(int j=0; j<i; j++)
        {
            if(arr[j] < arr[i])
                lis[i] = std::max(lis[i], lis[j]);
        }

        lis[i] = 1 + lis[i];
    }


    for(int i=n-2; i>=0; i--)
    {
        lds[i] = 0;

        for(int j=i+1; j<n; j++)
        {
            if(arr[i] > arr[j])
                lds[i] = std::max(lds[i], lds[j]);
        }

        lds[i] = 1 + lds[i];
    }


    int maxx = INT_MIN;

    for(int i=0; i<n; i++)
    {
        int temp = lis[i] + lds[i];
        maxx = std::max(temp, maxx);
    }

    return maxx-1;

}


int LIS(std::vector<int> arr, int n, int &maxx)
{
    if(lis[n] != -1)
        return lis[n];

    if(n == 0)
    {
        lis[n] = 1;
        return lis[n];
    }

    int temp = 0;

    for(int k=n-1; k>=0; k--)
    {
        int temp2 = (lis[k] != -1) ? lis[k] : LIS(arr , k, maxx);

        if(arr[k] < arr[n])
            temp = std::max (temp, temp2);

    }

    lis[n] = 1 + temp;

    maxx = std::max(maxx, lis[n]);

    return lis[n];
}



int LIS2(std::vector<int> arr)
{
    int maxx=1, n = arr.size();
    int dp[n];

    dp[0] = 1;

    for(int i=1; i<n; i++)
    {
        int temp = 0;
        for(int j=0; j<i; j++)
        {
            if(arr[j] < arr[i])
                temp = std::max (temp, dp[j]);
        }

        dp[i] = 1 + temp;

        maxx = std::max( maxx, dp[i] );
    }

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";
    return maxx;

}



int LDS(std::vector<int> arr, int n, int &maxx)
{
    if(lds[n] != -1)
        return lds[n];

    if(n == arr.size()-1)
    {
        lds[n] = 1;
        return lds[n];
    }

    int temp = 0;

    for(int k=n+1; k<arr.size(); k++)
    {
        int temp2 = (lds[k] != -1) ? lds[k] : LDS(arr, k, maxx);

        if(arr[n] > arr[k])
            temp = std::max (temp, temp2);

    }

    lds[n] = 1 + temp;

    maxx = std::max(maxx, lds[n]);

    return lds[n];
}




int LDS2(std::vector<int> arr)
{
    int maxx=1, n = arr.size();
    int dp[n];

    dp[n-1] = 1;

    for(int i=n-2; i>=0; i--)
    {
        int temp = 0;
        for(int j=i+1; j<n; j++)
        {
            if(arr[i] > arr[j])
                temp = std::max (temp, dp[j]);
        }

        dp[i] = 1 + temp;

        maxx = std::max( maxx, dp[i] );
    }

    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    return maxx;

}




// LATEST


int LongestBitonicSequence(vector<int>nums)
{
    int maxLen = 0;
    int n = nums.size();
    vector<int> LIS(n), LDS(n);

    longestIncreasingSub(nums, LIS, n);
    longestDecreasingSub(nums, LDS, n);

    for(int i=0; i<n; i++)
        maxLen = max(maxLen, LIS[i] + LDS[i] - 1);

    return maxLen;
}


void longestIncreasingSub(vector<int>& nums, vector<int>& LIS, int n)
{
    for(int i=0; i<n; i++)
    {
        LIS[i] = 1;
        for(int j=0; j<i; j++)
        {
            if(nums[j] < nums[i])
                LIS[i] = max(LIS[i], 1 + LIS[j]);
        }
    }
}

void longestDecreasingSub(vector<int>& nums, vector<int>& LDS, int n)
{
    for(int i=n-1; i>=0; i--)
    {
        LDS[i] = 1;
        for(int j=n-1; j>i; j--)
        {
            if(nums[j] < nums[i])
                LDS[i] = max(LDS[i], 1 + LDS[j]);
        }
    }
}
