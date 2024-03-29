
// This implementation of the �disjoint set� is optimized with both �path compression� and �union by rank�.

#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<stack>

using namespace std;


class UnionFind {

private:
    vector<int> root;
    vector<int> rank;

public:
    UnionFind(int sz) : root(sz), rank(sz)
    {
        for (int i = 0; i < sz; i++)
        {
            root[i] = i;
            rank[i] = 1;
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
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

};



int main()
{
    cout << boolalpha;      // for displaying booleans as literal strings, instead of 0 and 1

    UnionFind uf(10);       // Size N+1 because 0 vertex not there

    // 1-2-5-6-7  3-8-9  4
    uf.unionSet(1, 2);
    uf.unionSet(2, 5);
    uf.unionSet(5, 6);
    uf.unionSet(6, 7);
    uf.unionSet(3, 8);
    uf.unionSet(8, 9);

    cout << uf.connected(1, 5) << endl;  // true
    cout << uf.connected(5, 7) << endl;  // true
    cout << uf.connected(4, 9) << endl;  // false

    // 1-2-5-6-7  3-8-9-4
    uf.unionSet(9, 4);

    cout << uf.connected(4, 9) << endl;  // true

    return 0;
}
