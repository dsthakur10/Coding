/*

Given a n,m which means the row and column of the 2D matrix and an array of pair A( size k).
Originally, the 2D matrix is all 0 which means there is only sea in the matrix.

The list pair has "k operator" and each operator has two integer A[i].x, A[i].y means that you can change the
matrix[A[i].x][A[i].y] from sea to island.

Return how many island are there in the matrix after each operator.
You need to return an array of size K.

Example 1:

Input: m = 4, n = 5, A = [[1,1],[0,1],[3,3],[3,4]]
Output:
[1,1,2,2]
Explanation:

Initially
0.  00000
    00000
    00000
    00000

1.  00000
    01000
    00000
    00000

2.  01000
    01000
    00000
    00000

3.  01000
    01000
    00000
    00010

4.  01000
    01000
    00000
    00011

Example 2:
Input: m = 3, n = 3, A = [[0,0],[0,1],[2,2],[2,1]]
Output: [1,1,2,2]

*/


class UnionFind {

private:
    int comps;
    int totalNodes;
    vector<int> root;
    vector<int> rank;
    vector<int> size;

public:
    UnionFind(int sz) : root(sz), rank(sz), size(sz)
    {
        comps = sz;
        totalNodes = sz;
        for (int i = 0; i < sz; i++)
        {
            root[i] = i;
            rank[i] = 1;
            size[i] = 1;
        }
    }

    int find(int x) {
        if (x == root[x])
            return x;

        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
                root[rootY] = rootX;

            else if (rank[rootX] < rank[rootY])
                root[rootX] = rootY;

            else
            {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }

            size[rootX] += size[rootY];
            size[rootY] = size[rootX];
            comps--;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int getComponents(){
        return comps;
    }
};



// 0 - water
// 1 - island
// For DSU to apply in given problem, you need to convert 2D to 1D --> i*m + j for the coordinate (i, j)

int DIR[5] = {1, 0, -1, 0, 1};

vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {

    UnionFind uf(n*m);
    vector<vector<int>> grid(n, vector<int>(m, 0));
    int islands = 0;
    vector<int> result;

    for(int counter=0; counter<operators.size(); counter++)
    {
        int row = operators[counter][0];
        int col = operators[counter][1];
        int node = row*m + col;

        // if the cell is already visited --> No effect on #islands
        if(grid[row][col])
        {
            result.push_back(islands);
            continue;
        }

        // INCREMENT #islands when a new 1 is added.
        // (This decision to create a new island blindly will be taken care of by the relationship with neighbors)
        grid[row][col] = 1;
        islands++;

        // check for connectedness among the neighbors
        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
            {
                int neighbor = r*m + c;

                // IFF neighbor & current node are not connected && both are 1
                // --> Connect them & DECREMENT #islands
                if(!uf.connected(node, neighbor))
                {
                    islands--;
                    uf.unionSet(node, neighbor);
                }
            }
        }

        result.push_back(islands);
    }

    return result;
}

