// 01 Matrix

/*
Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

Example 1:
Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]

THERE IS AT LEAST ONE 0 IN MAT

*/

// Top-Down DP

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {

    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> dp (m, vector<int>(n,INT_MAX-10000));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
            findLU(dp, mat, i, j);
    }


    for(int i=m-1; i>=0; i--)
    {
        for(int j=n-1; j>=0; j--)
            findRD(dp, mat, i, j);
    }

    return dp;
}

int findRD(vector<vector<int>>& dp, vector<vector<int>>& mat, int i, int j)
{
    int m = mat.size(), n = mat[0].size();

    if(dp[i][j] != INT_MAX-10000)
        return dp[i][j];

    if(mat[i][j] == 0)
    {
        return dp[i][j] = 0;
    }

    if(i != m-1)
        dp[i][j] = min(1 + findRD(dp, mat, i+1, j), dp[i][j]);

    if(j != n-1)
        dp[i][j] = min(1 + findRD(dp, mat, i, j+1), dp[i][j]);

    return dp[i][j];
}


int findLU(vector<vector<int>>& dp, vector<vector<int>>& mat, int i, int j)
{
    int m = mat.size(), n = mat[0].size();

    if(dp[i][j] != INT_MAX-10000)
        return dp[i][j];

    if(mat[i][j] == 0)
    {
        return dp[i][j] = 0;
    }

    if(i != 0)
        dp[i][j] = min(1 + findLU(dp, mat, i-1, j), dp[i][j]);

    if(j != 0)
        dp[i][j] = min(1 + findLU(dp, mat, i, j-1), dp[i][j]);

    return dp[i][j];
}


// Bottom-Up DP

/*

From each 1, the minimum path to 0 could be in any direction. So, we need to check all the 4 directions.
In one iteration from top to bottom, we can check left and top directions, and we need another iteration
from bottom to top to check for right and bottom directions.

Why DP is done in two passes ?
    --> In DP we can only use the values which are previously calculated.
        When we are parsing from top left and coming down to bottom right,
        we can only use the values of above and left because only those two values are precomputed,
        if we take right and down, those values are not yet computed,
        if we work with those values we will get suboptimal answer.

    For example take this test case,

	[1,0,1,1,0,0,1,0,0,1],
	[0,1,1,0,1,0,1,0,1,1],
	[0,0,1,0,1,0,0,1,0,0],
	[1,0,1,0,1,1,1,1,1,1],
	[0,1,0,1,1,0,0,0,0,1],
	[0,0,1,0,1,1,1,0,1,0],
	[0,1,0,1,0,1,0,0,1,1],
	[1,0,0,0,1,1,1,1,0,1],
	[1,1,1,1,1,1,1,0,1,0],
	[1,1,1,1,0,1,0,0,1,1]

the output should be
[
	[1,0,1,1,0,0,1,0,0,1],
	[0,1,1,0,1,0,1,0,1,1],
	[0,0,1,0,1,0,0,1,0,0],
	[1,0,1,0,1,1,1,1,1,1],
	[0,1,0,1,1,0,0,0,0,1],
	[0,0,1,0,1,1,1,0,1,0],
	[0,1,0,1,0,1,0,0,1,1],
	[1,0,0,0,1,2,1,1,0,1],
	[2,1,1,1,1,2,1,0,1,0],
	[3,2,2,1,0,1,0,0,1,1]
]

Now if you notice the left most element of the last row this value should be 3 as per out which is correct
but if we try to parse all sides during the top left to bottom right parsing this happens,

Last two rows look like this

[2, 1, 1, 1, 1, 2, 1, 0, 1, 0]
[1, 1, 1, 1, 0, 1, 0, 0, 1, 1]
 ^

I am talking about updating this one
On above it will see two on right it will see 1 (this is a false value, this value is not yet calculated),
with this value we will incorrectly update this value to 2 instead of 3.


In DP, we can only use prevous values if they're already computed.
In this problem, a cell has at most 4 neighbors that are left, top, right, bottom.
If we use dynamic programming to compute the distance of the current cell based on 4 neighbors simultaneously,
it's impossible because we are not sure if distance of neighboring cells is already computed or not.

That's why, we need to compute the distance one by one:
Firstly, for a cell, we restrict it to only 2 directions which are left and top.
Then we iterate cells from top to bottom, and from left to right, we calculate the distance of a cell based on
its left and top neighbors.
Secondly, for a cell, we restrict it only have 2 directions which are right and bottom.
Then we iterate cells from bottom to top, and from right to left, we update the distance of a cell based on
its right and bottom neighbors.


*/

vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
{
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> dp (m, vector<int>(n,INT_MAX-10000));


    // Bottom-Left
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(mat[i][j] == 0)
                dp[i][j] = 0;
            else
            {
                if(i != 0)
                    dp[i][j] = min(dp[i][j], 1 + dp[i-1][j]);
                if(j != 0)
                    dp[i][j] = min(dp[i][j], 1 + dp[i][j-1]);
            }
        }
    }

    // Top-Right
    for(int i=m-1; i>=0; i--)
    {
        for(int j=n-1; j>=0; j--)
        {
            if(mat[i][j] == 1)
            {
                if(i != m-1)
                    dp[i][j] = min(dp[i][j], 1 + dp[i+1][j]);
                if(j != n-1)
                    dp[i][j] = min(dp[i][j], 1 + dp[i][j+1]);
            }
        }
    }

    return dp;
}



// Method-3 --> BFS --> Shortest path so only BFS can be used

/*
    1. Firstly, we can see that the distance of all zero-cells are 0.
    2. Same idea of Topology Sort, we process zero-cells first, then we use queue to keep the
        order of processing cells, so that cells which have the smaller distance will be processed first.
    3. Then we expand the unprocessed neighbors of the current processing cell and push into our queue.
    4. Afterall, we can achieve the minimum distance of all cells in our matrix.
*/

vector<int> DIR = {0, 1, 0, -1, 0};

vector<vector<int>> updateMatrix(vector<vector<int>>& mat)
{
    int m = mat.size(), n = mat[0].size();
    queue<pair<int, int>> q;

    // We will not be using visited[][] array to keep the track of visited nodes as it will take O(m*n)
    // extra space. Rather we will just mark given matrix as -1 for unvisited nodes.

    for (int r = 0; r < m; ++r)
    {
        for (int c = 0; c < n; ++c)
        {
            if (mat[r][c] == 0)         // Push all the 0 cells into queue. As they are having shortest distance
                q.push({r, c});

            else
                mat[r][c] = -1;         // Marked as not processed yet!
        }
    }

    // mat[r][c]=-1 will work as unvisited nodes.
    while (!q.empty())
    {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        for(int i = 0; i < 4; ++i)
        {
            int nr = r + DIR[i], nc = c + DIR[i+1];

            // if index goes out of bound OR mat[nr][nc] already calculated, then skip next part.
            if (nr < 0 || nr == m || nc < 0 || nc == n || mat[nr][nc] != -1)
                continue;

            mat[nr][nc] = 1 + mat[r][c];
            q.push({nr, nc});
        }
    }

    return mat;
