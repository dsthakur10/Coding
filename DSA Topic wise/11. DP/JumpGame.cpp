/*

You are given an integer array nums. You are initially positioned at the array's first index, and each element
in the array represents your maximum jump length at that position.

Return true if you can reach the last index, or false otherwise.

Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0,
which makes it impossible to reach the last index.

*/


// Method-1 DP
// TOP-DOWN --> TLE

vector<int> dp;

bool canJump(vector<int>& nums) {

    int n = nums.size();
    dp = vector<int>(n, -1);

    return solve(nums, 0);
}


int solve(vector<int>& nums, int n)
{
    if(n == nums.size()-1)
        return 1;

    if(dp[n] != -1)
        return dp[n];

    int flag = 0;

    int limit = min(nums[n], nums.size()-1);

    for(int jump=1; jump <= limit; jump++)
        flag = flag || solve(nums, jump+n);

    return dp[n] = flag;
}


// TOP-DOWN
vector<int> dp;

bool canJump(vector<int>& nums) {

    int n = nums.size();
    dp = vector<int>(n, -1);

    return solve(nums, 0);
}

int solve(vector<int>& nums, int n)
{
    if(n == nums.size()-1)
        return 1;

    if(dp[n] != -1)
        return dp[n];

    int limit = min(nums[n], (int)nums.size()-1);

    for(int jump=1; jump <= limit; jump++)
    {
        if(solve(nums, jump+n))
            return dp[n] = 1;
    }

    return dp[n] = 0;
}


// BOTTOM-UP

vector<bool> dp;

bool canJump(vector<int>& nums) {

    int n = nums.size();
    dp = vector<bool>(n, false);

    dp[n-1] = true;
    for(int i=n-2; i>=0; i--)
    {
        int limit = min(nums[i], n-1);
        bool flag = false;

        for(int jump=1; jump <= limit; jump++)
            flag = flag || dp[i+jump];

        dp[i] = flag;
    }

    return dp[0];
}


// Method-2 --> Greedy

/*
Idea is to work backwards from the last index. Keep track of the smallest index that can "jump" to the last index.
Check whether the current index can jump to this smallest index.
*/

bool canJump(vector<int>& nums) {

    int n = nums.size();

    int last = n-1, i, j;
    for(i=n-2; i>=0; i--)
    {
        if(i+nums[i] >= last)
            last = i;
    }

    return last<=0;
}
