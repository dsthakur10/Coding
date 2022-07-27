/*

Given an m x n integers matrix, return the length of the longest increasing path in matrix.

From each cell, you can either move in four directions: left, right, up, or down.
You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).

Example 1:
Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

Example 2:
Input: matrix = [[3,4,5],[3,2,6],[2,2,1]]
Output: 4
Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.

Example 3:
Input: matrix = [[1]]
Output: 1

*/

int maximum = 1;
vector<vector<int>> dp;
int DIR[5] = {-1, 0, 1, 0, -1};

int longestIncreasingPath(vector<vector<int>>& matrix) {

    int m = matrix.size(), n = matrix[0].size();
    dp = vector<vector<int>> (m, vector<int> (n, -1));

    vector<vector<int>> visited (m, vector<int> (n, 0));
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(dp[i][j] == -1)
                maximum = max(maximum, DFS(matrix, visited, i, j));

            else
                maximum = max(maximum, dp[i][j]);
        }
    }
    return maximum;
}

int DFS(vector<vector<int>>& matrix, vector<vector<int>>& visited, int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    visited[i][j] = 1;
    int m = matrix.size(), n = matrix[0].size();
    int length = 0;
    for(int k=0; k<4; k++)
    {
        int row = i + DIR[k];
        int col = j + DIR[k+1];

        if(row >= m || row < 0 || col >= n || col < 0 ||
           visited[row][col] || matrix[i][j] >= matrix[row][col])
            continue;

        //visited[row][col] = 1;
        length = max(length, DFS(matrix, visited, row, col));
    }

    visited[i][j] = 0;
    return dp[i][j] = 1 + length;
}
