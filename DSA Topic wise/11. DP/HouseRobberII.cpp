
/*

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money
stashed. ALL HOUSES AT THIS PLACE ARE ARRANGED IN A CIRCLE. That means the first house is the neighbor of the
last one. Meanwhile, adjacent houses have a security system connected, and it will automatically contact the
police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money
you can rob tonight without alerting the police

*/


int rob(vector<int>& nums) {

    int n = nums.size();

    if(n == 1)
        return nums[0];

    if(n == 2)
        return max(nums[0], nums[1]);

    return max(solve(nums, 0), solve(nums, 1));
}

int solve(vector<int> nums, int start)
{
    if(start == 0)
        nums.erase(nums.begin() + nums.size() - 1);

    else
        nums.erase(nums.begin());

    int n = nums.size();
    int dp[n+1];
    dp[0] = 0;
    dp[1] = nums[0];
    int maxSum = nums[0];
    for(int i=2; i<n+1; i++)
    {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]);
        maxSum = max(dp[i], maxSum);
    }

    return maxSum;
}
