/*

You are given an m x n integer array grid. There is a robot initially located at top-left corner(i.e., grid[0][0]).
The robot tries to move to the bottom-right corner (i.e., grid[m-1][n-1]).
The robot can only move either down or right at any point in time.

AN OBSTACLE AND SPACE ARE MARKED AS 1 OR 0 RESPECTIVELY IN GRID.
A path that the robot takes cannot include any square that is an obstacle.

Return the number of possible unique paths that the robot can take to reach the bottom-right corner.

*/


// TOP-DOWN

// obstacle = 1
// space = 0

int dp[101][101];
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    if(obstacleGrid[0][0] = 1)
        return 0;

    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    memset(dp, -1, sizeof(dp));
    return solve(obstacleGrid, m-1, n-1);

}

int solve(vector<vector<int>>& obstacleGrid, int m, int n)
{
    if(m == 0 && n == 0)
        return 1;

    if(dp[m][n] != -1)
        return dp[m][n];

    if(obstacleGrid[m][n] == 1)
        return dp[m][n] = 0;

    if(m == 0)
        return dp[m][n] = solve(obstacleGrid, m, n-1);

    if(n == 0)
        return dp[m][n] = solve(obstacleGrid, m-1, n);

    dp[m][n] = solve(obstacleGrid, m-1, n) + solve(obstacleGrid, m, n-1);

    return dp[m][n];
}


// BOTTOM-UP

// obstacle = 1
// space = 0

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    int dp[m][n];

    if(obstacleGrid[0][0] == 1)
        return 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i==0 && j==0)
                dp[i][j] = 1;

            else if(i == 0)
                dp[i][j] = (obstacleGrid[i][j] == 0) ? dp[i][j-1] : 0;

            else if(j == 0)
                dp[i][j] = (obstacleGrid[i][j] == 0) ? dp[i-1][j] : 0;

            else
                dp[i][j] = (obstacleGrid[i][j] == 0) ?
                                dp[i][j-1] + dp[i-1][j] : 0;
        }
    }

    return dp[m-1][n-1];
}


// Space optimization - 2D --> 1D

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    if(obstacleGrid[0][0] == 1)
        return 0;

    int m = obstacleGrid.size(), n = obstacleGrid[0].size();

    vector<int> dp(n);          // 1D array for storing values | size = row-size = #columns
    vector<int> temp(n);        // temporary array to store current values

    dp[0] = 1;
    for(int j=1; j<n; j++)                                  // initializing 1st row
        dp[j] = (obstacleGrid[0][j] == 0) ? dp[j-1] : 0;

    for(int i=1; i<m; i++)                                  // starting from 2nd row
    {
        for(int j=0; j<n; j++)
        {
            if(j == 0)
                temp[j] = (obstacleGrid[i][j] == 0) ? dp[j] : 0;

            else
                temp[j] = (obstacleGrid[i][j] == 0) ? temp[j-1] + dp[j] : 0;
        }
        dp = temp;
    }

    return dp[n-1];
}
