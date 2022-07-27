/*

You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.
If this is impossible, return -1.

Example 1:
Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:
Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens
4-directionally.

Example 3:
Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.

*/


// WRONG approach
// This method does not take into account all the ways in which a fresh orange can actually get rot.
// minutes can be reduced

// [[2,1,1],[1,1,1],[0,1,2]] --> Our output is 3 --> Correct is 2


int mins = 0;

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 2)
                BFS(grid, i, j);
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
                return -1;
        }
    }

    return mins;
}

void BFS(vector<vector<int>>& grid, int i, int j)
{
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    int localMins = 0;

    q.push({i, j});
    while(!q.empty())
    {
        int number = q.size();

        while(number > 0)
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            number--;

            grid[row][col] = 2;

            if(row < m-1 && grid[row+1][col] == 1)
                q.push({row+1, col});

            if(row > 0 && grid[row-1][col] == 1)
                q.push({row-1, col});

            if(col < n-1 && grid[row][col+1] == 1)
                q.push({row, col+1});

            if(col > 0 && grid[row][col-1] == 1)
                q.push({row, col-1});
        }

        localMins++;
    }

    mins = max(mins, localMins-1);
}



// Correct approach

int mins = 0;

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> minutes(m, vector<int>(n, INT_MAX));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 2)
                BFS(grid, minutes, i, j);
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1 && minutes[i][j] == INT_MAX)
                return -1;

            if(grid[i][j] != 0)
                mins = max(mins, minutes[i][j]);
        }
    }

    return mins;
}


void BFS(vector<vector<int>> grid, vector<vector<int>>& minutes, int i, int j)
{
    int m = grid.size(), n = grid[0].size();
    queue<pair<int, int>> q;
    int localMins = 0;

    q.push({i, j});
    while(!q.empty())
    {
        int number = q.size();

        while(number > 0)
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            number--;

            minutes[row][col] = min(localMins, minutes[row][col]);
            grid[row][col] = 2;

            if(row < m-1 && grid[row+1][col] == 1)
                q.push({row+1, col});

            if(row > 0 && grid[row-1][col] == 1)
                q.push({row-1, col});

            if(col < n-1 && grid[row][col+1] == 1)
                q.push({row, col+1});

            if(col > 0 && grid[row][col-1] == 1)
                q.push({row, col-1});
        }

        localMins++;
    }
}
