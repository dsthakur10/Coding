
/*

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right,
which minimizes the sum of all numbers along its path.

NOTE: You can only move either down or right at any point in time.

*/

INCORRECT method

int dp[201][201];

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    memset(dp, -1, sizeof(dp));
    return solve(grid, m-1, n-1);
}

int solve(vector<vector<int>>& grid, int m, int n)
{
    if(m == 0 && n == 0)
        return grid[0][0];

    // this will return 0 which will be minimum of dp[m-1][n] & dp[m][n-1] & we will get sum from invalid path.
    if(m < 0 || n < 0)
        return 0;

    if(dp[m][n] != -1)
        return dp[m][n];

    dp[m][n] = grid[m][n] + min(solve(grid, m-1, n), solve(grid, m, n-1));

    return dp[m][n];
}



// CORRECT Method
// TOP-DOWN

int dp[201][201];

int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    memset(dp, -1, sizeof(dp));
    return solve(grid, m-1, n-1);
}

int solve(vector<vector<int>>& grid, int m, int n)
{
    if(dp[m][n] != -1)
        return dp[m][n];

    if(m == 0 && n == 0)
        return grid[0][0];

    if(m == 0)
        return dp[m][n] = grid[m][n] + solve(grid, m, n-1);

    if(n == 0)
        return dp[m][n] = grid[m][n] + solve(grid, m-1, n);

    dp[m][n] = grid[m][n] + min(solve(grid, m-1, n), solve(grid, m, n-1));

    return dp[m][n];
}


// BOTTOM-UP

int minPathSum(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    int dp[m][n];

    dp[0][0] = grid[0][0];

    for(int i=1; i<m; i++)
        dp[i][0] = grid[i][0] + dp[i-1][0];

    for(int j=1; j<n; j++)
        dp[0][j] = grid[0][j] + dp[0][j-1];

    for(int i=1; i<m; i++)
    {
        for(int j=1; j<n; j++)
            dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
    }

    return dp[m-1][n-1];
}


// Space optimization

int minPathSum(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    vector<int> temp(n);

    dp[0] = grid[0][0];

    for(int j=1; j<n; j++)              // initializing 1st row
        dp[j] = grid[0][j] + dp[j-1];

    for(int i=1; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(j == 0)
                temp[j] = grid[i][j] + dp[j];

            else
                temp[j] = grid[i][j] + min(temp[j-1], dp[j]);
        }

        dp = temp;
    }

    return dp[n-1];
}
