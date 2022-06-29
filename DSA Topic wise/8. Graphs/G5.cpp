
// Number of Closed Islands

/*

Given a 2D grid consists of 0s (land) and 1s (water).
An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally
(all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

Example 1:
Input: grid =  [[1,1,1,1,1,1,1,0],
                [1,0,0,0,0,1,1,0],
                [1,0,1,0,1,1,1,0],
                [1,0,0,0,0,1,0,1],
                [1,1,1,1,1,1,1,0]]
Output: 2

Example 2:
Input: grid =  [[0,0,1,0,0],
                [0,1,0,1,0],
                [0,1,1,1,0]]
Output: 1

Example 3:
Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2

*/


// Method-1 --> BFS --> Start from boundaries & convert every single 0-cell to 1
// Start from i=1,j=1 to i=m-2, j=n-2 & convert every single 0-cell to 1. For each BFS/DFS main call increment islands


int closedIsland(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        if(grid[i][0] == 0)
            BFS(grid, i, 0);
    }

    for(int i=0; i<m; i++)
    {
        if(grid[i][n-1] == 0)
            BFS(grid, i, n-1);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[0][j] == 0)
            BFS(grid, 0, j);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[m-1][j] == 0)
            BFS(grid, m-1, j);
    }

    for(int i=1; i<m-1; i++)
    {
        for(int j=1; j<n-1; j++)
        {
            if(grid[i][j]==0)
            {
                BFS(grid, i, j);
                islands++;
            }
        }
    }
    return islands;
}


void BFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();

    grid[i][j] = 1;
    queue<pair<int, int>> q;
    q.push({i,j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        // move down
        if(col != n-1 && grid[row][col+1] == 0)
        {
            grid[row][col+1] = 1;
            q.push({row, col+1});
        }
        // move right
        if(row != m-1 && grid[row+1][col] == 0)
        {
            grid[row+1][col] = 1;
            q.push({row+1, col});
        }
        // move up
        if(col != 0 && grid[row][col-1] == 0)
        {
            grid[row][col-1] = 1;
            q.push({row, col-1});
        }

        // move left
        if(row != 0 && grid[row-1][col] == 0)
        {
            grid[row-1][col] = 1;
            q.push({row-1, col});
        }
    }
}



// Method-2 --> DFS

int closedIsland(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        if(grid[i][0] == 0)
            DFS(grid, i, 0);
    }

    for(int i=0; i<m; i++)
    {
        if(grid[i][n-1] == 0)
            DFS(grid, i, n-1);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[0][j] == 0)
            DFS(grid, 0, j);
    }

    for(int j=0; j<n; j++)
    {
        if(grid[m-1][j] == 0)
            DFS(grid, m-1, j);
    }

    for(int i=1; i<m-1; i++)
    {
        for(int j=1; j<n-1; j++)
        {
            if(grid[i][j]==0)
            {
                DFS(grid, i, j);
                islands++;
            }
        }
    }
    return islands;
}


void DFS(vector<vector<int>>& grid, int i, int j)
{
    grid[i][j] = 1;
    int m = grid.size(), n = grid[0].size();

    // move right
    if(j != n-1 && grid[i][j+1] == 0)
        DFS(grid, i, j+1);

    // move down
    if(i != m-1 && grid[i+1][j] == 0)
        DFS(grid, i+1, j);

    // move left
    if(j != 0 && grid[i][j-1] == 0)
        DFS(grid, i, j-1);

    // move up
    if(i != 0 && grid[i-1][j] == 0)
        DFS(grid, i-1, j);
}


// Method-3 --> BFS

int closedIsland(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 0 && !BFS(grid, i, j))
            {
                islands++;
                cout << i << j;
            }
        }
    }
    return islands;
}


bool BFS(vector<vector<int>>& grid, int i, int j)
{
    bool boundary = false;
    int m = grid.size(), n = grid[0].size();

    grid[i][j] = 1;
    queue<pair<int, int>> q;
    q.push({i,j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if(row == 0 || col == 0 || row == m-1 || col == n-1)
            boundary = true;

        // move down
        if(col != n-1 && grid[row][col+1] == 0)
        {
            grid[row][col+1] = 1;
            q.push({row, col+1});
        }
        // move right
        if(row != m-1 && grid[row+1][col] == 0)
        {
            grid[row+1][col] = 1;
            q.push({row+1, col});
        }
        // move up
        if(col != 0 && grid[row][col-1] == 0)
        {
            grid[row][col-1] = 1;
            q.push({row, col-1});
        }

        // move left
        if(row != 0 && grid[row-1][col] == 0)
        {
            grid[row-1][col] = 1;
            q.push({row-1, col});
        }
    }

    return boundary;
}



// Method-4.1

bool boundary = false;

int closedIsland(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 0 && !DFS(grid, i, j))
                islands++;

            boundary = false;
        }
    }
    return islands;
}


bool DFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();
    grid[i][j] = 1;

    if(i == 0 || j == 0 || i == m-1 || j == n-1)
        boundary = true;

    if(i != 0 && grid[i-1][j] == 0)
       DFS(grid, i-1, j);

    if(i != m-1 && grid[i+1][j] == 0)
       DFS(grid, i+1, j);

    if(j != 0 && grid[i][j-1] == 0)
        DFS(grid, i, j-1);

    if(j != n-1 && grid[i][j+1] == 0)
        DFS(grid, i, j+1);

    return boundary;
}


// Method-4.2 DFS

int closedIsland(vector<vector<int>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 0 && !DFS(grid, i, j))
            {
                islands++;
                //cout << i << j;
            }
        }
    }
    return islands;
}


bool DFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();
    grid[i][j] = 1;
    bool l,r,u,d, boundary;
    l = r = u = d = boundary = false;

    if(i == 0 || j == 0 || i == m-1 || j == n-1)
        boundary = true;

    if(i != 0 && grid[i-1][j] == 0 && DFS(grid, i-1, j))
        u = true;

    if(i != m-1 && grid[i+1][j] == 0 && DFS(grid, i+1, j))
        d = true;

    if(j != 0 && grid[i][j-1] == 0 && DFS(grid, i, j-1))
        l = true;

    if(j != n-1 && grid[i][j+1] == 0 && DFS(grid, i, j+1))
        r = true;

    return u || d || l || r || boundary;
}
