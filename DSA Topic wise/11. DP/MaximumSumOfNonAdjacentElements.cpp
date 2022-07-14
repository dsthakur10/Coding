/*

Given an array of size N containing positive integers.
Find the maximum sum of a subsequence such that no two numbers in the sequence should be adjacent in the array

*/


// Method-1 --> O(n^2) --> BOTTOM-UP --> TLE

int findMaxSum(int *arr, int n)
{
    if(n == 1)
        return arr[0];

    if(n == 2)
        return max(arr[0], arr[1]);

    int dp[n];
    dp[0] = arr[0];
    dp[1] = arr[1];

    int maxSum = max(dp[0], dp[1]);
    for(int i=2; i<n; i++)
    {
        int sum = 0;
        for(int j=0; j<i-1; j++)
            sum = max(sum, dp[j]);

        dp[i] = sum + arr[i];

        maxSum = max(dp[i], maxSum);
    }

    return maxSum;
}



// O(n^2) --> TOP-DOWN --> TLE

int dp[1000000];
int maxSum;

int findMaxSum(vector<int>& nums) {

    memset(dp, -1, sizeof(dp));
    int n = nums.size();

    if(n == 1)
        return nums[0];

    maxSum = max(nums[0], nums[1]);

    if(n == 2)
        return maxSum;

    solve(nums, n-1);

    return maxSum;
}

int solve(vector<int> nums, int n)
{
    if(dp[n] != -1)
        return dp[n];

    if(n == 0)
        return dp[0] = nums[0];

    if(n == 1)
        return dp[1] = nums[1];

    int sum = 0;
    for(int k=0; k<n-1; k++)
        sum = max(sum, solve(nums, k));

    dp[n] = sum + nums[n];

    maxSum = max(dp[n], maxSum);
    maxSum = max(dp[n], solve(nums, n-1));

    return dp[n];
}




// Method-2 --> O(n) time --> TOP-DOWN

vector<vector<int>> dp;
int findMaxSum(int *arr, int n) {

    dp = vector<vector<int>> (n+1, vector<int> (2, -1));
    return max(solve(arr, n, 1), solve(arr, n, 0));
}

int solve(int *arr, int n, int k)
{
    if(n == 0)
        return 0;

    if(n == 1)
    {
        dp[n][0] = 0;
        dp[n][1] = arr[0];

        return dp[n][k];
    }

    if(dp[n][k] != -1)
        return dp[n][k];

    if(k == 0)
        dp[n][k] = max(solve(arr, n-1, 0), solve(arr, n-1, 1));

    else
        dp[n][k] = arr[n-1] + solve(arr, n-1, 0);

    //maxSum = max(dp[n][k], maxSum);

    return dp[n][k];
}


// O(n) time --> BOTTOM-UP

int findMaxSum(int *arr, int n) {

    //dp = vector<vector<int>> (n+1, vector<int> (2, -1));
    int dp[n][2];

    dp[0][0] = 0;
    dp[0][1] = arr[0];

    for(int i=1; i<n; i++)
    {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);     // exclude arr[i]
        dp[i][1] = dp[i-1][0] + arr[i];             // include arr[i]
    }

    return max(dp[n-1][0], dp[n-1][1]);
}
