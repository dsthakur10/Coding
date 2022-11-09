/*

You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

Example 1:
Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

Example 2:
Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

Example 3:
Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.

*/


int DIR[5] = {-1, 0, 1, 0, -1};

bool isValid(int row, int col, int m, int n)
{
    if(row > m-1 || col > n-1 || row < 0 || col < 0)
        return false;

    return true;
}


void DFS(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j, int& ones)
{
    int m = grid.size(), n = grid[0].size();

    if(i > m-1 || j > n-1 || i < 0 || j < 0 || visited[i][j] || grid[i][j] == 0)
        return;

    visited[i][j] = 1;
    ones++;

    DFS(grid, visited, i+1,j, ones);
    DFS(grid, visited, i-1,j, ones);
    DFS(grid, visited, i,j+1, ones);
    DFS(grid, visited, i,j-1, ones);
}


void printComponents(vector<vector<int>>& grid, vector<vector<int>>& group, int i, int j, int& ones, int id)
{
    int m = grid.size(), n = grid[0].size();

    if(i > m-1 || j > n-1 || i < 0 || j < 0 || grid[i][j] != 1)
        return;

    grid[i][j] = ones;
    group[i][j] = id;
    printComponents(grid, group, i+1,j, ones, id);
    printComponents(grid, group, i-1,j, ones, id);
    printComponents(grid, group, i,j+1, ones, id);
    printComponents(grid, group, i,j-1, ones, id);

}


int largestIsland(vector<vector<int>>& grid) {

    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> visited(m, vector<int> (n, 0));
    vector<vector<int>> group(m, vector<int> (n, -1));

    int maxArea = 0;
    int id = 1;
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            int ones = 0;
            if(!visited[i][j] && grid[i][j] == 1)
            {
                DFS(grid, visited, i, j, ones);
                printComponents(grid, group, i, j, ones, id);
                id++;
                maxArea = max(ones, maxArea);
            }
        }
    }

    unordered_set<int> seenID;
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            int area = 0;
            seenID.clear();

            if(grid[i][j] == 0)
            {
                for(int k=0; k<4; k++)
                {
                    int row = i + DIR[k];
                    int col = j + DIR[k+1];

                    if(isValid(row, col, m, n) && grid[row][col] != 0
                       && seenID.find(group[row][col]) == seenID.end())
                    {
                        seenID.insert(group[row][col]);
                        area += grid[row][col];
                    }
                }
            }

            maxArea = max(1 + area, maxArea);
        }
    }

    return maxArea;
}
