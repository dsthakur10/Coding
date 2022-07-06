/*

Consider a rat placed at (0, 0) in a square matrix of order N * N. It has to reach the destination at (N - 1, N - 1)
Find all possible paths that the rat can take to reach from source to destination. Directions in which the rat
can move are 'U'(up), 'D'(down), 'L' (left), 'R' (right). Value 0 at a cell in the matrix represents that it is
blocked and rat cannot move to it while value 1 at a cell in the matrix represents that rat can travel through it.

Note: In a path, no cell can be visited more than one time. If the source cell is 0, the rat cannot move to any
other cell.

Example 1:

Input:
N = 4
m[][] = {{1, 0, 0, 0},
         {1, 1, 0, 1},
         {1, 1, 0, 0},
         {0, 1, 1, 1}}

Output: DDRDRR DRDDRR
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR


Example 2:
Input:
N = 2
m[][] = {{1, 0},
         {1, 0}}

Output: -1
Explanation: No path exists and destination cell is blocked.

*/

vector<string> result;
vector<vector<int>> visited;

void dfs(vector<vector<int>>& grid, string& output, int n, int row, int col)
{
    if(grid[row][col] == 0)
        return;

    if(row == n-1 && col == n-1)
    {
        result.push_back(output);
        return;
    }

    // DOWN
    if(row < n-1 && !visited[row+1][col] && grid[row+1][col] == 1)
    {
        visited[row+1][col] = 1;
        output.push_back('D');
        dfs(grid, output, n, row+1, col);
        output.pop_back();
        visited[row+1][col] = 0;
    }

    // LEFT
    if(col > 0 && !visited[row][col-1] && grid[row][col-1] == 1)
    {
        visited[row][col-1] = 1;
        output.push_back('L');
        dfs(grid, output, n, row, col-1);
        output.pop_back();
        visited[row][col-1] = 0;
    }

    // RIGHT
    if(col < n-1 && !visited[row][col+1] && grid[row][col+1] == 1)
    {
        visited[row][col+1] = 1;
        output.push_back('R');
        dfs(grid, output, n, row, col+1);
        output.pop_back();
        visited[row][col+1] = 0;
    }

    // UP
    if(row > 0 && !visited[row-1][col] && grid[row-1][col] == 1)
    {
        visited[row-1][col] = 1;
        output.push_back('U');
        dfs(grid, output, n, row-1, col);
        output.pop_back();
        visited[row-1][col] = 0;
    }
}

vector<string> findPath(vector<vector<int>> &m, int n) {

    visited = vector<vector<int>> (n, vector<int>(n, 0));

    if(m[0][0] == 0)
        return result;

    string output;
    visited[0][0] = 1;
    dfs(m, output, n, 0, 0);
    return result;
}




vector<string> result;
vector<vector<int>> visited;

void dfs(vector<vector<int>>& grid, string& output, int n, int row, int col)
{
    if(grid[row][col] == 0)
        return;

    if(row == n-1 && col == n-1)
    {
        result.push_back(output);
        return;
    }

    if(visited[row][col])
        return;

    visited[row][col] = 1;
    // DOWN
    if(row < n-1 && grid[row+1][col] == 1)
    {
        output.push_back('D');
        dfs(grid, output, n, row+1, col);
        output.pop_back();
    }

    // LEFT
    if(col > 0 && grid[row][col-1] == 1)
    {
        output.push_back('L');
        dfs(grid, output, n, row, col-1);
        output.pop_back();
    }

    // RIGHT
    if(col < n-1 && grid[row][col+1] == 1)
    {
        output.push_back('R');
        dfs(grid, output, n, row, col+1);
        output.pop_back();
    }

    // UP
    if(row > 0 && grid[row-1][col] == 1)
    {
        output.push_back('U');
        dfs(grid, output, n, row-1, col);
        output.pop_back();
    }


    visited[row][col] = 0;
}

vector<string> findPath(vector<vector<int>> &m, int n) {

    visited = vector<vector<int>> (n, vector<int>(n, 0));

    if(m[0][0] == 0)
        return result;

    string output;
    dfs(m, output, n, 0, 0);
    return result;
}
