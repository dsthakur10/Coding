/*
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

*/


// Method-1 --> TOP-DOWN
int dp[46];

int climbStairs(int n) {

    memset(dp, -1, sizeof(dp));
    return maxWaysToClimb(n);
}

int maxWaysToClimb(int n)
{
    if(n < 0)
        return 0;

    if(n == 0)
        return 1;

    if(dp[n] != -1)
        return dp[n];

    dp[n] = maxWaysToClimb(n-1) + maxWaysToClimb(n-2);

    return dp[n];
}



// BOTTOM-UP

int climbStairs(int n) {

    if(n == 1)
        return 1;

    int dp[n+1];

    dp[0] = 1;
    dp[1] = 1;

    for(int i=2; i<n+1; i++)
        dp[i] = dp[i-1] + dp[i-2];

    return dp[n];
}
