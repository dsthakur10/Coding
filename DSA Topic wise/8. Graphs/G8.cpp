
//  Coloring A Border

/*
You are given an m x n integer matrix grid, and three integers row, col, and color.
Each value in the grid represents the color of the grid square at that location.

Two squares belong to the same connected component if they have the same color and are next to each other
in any of the 4 directions.

The border of a connected component is all the squares in the connected component that are either
4-directionally adjacent to a square not in the component, or on the boundary of the grid
(the first or last row or column).

You should color the border of the connected component that contains the square grid[row][col] with color.

Return the final grid.

Example 1:
Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
Output: [[3,3],[3,2]]

Example 2:
Input: grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
Output: [[1,3,3],[2,3,3]]

Example 3:
Input: grid = [[1,1,1],[1,1,1],[1,1,1]], row = 1, col = 1, color = 2
Output: [[2,2,2],[2,1,2],[2,2,2]]

*/


/*
    1. From an initial point, perform DFS and flip the cell color to negative to track visited cells.

    2. After DFS is complete for the cell, check if this cell is inside.
        If so, flip its color back to the positive.

    3. In the end, cells with the negative color are on the border. Change their color to the target color

*/



vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {

    int m = grid.size(), n = grid[0].size();

    DFS(grid, row, col, grid[row][col]);

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            grid[i][j] = grid[i][j] < 0 ? color : grid[i][j];
        }
    }

    return grid;
}

void DFS(vector<vector<int>>& grid, int i, int j, int compColor)
{
    // 1. Flipping color to negative to track the record

    int m = grid.size(), n = grid[0].size();
    grid[i][j] = -compColor;

    // move right
    if(j != n-1 && grid[i][j+1] == compColor)
        DFS(grid, i, j+1, compColor);

    // move down
    if(i != m-1 && grid[i+1][j] == compColor)
        DFS(grid, i+1, j, compColor);

    // move left
    if(j != 0 && grid[i][j-1] == compColor)
        DFS(grid, i, j-1, compColor);

    // move up
    if(i != 0 && grid[i-1][j] == compColor)
        DFS(grid, i-1, j, compColor);

    // 2. Reverting the color to positive only if the cell is inside the border

    if(i != 0 && i != m-1 && j != 0 && j != n-1 && abs(grid[i-1][j]) == compColor && abs(grid[i+1][j]) == compColor && abs(grid[i][j-1]) == compColor && abs(grid[i][j+1]) == compColor)
    {
        grid[i][j] = compColor;
    }
}
