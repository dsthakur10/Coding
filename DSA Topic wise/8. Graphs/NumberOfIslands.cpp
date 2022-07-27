
// Number of islands

/*

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.
You may assume all four edges of the grid are all surrounded by water.

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

*/


// Method-1 --> BFS

int numIslands(vector<vector<char>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    vector<vector<int>> visited(m , vector<int> (n, 0));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(!visited[i][j] && grid[i][j] == '1')
            {
                BFS(grid, visited, i, j);
                islands++;
            }
        }
    }

    return islands;
}


void BFS(vector<vector<char>>& grid, vector<vector<int>>& visited, int i, int j)
{
    queue<pair<int,int>> q;
    visited[i][j] = 1;
    q.push({i,j});

    while(!q.empty())
    {
        int cur1 = q.front().first;     // present row
        int cur2 = q.front().second;    // present column
        q.pop();

        // move right
        if(cur2 != grid[0].size()-1 && !visited[cur1][cur2+1] && grid[cur1][cur2+1] == '1')
        {
            visited[cur1][cur2+1] = 1;
            q.push({cur1, cur2+1});
        }

        // move down
        if(cur1 != grid.size()-1 && !visited[cur1+1][cur2] && grid[cur1+1][cur2] == '1')
        {
            visited[cur1+1][cur2] = 1;
            q.push({cur1+1, cur2});
        }

        // move left
        if(cur2 != 0 && !visited[cur1][cur2-1] && grid[cur1][cur2-1] == '1')
        {
            visited[cur1][cur2-1] = 1;
            q.push({cur1, cur2-1});
        }

        // move up
        if(cur1 != 0 && !visited[cur1-1][cur2] && grid[cur1-1][cur2] == '1')
        {
            visited[cur1-1][cur2] = 1;
            q.push({cur1-1, cur2});
        }
    }
}



// Method-2 --> DFS

int numIslands(vector<vector<char>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;
    vector<vector<int>> visited(m , vector<int> (n, 0));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(!visited[i][j] && grid[i][j] == '1')
            {
                DFS(grid, visited, i, j);
                islands++;
            }
        }
    }

    return islands;
}

void DFS(vector<vector<char>>& grid, vector<vector<int>>& visited, int i, int j)
{
    visited[i][j] = 1;

    // move right
    if(j != grid[0].size()-1 && !visited[i][j+1] && grid[i][j+1] == '1')
        DFS(grid, visited, i, j+1);

    // move down
    if(i != grid.size()-1 && !visited[i+1][j] && grid[i+1][j] == '1')
        DFS(grid, visited, i+1, j);

    // move left
    if(j != 0 && !visited[i][j-1] && grid[i][j-1] == '1')
        DFS(grid, visited, i, j-1);

    // move up
    if(i != 0 && !visited[i-1][j] && grid[i-1][j] == '1')
        DFS(grid, visited, i-1, j);

}



// Method-3 --> (Optimized) Without visited array | BFS --> Convert grid blocks to 0 if they are 1

int numIslands(vector<vector<char>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == '1')
            {
                BFS(grid, i, j);
                islands++;
            }
        }
    }

    return islands;
}


void BFS(vector<vector<char>>& grid, int i, int j)
{
    queue<pair<int,int>> q;
    grid[i][j] = '0';
    q.push({i,j});

    while(!q.empty())
    {
        int cur1 = q.front().first;     // present row
        int cur2 = q.front().second;    // present column
        q.pop();
        //grid[cur1][cur2] = '0';

        // You cannot make grid elements 0 here while removing them from IF()

        /*

        When you push the neighbours of the current piece of land you may actually be
        pushing that neighbour multiple times in the course of the entire run.

        Here's an example: [["1", "1"], ["1", "1"]] ( a square island).

        How many times does the bottom right piece of land get pushed onto the queue?

        Twice! Once when BFS goes to the top right corner then again when it goes to the bottom left corner.
        It does this because BFS finishes the neighbours of the top left corner before it moves on to the neighbours of
        its neighbours and you only mark a land piece as visited once you reach it in BFS.

        To fix: every time you push a piece of land onto the queue mark it as "visited" or whatever you're using.

        */

        // move right
        if(cur2 != grid[0].size()-1 && grid[cur1][cur2+1] == '1')
        {
            grid[cur1][cur2+1] = '0';
            q.push({cur1, cur2+1});

            // q.push({cur1, cur2+1});

        }

        // move down
        if(cur1 != grid.size()-1 && grid[cur1+1][cur2] == '1')
        {
            grid[cur1+1][cur2] = '0';
            q.push({cur1+1, cur2});

            // q.push({cur1+1, cur2});
        }

        // move left
        if(cur2 != 0 && grid[cur1][cur2-1] == '1')
        {
            grid[cur1][cur2-1] = '0';
            q.push({cur1, cur2-1});

            // q.push({cur1, cur2-1});
        }

        // move up
        if(cur1 != 0 && grid[cur1-1][cur2] == '1')
        {
            grid[cur1-1][cur2] = '0';
            q.push({cur1-1, cur2});

            // q.push({cur1-1, cur2});
        }
    }
}


// Method-4 --> (Optimized) Without visited array | DFS --> Convert grid blocks to 0 if they are 1

int numIslands(vector<vector<char>>& grid) {

    int m = grid.size();
    int n = grid[0].size();
    int islands = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == '1')
            {
                DFS(grid, i, j);
                islands++;
            }
        }
    }

    return islands;
}

void DFS(vector<vector<char>>& grid, int i, int j)
{
    grid[i][j] = '0';

    // move right
    if(j != grid[0].size()-1 && grid[i][j+1] == '1')
        DFS(grid, i, j+1);

    // move down
    if(i != grid.size()-1 && grid[i+1][j] == '1')
        DFS(grid, i+1, j);

    // move left
    if(j != 0 && grid[i][j-1] == '1')
        DFS(grid, i, j-1);

    // move up
    if(i != 0 && grid[i-1][j] == '1')
        DFS(grid, i-1, j);

}


// Method-5 --> Optimized BFS --> Fancy way of writing conditions to push grid[i][j] into queue using offsets array

int numIslands(vector<vector<char>>& grid)
{
    int m = grid.size(), n = grid[0].size();
    int islands = 0,
    int offsets[] = {0, 1, 0, -1, 0};

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '1')
            {
                islands++;
                grid[i][j] = '0';
                queue<pair<int, int>> todo;
                todo.push({i, j});

                while (!todo.empty())
                {
                    pair<int, int> p = todo.front();
                    todo.pop();
                    for (int k = 0; k < 4; k++)
                    {
                        int r = p.first + offsets[k],
                        int c = p.second + offsets[k + 1];

                        if (r >= 0 && r < m && c >= 0 && c < n && grid[r][c] == '1')
                        {
                            grid[r][c] = '0';
                            todo.push({r, c});
                        }
                    }
                }
            }
        }
    }
    return islands;
}
