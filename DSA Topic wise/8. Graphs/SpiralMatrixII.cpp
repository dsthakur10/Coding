
/*

Given a positive integer n, generate an n x n matrix filled with elements from 1 to n2 in spiral order.
    Order --> R -> D -> L -> U

*/


// R->D->L->U
// 0-1-2-3

int RD[4] = {0, 1, 0, -1};
int CD[4] = {1, 0, -1, 0};

vector<vector<int>> generateMatrix(int n) {

    vector<vector<int>> result(n , vector<int>(n, 0));

    queue<vector<int>> q;
    q.push({0,0,0});
    int value = 1;

    while(!q.empty())
    {
        int curRow = q.front()[0];
        int curCol = q.front()[1];
        int dir = q.front()[2];
        q.pop();
        result[curRow][curCol] = value;
        value++;

        int counter = 0;
        while(counter < 4)
        {
            int r = curRow + RD[dir];
            int c = curCol + CD[dir];

            if(r >= 0 && c >= 0 && r < n && c < n && !result[r][c])
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
