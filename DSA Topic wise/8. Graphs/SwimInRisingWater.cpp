/*

You are given an n x n integer grid where each value grid[i][j] represents the elevation at that point (i, j).

The rain starts to fall. At time t, the depth of the water everywhere is t.
You can swim from a square to another 4-directionally adjacent square if and only if the elevation of
both squares individually are at most t. You can swim infinite distances in zero time. Of course,
you must stay within the boundaries of the grid during your swim.

Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at the
top left square (0, 0).

Example 1:
Input: grid = [[0,2],[1,3]]
Output: 3
Explanation:
At time 0, you are in grid location (0, 0).
You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
You cannot reach point (1, 1) until time 3.
When the depth of water is 3, we can swim anywhere inside the grid.

Example 2:
Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
Output: 16
Explanation: The final route is shown.
We need to wait until time 16 so that (0, 0) and (4, 4) are connected.

*/


// LOGIC: min (max (level in path traversal to destination) )

/*

You can swim to adjacent cell only if the level of both cells is same at time t.
Since we are given elevations at different grid locations, rain water keep filling the grid locations
till the level becomes equal to a particular grid location's adjacent cells. Only then swimmer can swim to
adjacent cell.

Your task is to find out minimum time taken by rain water to fill grid cells to certain levels
such that swimmer can reach (n-1) X (n-1)

    This implies that we have to find the minimum of maximum level of any cell in any path to reach BOTTOM-RIGHT.

    --> Find the minimum(maximum cell level in path)
    --> We will use Dijkstra for this.

    --> Path-weight ==> temp = max (grid[nextRow][nextCol], dist[curRow][curCol])

    --> Edge Relaxation --> temp = max (grid[nextRow][nextCol], dist[curRow][curCol])
                            if(temp < dist[nextRow][nextCol])
                                dist[nextRow][nextCol] = temp
    --> We will keep visiting cells until we reach bottom-left cell. Since we are using Dijkstra, it will make sure
        we reach destination in minimum possible path-weight.

*/

int DIR[5] = {-1, 0, 1, 0, -1};

int swimInWater(vector<vector<int>>& grid) {

    int n = grid.size();

    // <distance, row, col>
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    vector<vector<int>> visited(n, vector<int>(n, 0));

    dist[0][0] = grid[0][0];
    pq.push({dist[0][0], 0, 0});
    visited[0][0] = 1;

    while(!pq.empty())
    {
        int curWeight = pq.top()[0];
        int row = pq.top()[1];
        int col = pq.top()[2];
        pq.pop();

        if(row == n-1 && col == n-1)        // destination reached. Return path weight
            return dist[row][col];

        if(curWeight > dist[row][col])      // obsolete entry
            continue;

        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r > n-1 || c > n-1 || r < 0 || c < 0 || visited[r][c])
                continue;

            int x = max(grid[r][c], dist[row][col]);

            if(dist[r][c] > x)
            {
                dist[r][c] = x;
                pq.push({dist[r][c], r, c});
                visited[r][c] = 1;
            }
        }
    }

    return -1;
}
