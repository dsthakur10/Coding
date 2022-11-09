/*

Given an m x n matrix, return all elements of the matrix in spiral order.
    Order --> R -> D -> L -> U

Example 1:
Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]


*/


// R->D->L->U
// 0-1-2-3

int RD[4] = {0, 1, 0, -1};
int CD[4] = {1, 0, -1, 0};

vector<int> spiralOrder(vector<vector<int>>& matrix) {

    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> result;
    vector<vector<int>> visited(m, vector<int>(n, 0));

    queue<vector<int>> q;
    q.push({0,0,0});

    while(!q.empty())
    {
        int curRow = q.front()[0];
        int curCol = q.front()[1];
        int dir = q.front()[2];
        q.pop();
        result.push_back(matrix[curRow][curCol]);
        visited[curRow][curCol] = 1;

        int counter = 0;
        while(counter < 4)
        {
            int r = curRow + RD[dir];
            int c = curCol + CD[dir];

            if(r >= 0 && c >= 0 && r < m && c < n && !visited[r][c])
            {
                q.push({r,c,dir});
                break;
            }

            dir = (dir+1) % 4;
            counter++;
        }
    }
    return result;
}
