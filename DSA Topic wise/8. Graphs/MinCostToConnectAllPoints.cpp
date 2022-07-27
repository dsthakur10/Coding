
// Min Cost to Connect All Points


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
        if(root[x] == x)
            return x;

        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if(rootX != rootY)
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



int minCostConnectPoints(vector<vector<int>>& points) {

    int n = points.size();
    vector<vector<int>> edges;

    // Creating edges with vertex numbers & weights
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            int weight = abs(points[i][0] - points[j][0]) +
                    abs(points[i][1] - points[j][1]);

            edges.push_back({weight, i, j});
        }
    }

    UnionFind uf(n);
    sort(edges.begin(), edges.end());

    int sum = 0;
    int counter = 0;
    for(int i=0; i<edges.size(), counter < n-1; i++)
    {
        int weight = edges[i][0];
        int u = edges[i][1];
        int v = edges[i][2];

        if(uf.unionSet(u,v))
        {
            sum += weight;
            counter++;
        }
    }

    return sum;
}
