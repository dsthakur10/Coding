/*

You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an
array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins.
If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

Example 1:
Input: nums = [3,1,5,8]
Output: 167
Explanation: nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
            coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

Example 2:
Input: nums = [1,5]
Output: 10

*/



// LOGIC:  This is not exactly MCM pattern --> This is a mixture of "MCM pattern" + "MERGE intervals"

/*
    WHY not MCM pattern ?
        --> In MCM pattern, we use an array element any number of times we want to calculate intermediate results.
        --> Here, this is just not the case. Once a balloon is burst, you cannot use it
        --> i.e. restriction is imposed on array element to use.

The natural way to divide the problem is burst one balloon and separate the balloons into 2 sub sections
one on the left and other on the right. However, in this problem the left and right become adjacent and
have effects on the maxCoins in the future

    [i....k-1]  k  [k+1....j]
    --> If you burst kth balloon, you will get 2 intervals that won't be independent.
    --> Left & right intervals are dependent on one another's extreme elements.

Hence, we need a way to find out some independence between the 2 subarrays to solve.

    --> Coins you get for a balloon DOEST NOT depend on "already burst" balloons --> Consider kth balloon as last
    --> Instead of dividing the problem by first balloon to burst, we divide the problem by last balloon to burst

If kth ballon is the last balloon to get burst, cost incurred will be nums[-1] * nums[k] * nums[n]

    WHY only LAST balloon & not FIRST balloon ?
        --> cost of bursting FIRST = nums[k-1] * nums[k] * nums[k+1]
        --> cost of bursting LAST  = nums[-1] * nums[k] * nums[n]
        --> Considering kth balloon as LAST balloon to burst, we can easily solve our left & right subproblems
            with dependency & proper defined boundaries.

        --> [i....k-1]  k  [k+1....j] --> FIRST to burst --> Burst k immediately --> boundaries will be undefined
        --> [i....k]  k  [k....j] --> LAST to burst --> DO NOT need to burst k at the moment --> boundary is defined

*/


// Add 1 in the beginning & ending of array --> so that last balloon to burst gets #coins = (1 * nums[k] * 1)

// dp[i][j] --> Max #coins after bursting all the balloons in (i+1 --> j-1)
// ith & jth balloon will be the last one to burst

int dp[303][303];

int maxCoins(vector<int>& nums) {

    int n = nums.size();
    memset(dp, -1, sizeof(dp));
    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    return solve(nums, 0, nums.size()-1);
}


int solve(vector<int>& nums, int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    // subarray must have atleast 3 ballons to calculate cost (#coins)
    if(j-i+1 < 3)
        return 0;

    int ans = 0;

    // kth is the balloon to get burst at the LAST but before ith & jth balloon
    // Interval ranges (i+1 .... j-1) --> ith & jth are not to be considered

    for(int k=i+1; k<j; k++)
    {
        // kth balloon is the last to burst --> coins = nums[i] * nums[k] * nums[j]

        int cost = nums[i] * nums[k] * nums[j];
        //ans = max(solve(nums, i, k-1) + solve(nums, k+1, j) + cost);      // FIRST to BURST
        ans = max(ans, solve(nums, i, k) + solve(nums, k, j) + cost);
    }

    return dp[i][j] = ans;
}



// BOTTOM-UP

int maxCoinsDP(vector<int> &iNums) {
    int nums[iNums.size() + 2];
    int n = 1;
    for (int x : iNums) if (x > 0) nums[n++] = x;
    nums[0] = nums[n++] = 1;


    int dp[n][n] = {};
    for (int k = 2; k < n; ++k) {
        for (int left = 0; left < n - k; ++left)
            int right = left + k;
            for (int i = left + 1; i < right; ++i)
                dp[left][right] = max(dp[left][right],
                     nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
        }

    return dp[0][n - 1];
}
