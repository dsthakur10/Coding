// Shortest Path in Binary Matrix

/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix.
If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell
(i.e., (n - 1, n - 1)) such that:

All the visited cells of the path are 0.
All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an
edge or a corner).
The length of a clear path is the number of visited cells of this path.


Example 1:
Input: grid = [[0,1],[1,0]]
Output: 2

Example 2:
Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4

Example 3:
Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1

*/


/*
    WHY NOT DP ?
    DP needs a guarantee that its status will be updated in strictly order, here if you can guarantee moving direction only
    follow left -> right, or top to down, then your cost array based on 2D coordinates can use DP; however the question
    allows to move in 8 directions, so only BFS, Dijkstra, A star will work, if no "1" obstacles
    I assume greedy BFS may also work.

    Reason according to me, Is when we are using DP we are saying that we already know the answer of that particular state
    and do not want to keep recalculating it(Like in recursion). But the problem here is since there are 8 directions,
    And say you are traversing from left-up direction then you are not sure of the answer in the right/down positions
    where you have not reached yet.
    For example: If it could have stricted to 2 directions, then we could have used Dp.

*/


// We can optimize this algo by not using extra O(n^2) space of bool vector visited[].
// Since the grid is 0-1 grid. Mark every visited 0 as 1 --> We are not going to access 1-cells anyway.

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if(grid[0][0] != 0 || grid[n-1][n-1] != 0)
        return -1;

    int d[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    queue<pair<int,int>> q;
    vector<vector<bool>> visited(n,vector(n,false));
    int ans = 0;

    q.push({0,0});
    //visited[0][0] = true;
    while(!q.empty())
    {
        int qSize = q.size();
        ans++;

        for(int i=0; i<qSize; i++)
        {
            int x = q.front().first;
            int y = q.front().second;
            q.pop();

            if(x == n-1 && y == n-1)
                return ans;

            for(int j=0; j<8; j++)
            {
                int r = x + d[j][0];
                int c = y + d[j][1];

                if(r < 0 || r > n-1 || c < 0 || c > n-1 || grid[r][c]) // || visited[r][c]
                    continue;

                //visited[r][c] = 1;
                grid[r][c] = 1;
                q.push({r,c});
            }
        }
    }

    return -1;
}



// NOT OPTIMIZED
int DIR[9] = {-1, 0, -1 , 1, 1, 0, 1, -1, -1};

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

    int n = grid.size();

    if(grid[0][0] == 1 || grid[n-1][n-1] == 1)
        return -1;

    return BFS(grid, 0, 0);
}

int BFS(vector<vector<int>>& grid, int i, int j)
{
    int n = grid.size();
    queue<vector<int>> q;

    q.push({i, j, 1});

    while(!q.empty())
    {
        int row = q.front()[0];
        int col = q.front()[1];
        int dist = q.front()[2];
        q.pop();

        if(row >= n || row < 0 || col >= n || col < 0 || grid[row][col] == 1)
            continue;

        if(row == n-1 && col == n-1)
            return dist;

        grid[row][col] = 1;
        for(int k=0; k<8; k++)
            q.push({row + DIR[k], col + DIR[k+1], dist+1});
    }

    return -1;
}
