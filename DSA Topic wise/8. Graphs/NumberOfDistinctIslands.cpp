/*

Given a non-empty 2D array grid of 0's and 1's, an island is a group of 1's (representing land) connected
4-directionally (horizontal or vertical). You may assume all four edges of the grid are surrounded by water.

Count the number of distinct islands. An island is considered to be the same as another if and only if one island
has the same shape as another island (and not rotated or reflected).

Notice that:

1 1
1

and

  1
1 1

are considered different island, because we do not consider reflection / rotation

Example 1:
Input:
  [
    [1,1,0,1,1],
    [1,0,0,0,0],
    [0,0,0,0,1],
    [1,1,0,1,1]
  ]
Output: 3

Example 2:
Input:
  [
    [1,1,0,0,0],
    [1,1,0,0,0],
    [0,0,0,1,1],
    [0,0,0,1,1]
  ]
Output: 1

*/


 // U-R-D-B

int DIR[5] = {-1, 0, 1, 0, -1};
set<vector<vector<int>>> us;

int numberofDistinctIslands(vector<vector<int>> &grid) {

    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> visit(m, vector<int> (n, 0));
    vector<vector<int>> coords;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            coords.clear();

            if(!visit[i][j] && grid[i][j])
            {
                DFS(grid, visit, coords, i, j, 0, 0);
                us.insert(coords);
            }
        }
    }
    return us.size();
}

void DFS(vector<vector<int>>& grid, vector<vector<int>>& visit,
            vector<vector<int>>& coords, int row, int col, int X, int Y)
{
    int m = grid.size(), n = grid[0].size();
    visit[row][col] = 1;
    coords.push_back({X, Y});

    for(int k=0; k<4; k++)
    {
        int r = row + DIR[k];
        int c = col + DIR[k+1];
        int x = X + DIR[k];
        int y = Y + DIR[k+1];

        if(r >= 0 && c >= 0 && r <= m-1 && c <= n-1 && !visit[r][c] && grid[r][c])
        {
            DFS(grid, visit, coords, r, c, x, y);
        }
    }
}
