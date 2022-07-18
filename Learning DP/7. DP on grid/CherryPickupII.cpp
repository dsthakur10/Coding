
// FIXED STARTING & VARIABLE ENDING point

/*

You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of
cherries that you can collect from the (i, j) cell.

You have two robots that can collect cherries for you:

Robot #1 is located at the top-left corner (0, 0), and
Robot #2 is located at the top-right corner (0, cols - 1).
Return the maximum number of cherries collection using both robots by following the rules below:

    1. From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
    2. When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
    3. When both robots stay in the same cell, only one takes the cherries.
    4. Both robots cannot move outside of the grid at any moment.
    5. Both robots should reach the bottom row in grid.

*/


// Method-1 --> 4D matrix --> Memory overflow

// m = rows
// n = columns

int dp[71][71][71][71];
int cherryPickup(vector<vector<int>>& grid) {

    memset(dp, -1, sizeof(dp));

    int m = grid.size(), n = grid[0].size();
    return max(0, solve(grid, 0, 0, 0, n-1));
}

int solve(vector<vector<int>>& grid, int r1, int c1, int r2, int c2)
{
    int m = grid.size(), n = grid[0].size();

    if(c1 >= n || c1 < 0 || c2 >= n || c2 < 0)
        return 0;

    if(r1 == m-1)           // r2 will also be m-1
    {
        if(c1 == c2)
            return grid[r1][c1];
        else
            return grid[r1][c1] + grid[r2][c2];
    }

    if(dp[r1][c1][r2][c2] != -1)
        return dp[r1][c1][r2][c2];

    int cherry = 0;
    if(r1 == r2 && c1 == c2)
        cherry = grid[r1][c1];

    else
        cherry = grid[r1][c1] + grid[r2][c2];

    int maximum = 0;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
            maximum = max(maximum, solve(grid, r1+1, c1+i, r2+1, c2+j));
    }

    return dp[r1][c1][r2][c2] = cherry + maximum;
}



// Method-2 --> 3D DP

/*

If you notice properly, it can be seen that in every iteration row is fixed & is incremented by 1.
So you actually don't need 2 different parameters for row. A single parameter will work for both the robots as
each iteration will lead to +1 in row number.

*/

// m = rows
// n = columns

int dp[71][71][71];
int cherryPickup(vector<vector<int>>& grid) {

    memset(dp, -1, sizeof(dp));

    int m = grid.size(), n = grid[0].size();
    return max(0, solve(grid, 0, 0, n-1));
}

int solve(vector<vector<int>>& grid, int r1, int c1, int c2)
{
    int m = grid.size(), n = grid[0].size();

    if(c1 >= n || c1 < 0 || c2 >= n || c2 < 0)
        return 0;

    if(r1 == m-1)           // r2 will also be m-1
    {
        if(c1 == c2)
            return grid[r1][c1];
        else
            return grid[r1][c1] + grid[r1][c2];
    }

    if(dp[r1][c1][c2] != -1)
        return dp[r1][c1][c2];

    int cherry = 0;
    if(c1 == c2)
        cherry = grid[r1][c1];

    else
        cherry = grid[r1][c1] + grid[r1][c2];

    int maximum = 0;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
            maximum = max(maximum, solve(grid, r1+1, c1+i, c2+j));
    }

    return dp[r1][c1][c2] = cherry + maximum;
}




// BOTTOM-UP

int cherryPickup(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    int dp[m][n][n];

    for(int row = m-1; row >=0; row--)
    {
        for(int col1 = 0; col1 < n; col1++)
        {
            for(int col2 = 0; col2 < n; col2++)
            {
                int x;
                if(col1 == col2)
                    x = grid[row][col1];
                else
                    x = grid[row][col1] + grid[row][col2];

                dp[row][col1][col2] = x;

                if(row != m-1)
                {
                    int maximum = 0;
                    for(int i=-1; i<=1; i++)
                    {
                        for(int j=-1; j<=1; j++)
                        {
                            if(col1+i >= n || col1+i < 0 || col2+j >=n || col2+j < 0)
                                continue;
                            maximum = max(maximum, dp[row+1][col1+i][col2+j]);
                        }
                    }

                    dp[row][col1][col2] += maximum;
                }
            }
        }
    }

    return dp[0][0][n-1];
}
