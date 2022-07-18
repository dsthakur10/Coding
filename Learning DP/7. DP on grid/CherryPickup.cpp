
// FIXED STARTING & FIXED ENDING point

/*

You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.

0 means the cell is empty, so you can pass through,
1 means the cell contains a cherry that you can pick up and pass through, or
-1 means the cell contains a thorn that blocks your way.
Return the maximum number of cherries you can collect by following the rules below:

Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells
(cells with value 0 or 1).
After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.

When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.

If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.

*/


// Method-1

/*

We want to reach (n-1, n-1) from (0, 0) & then again comeback to (0, 0) thereby collecting as many cherries as
possible in the way.

Instead of having 2 paths starting from (0, 0) --> (n-1, n-1) & then (n-1, n-1) --> (0, 0), what we can do is
traverse (0, 0) --> (n-1, n-1) TWICE using 2 different players.
    --> Find 2 paths that collects maximum cherries starting from (0, 0) --> (n-1, n-1)

APPROACH-1:
Greedy approach in DP --> Let 1st path be traversed by player-1 & let him collect maximum #cherries possible
Now start traversing 2nd path by player-2 & let him collect maximum #cherries possible from remaining cherries.

This approach will fail --> WHY ? There can be a case where local maximum won't give you global maximum

Example:
11100
00101
10100
00100
00111

APPROACH-2:
We want maximum #cherries collectively --> We have to do traversal of both the paths at the same time & select
global maximum answer.

We will start in reverse order. Considering that both the players are at (n-1, n-1) cell.
There can be only 2 ways: UP or LEFT

AVOID "Duplicate counting"
We just need to keep track of indices of both the players. If both the players arrive at same cell,
count the cherries once.

We can explore all the possibilities from a given cell (r1, c1) of player-1 & (r2, c2) of player-2 & select
the maximum of them.

Hence a 4D DP solution will be required to track the state comprising of both the players simultaneously.

NOTE: If at any point, you discover that indices are out of bounds or grid has thorn (grid[i][j] = -1),
return INT_MIN (-infinty) --> This will never allow parent recursion problem to select this path as we want
maximum of all & there can be nothing smaller that INT_MIN.

*/


int dp[51][51][51][51];

int cherryPickup(vector<vector<int>>& grid) {
    memset(dp, -1, sizeof(dp));
    int n = grid.size();

    return max(0, solve(grid, n-1, n-1 ,n-1 , n-1));
}


int solve(vector<vector<int>>& grid, int r1, int c1, int r2, int c2)
{
    int n = grid.size();
    if(r1 < 0 || r2 < 0 || c1 < 0 || c2 < 0)        // indices go out of bounds --> block this path
        return INT_MIN;

    if(grid[r1][c1] == -1 || grid[r2][c2] == -1)        // thorn appears in the cell --> block this move
        return INT_MIN;

    if(dp[r1][c1][r2][c2] != -1)
        return dp[r1][c1][r2][c2];

    if(r1 == 0 && c1 == 0)                          // player-1 reached the starting point
        return grid[0][0];

    if(r2 == 0 && c2 == 0)                          // player-2 reached the starting point
        return grid[0][0];

    int cherry = 0;
    if(r1 == r2 && c1 == c2)                        // if both players are at same cell, count once
        cherry = grid[r1][c1];

    else                                            // count the cherries of the cells of both players simultaneously
        cherry = grid[r1][c1] + grid[r2][c2];

    cherry += max ( max( solve(grid, r1-1, c1, r2-1, c2), solve(grid, r1-1, c1, r2, c2-1) ),
                    max( solve(grid, r1, c1-1, r2-1, c2), solve(grid, r1, c1-1, r2, c2-1) )
                  );

    return dp[r1][c1][r2][c2] = cherry;
}
