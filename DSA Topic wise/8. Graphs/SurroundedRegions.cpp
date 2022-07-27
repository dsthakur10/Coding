/*

Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.
A region is captured by flipping all 'O's into 'X's in that surrounded region.

Example 1:
Input: board = [["X","X","X","X"],
                ["X","O","O","X"],
                ["X","X","O","X"],
                ["X","O","X","X"]]

Output:    [["X","X","X","X"],
            ["X","X","X","X"],
            ["X","X","X","X"],
            ["X","O","X","X"]]

Explanation: Notice that an 'O' should not be flipped if:
- It is on the border, or
- It is adjacent to an 'O' that should not be flipped.
The bottom 'O' is on the border, so it is not flipped.
The other three 'O' form a surrounded region, so they are flipped.

*/


// BFS
void solve(vector<vector<char>>& board) {

    int m = board.size(), n = board[0].size();

    for(int j=0; j<n; j++)
    {
        if(board[0][j] == 'O')
            bfs(board, 0, j);

        if(board[m-1][j] == 'O')
            bfs(board, m-1, j);
    }

    for(int i=0; i<m; i++)
    {
        if(board[i][0] == 'O')
            bfs(board, i, 0);

        if(board[i][n-1] == 'O')
            bfs(board, i, n-1);
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(board[i][j] == '*')
                board[i][j] = 'O';
            else
                board[i][j] = 'X';
        }
    }
}

void bfs(vector<vector<char>>& board, int i, int j)
{
    int m = board.size(), n = board[0].size();
    queue<pair<int, int>> q;

    q.push({i, j});

    while(!q.empty())
    {
        int row = q.front().first;
        int col = q.front().second;
        q.pop();

        if(row >= m || row < 0 || col >= n || col < 0 || board[row][col] == 'X' || board[row][col] == '*')
            continue;

        board[row][col] = '*';

        q.push({row+1, col});
        q.push({row-1, col});
        q.push({row, col+1});
        q.push({row, col-1});
    }
}



// DFS

void solve(vector<vector<char>>& board) {

    int m = board.size(), n = board[0].size();

    for(int j=0; j<n; j++)
    {
        if(board[0][j] == 'O')
            dfs(board, 0, j);

        if(board[m-1][j] == 'O')
            dfs(board, m-1, j);
    }

    for(int i=0; i<m; i++)
    {
        if(board[i][0] == 'O')
            dfs(board, i, 0);

        if(board[i][n-1] == 'O')
            dfs(board, i, n-1);
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(board[i][j] == '*')
                board[i][j] = 'O';
            else
                board[i][j] = 'X';
        }
    }
}


void dfs(vector<vector<char>>& board, int row, int col)
{
    int m = board.size(), n = board[0].size();

    if(row >= m || row < 0 || col >= n || col < 0 || board[row][col] == 'X' || board[row][col] == '*')
            return;

    board[row][col] = '*';

    int dir[] = {-1, 0, 1, 0, -1};

    for(int k=0; k<4; k++)
        dfs(board, row+dir[k], col + dir[k+1]);
}
