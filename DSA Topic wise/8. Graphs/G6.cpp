
// Number of Enclaves

/*

You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

Example 1:
Input: grid =  [[0,0,0,0],
                [1,0,1,0],
                [0,1,1,0],
                [0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.

Example 2:
Input: grid =  [[0,1,1,0],
                [0,0,1,0],
                [0,0,1,0],
                [0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.


*/



// Method-1 --> BFS

int numEnclaves(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int enc = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
                enc += BFS(grid, i, j);
        }
    }
    return enc;
}


int BFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();
    int enc = 0;
    bool boundary = false;

    queue<pair<int, int>> q;
    grid[i][j] = 0;
    q.push({i,j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();
        enc++;

        cout << "i" << row << " j = " << col;

        if(row == 0 || row == m-1 || col == 0 || col == n-1)
            boundary = true;

        // move right
        if(col != n-1 && grid[row][col+1] == 1)
        {
            grid[row][col+1] = 0;
            q.push({row, col+1});
        }

        // move down
        if(row != m-1 && grid[row+1][col] == 1)
        {
            grid[row+1][col] = 0;
            q.push({row+1, col});
        }

        // move left
        if(col != 0 && grid[row][col-1] == 1)
        {
            grid[row][col-1] = 0;
            q.push({row, col-1});
        }

        // move up
        if(row != 0 && grid[row-1][col] == 1)
        {
            grid[row-1][col] = 0;
            q.push({row-1, col});
        }
    }

    if(boundary)
        return 0;

    return enc;
}



// Method-2 --> DFS

int count = 0;
bool boundary = false;

int numEnclaves(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int enc = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
            {
                DFS(grid, i, j);
                enc += count;

                count = 0;
                boundary = false;
            }
        }
    }
    return enc;
}


void DFS(vector<vector<int>>& grid, int i, int j)
{
    grid[i][j] = 0;
    int m = grid.size(), n = grid[0].size();
    count++;

    if(i == 0 || i == m-1 || j == 0 || j == n-1)
        boundary = true;

    // move right
    if(j != n-1 && grid[i][j+1] == 1)
        DFS(grid, i, j+1);

    // move down
    if(i != m-1 && grid[i+1][j] == 1)
        DFS(grid, i+1, j);

    // move left
    if(j != 0 && grid[i][j-1] == 1)
        DFS(grid, i, j-1);

    // move up
    if(i != 0 && grid[i-1][j] == 1)
        DFS(grid, i-1, j);

    if(boundary)
        count = 0;
}



// Method-3 --> BFS

int numEnclaves(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int enc = 0;

    for(int i=0; i<m; i++)
    {
        if(grid[i][0] == 1)
            BFS(grid, i, 0);
    }

    for(int i=0; i<m; i++)
    {
        if(grid[i][n-1] == 1)
            BFS(grid, i, n-1);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[0][j] == 1)
            BFS(grid, 0, j);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[m-1][j] == 1)
            BFS(grid, m-1, j);
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j])
                enc++;
        }
    }

    return enc;
}


void BFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();

    grid[i][j] = 0;
    queue<pair<int, int>> q;
    q.push({i,j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // move down
        if(col != n-1 && grid[row][col+1] == 1)
        {
            grid[row][col+1] = 0;
            q.push({row, col+1});
        }
        // move right
        if(row != m-1 && grid[row+1][col] == 1)
        {
            grid[row+1][col] = 0;
            q.push({row+1, col});
        }
        // move up
        if(col != 0 && grid[row][col-1] == 1)
        {
            grid[row][col-1] = 0;
            q.push({row, col-1});
        }

        // move left
        if(row != 0 && grid[row-1][col] == 1)
        {
            grid[row-1][col] = 0;
            q.push({row-1, col});
        }
    }
}



// Method-4 --> DFS

int numEnclaves(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int enc = 0;

    for(int i=0; i<m; i++)
    {
        if(grid[i][0] == 1)
            DFS(grid, i, 0);
    }

    for(int i=0; i<m; i++)
    {
        if(grid[i][n-1] == 1)
            DFS(grid, i, n-1);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[0][j] == 1)
            DFS(grid, 0, j);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[m-1][j] == 1)
            DFS(grid, m-1, j);
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j])
                enc++;
        }
    }

    return enc;
}


void DFS(vector<vector<int>>& grid, int i, int j)
{
    grid[i][j] = 0;
    int m = grid.size(), n = grid[0].size();

    // move right
    if(j != n-1 && grid[i][j+1] == 1)
        DFS(grid, i, j+1);

    // move down
    if(i != m-1 && grid[i+1][j] == 1)
        DFS(grid, i+1, j);

    // move left
    if(j != 0 && grid[i][j-1] == 1)
        DFS(grid, i, j-1);

    // move up
    if(i != 0 && grid[i-1][j] == 1)
        DFS(grid, i-1, j);
}
