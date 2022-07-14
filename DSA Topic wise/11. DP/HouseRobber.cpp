/*

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money
stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems
connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money
you can rob tonight without alerting the police.

*/

// Method-1 --> O(n^2) --> BOTTOM-UP

int rob(vector<int>& nums) {
    int n = nums.size();
    int maxSum;

    if(n == 1)
        return nums[0];

    if(n == 2)
        return max(nums[0], nums[1]);

    int dp[n];
    dp[0] = nums[0];
    dp[1] = nums[1];

    maxSum = max(dp[0], dp[1]);

    for(int i=2; i<n; i++)
    {
        int sum = 0;
        for(int j=0; j<i-1; j++)
            sum = max(sum, dp[j]);

        dp[i] = sum + nums[i];

        maxSum = max(dp[i], maxSum);
    }

    return maxSum;
}



// TOP-DOWN --> O(n^2)

int dp[100];
int maxSum;

int rob(vector<int>& nums) {

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



// Method-2 --> O(n) time --> BOTTOM-UP

int rob(vector<int>& nums) {

    int n = nums.size();
    int dp[n][2];

    dp[0][0] = 0;
    dp[0][1] = nums[0];

    for(int i=1; i<n; i++)
    {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);     // exclude arr[i]
        dp[i][1] = dp[i-1][0] + nums[i];             // include arr[i]
    }

    return max(dp[n-1][0], dp[n-1][1]);
}
