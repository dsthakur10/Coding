
// Path-Compression method for Disjoint-Set Data structure --> Optimizes find() function of Quick-Union

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

public:
    UnionFind(int sz) : root(sz)
    {
        for (int i = 0; i < sz; i++)
            root[i] = i;
    }

    int find(int x)
    {
        if (x == root[x])
            return x;

        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
            root[rootY] = rootX;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

};



int main()
{
    cout << boolalpha;              // for displaying booleans as literal strings, instead of 0 and 1

    UnionFind uf(10);

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
