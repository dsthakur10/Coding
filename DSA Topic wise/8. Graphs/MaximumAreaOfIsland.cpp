/*

You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally
(horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.

Input: grid =  [[0,0,1,0,0,0,0,1,0,0,0,0,0],
                [0,0,0,0,0,0,0,1,1,1,0,0,0],
                [0,1,1,0,1,0,0,0,0,0,0,0,0],
                [0,1,0,0,1,1,0,0,1,0,1,0,0],
                [0,1,0,0,1,1,0,0,1,1,1,0,0],
                [0,0,0,0,0,0,0,0,0,0,1,0,0],
                [0,0,0,0,0,0,0,1,1,1,0,0,0],
                [0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally

*/


// 1 --> land
// 0 --> water

// BFS

int area = 0;
int maxAreaOfIsland(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
                area = max(area, BFS(grid, i, j));
        }
    }

    return area;
}

int BFS(vector<vector<int>>& grid, int i, int j)
{
    int count = 0;
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;

    q.push({i,j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if(row >= m || row < 0 || col >= n || col < 0 || grid[row][col] == 0)
            continue;

        count++;
        grid[row][col] = 0;

        int dir[] = {-1, 0, 1, 0, -1};

        for(int k=0; k<4; k++)
            q.push({row+dir[k], col+dir[k+1]});

    }

    return count;
}


// DFS

int area = 0;
int maxAreaOfIsland(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
                area = max(area, DFS(grid, i, j));
        }
    }

    return area;
}


int DFS(vector<vector<int>>& grid, int row, int col)
{
    int m = grid.size(), n = grid[0].size();

    if(row >= m || row < 0 || col >= n || col < 0 || grid[row][col] == 0)
        return 0;

    int count = 1;
    grid[row][col] = 0;

    int dir[] = {-1, 0, 1, 0, -1};

    for(int k=0; k<4; k++)
        count += DFS(grid, row+dir[k], col+dir[k+1]);

    return count;
}
