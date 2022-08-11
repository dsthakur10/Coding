

// TOP-DOWN

vector<int> dp;

int jump(vector<int>& nums) {

    int n = nums.size();
    dp = vector<int> (n, -1);

    return solve(nums, 0);
}

int solve(vector<int>& nums, int n)
{
    int len = nums.size();

    if(n >= len)
        return INT_MAX;

    if(dp[n] != -1)
        return dp[n];

    if(n == len-1)
        return dp[n] = 0;

    if(nums[n] == 0)
        return dp[n] = INT_MAX;

    int limit = min(nums[n], len-1);
    int jumps = INT_MAX;

    for(int k=1; k<=limit; k++)
    {
        int x = solve(nums, n+k);

        if(x != INT_MAX)
            jumps = min(jumps, 1 + x);
    }

    return dp[n] = jumps;
    //return dp[n] = (jumps == INT_MAX) ? 0 : jumps;
}



// BOTTOM-UP

vector<int> dp;

int jump(vector<int>& nums) {

    int n = nums.size();
    dp = vector<int> (n, INT_MAX);

    dp[n-1] = 0;
    for(int i=n-2; i>=0; i--)
    {
        int limit = min(nums[i], n-1);
        int jumps = INT_MAX;

        if(nums[i] == 0)
            continue;

        for(int k=1; k<=limit; k++)
        {
            if(i+k >= n)
                break;

            int x = dp[i+k];

            if(x != INT_MAX)
                jumps = min(jumps, 1 + x);
        }

        dp[i] = jumps;
    }

    return dp[0];
}



// Method-2 --> Greedy using BFS

/*

This problem has a nice BFS structure. Let's illustrate it using the example nums = [2, 3, 1, 1, 4] in the problem
statement. We are initially at position 0. Then we can move at most nums[0] steps from it.
So, after one move, we may reach nums[1] = 3 or nums[2] = 1. So these nodes are reachable in 1 move.
From these nodes, we can further move to nums[3] = 1 and nums[4] = 4.
Now you can see that the target nums[4] = 4 is reachable in 2 moves.

Putting these into codes, we keep two pointers "start" and "end" that records the current range of starting nodes.
Each time after we make a move, update start to be end + 1 and end to be the farthest index that can be reached
in 1 move from the current [start, end].

*/

int jump(vector<int>& nums) {

    int n = nums.size();
    int start = 0, end = 0;
    int steps = 0;

    while(end < n-1)
    {
        steps++;

        int farthestpoint = end+1;
        for(int i=start; i<=end; i++)
        {
            if(i+nums[i] >= n-1)
                return steps;

            farthestpoint = max(farthestpoint, i+nums[i]);
        }

        start = end+1;
        end = farthestpoint;
    }

    return steps;
}
