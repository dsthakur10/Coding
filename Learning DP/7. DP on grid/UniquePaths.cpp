/*

There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]).
The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]).
The robot can only move either down or right at any point in time.

Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the
bottom-right corner.

*/


// TOP-DOWN

int dp[101][101];

int uniquePaths(int m, int n) {

    memset(dp, -1, sizeof(dp));
    return solve(m-1, n-1);
}

int solve(int m, int n)
{
    if(m == 0 || n == 0)
        return 1;

    if(dp[m][n] != -1)
        return dp[m][n];

    dp[m][n] = solve(m-1, n) + solve(m, n-1);

    return dp[m][n];
}


// BOTTOM-UP

int uniquePaths(int m, int n) {

    int dp[m][n];

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 1;

            else
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}


// Space optimization - 2D --> 1D

int uniquePaths(int m, int n) {

    vector<int> dp(n);          // 1D array for storing values | size = row-size = #columns
    vector<int> temp(n);        // temporary array to store current values

    for(int j=0; j<n; j++)      // initializing 1st row
        dp[j] = 1;

    for(int i=1; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(j==0)
                temp[j] = 1;

            else
                temp[j] = temp[j-1] + dp[j];    // LEFT (coming from temp[]) + UP (coming from dp[])
        }

        dp = temp;
    }

    return dp[n-1];
}
