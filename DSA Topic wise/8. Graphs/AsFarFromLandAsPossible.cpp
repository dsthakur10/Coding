
// As Far from Land as Possible

/*

Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land,
find a water cell such that its DISTANCE TO THE NEAREST LAND CELL IS MAXIMIZED, and return the distance.

If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells
(x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

Example 1:
Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.

Example 2:
Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.

*/



// Manhattan distance clearly shows that grid can be moved 4-directionally --> UP, DOWN, LEFT, RIGHT

// Method-1 --> BFS

/*
    Goal --> Find a water cell(0) such that its DISTANCE TO THE NEAREST LAND CELL(1) IS MAXIMIZED, and return the distance.

    DISTANCE TO THE NEAREST LAND CELL(1) IS MAXIMIZED   =   maximum(minimum(distance of 1-cell from 0-cell))
    dist[1-cells] = 0
    1. Find nearest 1-cell to all 0-cells. Store in dist[][] array
    2. Return maximum distance of all nearest distances (from dist[][])

*/


// Method-1 --> Using extra space to store distance[][]

int maxDistance(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int, int>> q;
    vector<vector<int>> dist(n, vector<int>(n, -1));

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
            {
                dist[i][j] = 0;
                q.push({i,j});
            }
        }
    }

    if(q.empty() || q.size() == n*n)
        return -1;

    int maximum = -1;
    int DIR[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    while(!q.empty())
    {
        int qSize = q.size();

        for(int steps = 0; steps < qSize; steps++)
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for(int i=0; i<4; i++)
            {
                int x = r + DIR[i][0];
                int y = c + DIR[i][1];

                if(x < 0 || y < 0 || x > n-1 || y > n-1 || grid[x][y])
                    continue;

                grid[x][y] = 1;
                dist[x][y] = 1 + dist[r][c];
                q.push({x, y});
            }
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            maximum = max(dist[i][j], maximum);
    }

    return maximum;
}



// Method-2 --> Without using extra space | not using distance[][]

int maxDistance(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int, int>> q;

    int DIR[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(grid[i][j] == 1)
            {
                q.push({i,j});
            }
        }
    }

    if(q.empty() || q.size() == n*n)
        return -1;

    int maximum = 0;
    while(!q.empty())
    {
        int qSize = q.size();
        maximum++;
        for(int steps = 0; steps < qSize; steps++)
        {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for(int i=0; i<4; i++)
            {
                int x = r + DIR[i][0];
                int y = c + DIR[i][1];

                if(x < 0 || y < 0 || x > n-1 || y > n-1 || grid[x][y])
                    continue;

                grid[x][y] = 1;
                q.push({x, y});
            }
        }
    }

    return maximum-1;
}
