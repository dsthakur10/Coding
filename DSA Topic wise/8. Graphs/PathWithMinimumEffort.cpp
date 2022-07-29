/*

You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns,
where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0),
and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed).
You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example 1:
Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:
Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells,
which is better than route [1,3,5,3,5].

Example 3:
Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.

*/



// Dijkstra on GRID
// LOGIC --> Change in traditional Dijkstra
/*
    1. Here, we want to minimize the effort of reaching end vertex from source vertex instead of minimizing
        the cost.
    2. Parameter of cost changes here. We do not want to sum up all the edge weights & find minimum to reach
        particular node. Instead we want to choose maximum absolute difference between 2 node's values alongside
        the path to desired node & find the minimum possible maxEffort along the path to destination.
    3. Sum the edge weights along the path --> Maximum difference between neighboring nodes along the path
       Minimize the sum to the destination --> Minimize the maxEffort to the destination

Here, the total path cost is the maximum absolute difference, its a different kind of cost function compared to
the vanilla adding all costs together along the path.

For Dijkstra, edge weight cannot be negative, but what does that really mean.
It effectively means total path cost cannot go down when a new edge joins the path.
In the vanilla Dijkstra, it's in the form of negative edge weight.
If we translate that to this problem, we can see that the total path cost (maximum absolute difference)
will never go down when a new edge joins the path

*/


int DIR[5] = {-1, 0, 1, 0, -1};

int minimumEffortPath(vector<vector<int>>& heights) {

    int m = heights.size(), n = heights[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<vector<int>> dist(m, vector<int> (n, INT_MAX));

    dist[0][0] = 0;
    pq.push({0,0,0});       // distance (effort), row, column

    while(!pq.empty())
    {
        int curEffort = pq.top()[0];
        int row = pq.top()[1];
        int col = pq.top()[2];
        pq.pop();

        if(row == m-1 && col == n-1)
            return curEffort;

        if(curEffort > dist[row][col])
            continue;

        // finding neighbors of current graph
        for(int k = 0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= m || c >= n || r < 0 || c < 0)
                continue;

            int effort = max(curEffort, abs(heights[row][col] - heights[r][c]));

            if(effort < dist[r][c])
            {
                dist[r][c] = effort;
                pq.push({dist[r][c], r, c});
            }
        }
    }

    return 0;
}
