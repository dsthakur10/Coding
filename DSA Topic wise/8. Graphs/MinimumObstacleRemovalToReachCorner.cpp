
/*

shortest path - with no weights -> (bfs always)
shortest path - with weights as 0/1 - > (0/1 bfs always)
shortest path - with any weights( without -ve edge cycle) ->dijkstra always

Q. Is it possible to optimize backtracking code with dp for this problem?

Ans: No. In this question 1 <= m, n <= 10^5, which is toooo big for backtracking;
You cannot use DP here as there are 4 directions and revisiting a node again can give you minimum answer.
So DP fails here ,
    --> Remember one thing - if it's given 4 direction always go with graphs

*/


/*

You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:

0 represents an empty cell,
1 represents an obstacle that may be removed.
You can move up, down, left, or right from and to an empty cell.

Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to
the lower right corner (m - 1, n - 1).

Example 1:
Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:
Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.


*/



// Method-1 --> Dijkstra

int DIR[5] = {-1, 0, 1, 0, -1};

int minimumObstacles(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<vector<int>> dist(m, vector<int> (n, INT_MAX));

    dist[0][0] = 0;
    pq.push({dist[0][0], 0, 0});

    while(!pq.empty())
    {
        int curObstacles = pq.top()[0];
        int row = pq.top()[1];
        int col = pq.top()[2];
        pq.pop();

        if(row == m-1 && col == n-1)
            return curObstacles;

        if(curObstacles > dist[row][col])
            continue;

        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= m || c >= n || r < 0 || c < 0)
                continue;

            int obstacles = curObstacles + grid[r][c];

            if(obstacles < dist[r][c])
            {
                dist[r][c] = obstacles;
                pq.push({dist[r][c], r, c});
            }
        }
    }

    return 0;
}



// Method-2 --> 0-1 BFS

int minimumObstacles(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    deque<vector<int>> dq;

    vector<vector<int>> dist(m, vector<int> (n, INT_MAX));

    dist[0][0] = 0;
    dq.push_front({dist[0][0], 0, 0});

    while(!dq.empty())
    {
        int curObstacles = dq.front()[0];
        int row = dq.front()[1];
        int col = dq.front()[2];
        dq.pop_front();

        if(row == m-1 && col == n-1)
            return curObstacles;

        if(curObstacles > dist[row][col])
            continue;

        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= m || c >= n || r < 0 || c < 0)
                continue;

            int obstacles = curObstacles + grid[r][c];

            if(obstacles < dist[r][c])
            {
                dist[r][c] = obstacles;

                if(grid[r][c] == 0)
                    dq.push_front({dist[r][c], r, c});

                else
                    dq.push_back({dist[r][c], r, c});
            }
        }
    }
    return 0;
}
