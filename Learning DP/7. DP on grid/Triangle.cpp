
/*

Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the
current row, you may move to either index i or index i + 1 on the next row.

*/

// TOP-DOWN

int dp[201][201];

int minimumTotal(vector<vector<int>>& triangle) {

    memset(dp, -1, sizeof(dp));
    return solve(triangle, 0, 0);
}

int solve(vector<vector<int>>& triangle, int row, int col)
{
    if(row == triangle.size())
        return 0;

    if(col > row)
        return 0;

    if(dp[row][col] != -1)
        return dp[row][col];

    dp[row][col] = triangle[row][col] +
                min(solve(triangle, row+1, col), solve(triangle, row+1, col+1));

    return dp[row][col];
}



// BOTTOM-UP

int minimumTotal(vector<vector<int>>& triangle) {

    int n = triangle.size();
    int dp[n][n];

    for(int row = n-1; row >= 0; row--)
    {
        for(int col = row; col >= 0; col--)
        {
            if(row == n-1)
                dp[row][col] = triangle[row][col];

            else
                dp[row][col] = triangle[row][col] + min(dp[row+1][col], dp[row+1][col+1]);
        }
    }

    return dp[0][0];
}

