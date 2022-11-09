
/*

Given a n * m matrix grid where each element can either be 0 or 1. You need to find the shortest distance
between a given source cell to a destination cell. The path can only be created out of a cell if its value is 1.

If the path is not possible between source cell and destination cell, then return -1.

Note : You can move into an adjacent cell if that adjacent cell is filled with element 1.
Two cells are adjacent if they share a side. In other words, you can move in one of the four directions:
Up, Down, Left and Right.

Example 1:

Input:
grid[][] = {{1, 1, 1, 1},
            {1, 1, 0, 1},
            {1, 1, 1, 1},
            {1, 1, 0, 0},
            {1, 0, 0, 1}}
source = {0, 1}
destination = {2, 2}

Output: 3

Example 2:
Input:
grid[][] = {{1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0},
            {1, 0, 1, 0, 1}}
source = {0, 0}
destination = {3, 4}

Output: -1


*/



// path can only be created out of cell if grid[i][j] = 1
typedef vector<int> vec;
int DIR[5] = {-1, 0, 1, 0, -1};

int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                 pair<int, int> destination) {

    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int> (n, INT_MAX));
    priority_queue<vec, vector<vec>, greater<vec>> pq;

    distance[source.first][source.second] = 0;
    pq.push({0, source.first, source.second});
    while(!pq.empty())
    {
        int curDist = pq.top()[0];
        int row = pq.top()[1];
        int col = pq.top()[2];
        pq.pop();

        if(row == destination.first && col == destination.second)
            return curDist;

        if(curDist > distance[row][col])
            continue;

        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= 0 && c >= 0 && r < m && c < n &&
                grid[r][c] && distance[r][c] > curDist + 1)
            {
                distance[r][c] = curDist + 1;
                pq.push({distance[r][c], r, c});
            }
        }
    }

    return -1;
}



// BFS

int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                 pair<int, int> destination) {

    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> distance(m, vector<int> (n, INT_MAX));
    queue<vec> q;

    distance[source.first][source.second] = 0;
    q.push({0, source.first, source.second});
    while(!q.empty())
    {
        int curDist = q.front()[0];
        int row = q.front()[1];
        int col = q.front()[2];
        q.pop();

        if(row == destination.first && col == destination.second)
            return curDist;

        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= 0 && c >= 0 && r < m && c < n &&
                grid[r][c] && distance[r][c] > curDist + 1)
            {
                distance[r][c] = curDist + 1;
                q.push({distance[r][c], r, c});
            }
        }
    }

    return -1;
}



// BFS-2
int DIR[5] = {-1, 0, 1, 0, -1};

int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                 pair<int, int> destination) {

    int m = grid.size();
    int n = grid[0].size();
    queue<pair<int, int>> q;

    int level = 0;
    q.push({source.first, source.second});
    grid[source.first][source.second] = 0;

    while(!q.empty())
    {
        int N = q.size();
        level++;

        while(N > 0)
        {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            N--;

            if(row == destination.first && col == destination.second)
                return level-1;

            for(int k=0; k<4; k++)
            {
                int r = row + DIR[k];
                int c = col + DIR[k+1];

                if(r >= 0 && c >= 0 && r < m && c < n && grid[r][c])
                {
                    q.push({r, c});
                    grid[r][c] = 0;
                }
            }
        }
    }

    return -1;
}
