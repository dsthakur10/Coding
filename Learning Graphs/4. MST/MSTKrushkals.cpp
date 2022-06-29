
// Krushkal's algorithm for MST

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<unordered_set>
#include<climits>

using namespace std;
typedef pair<int, long> pi;
typedef pair<long, int> pli;        // <distance[u], u>

class UndirectedGraph{

    int nodes;
    vector<vector<pi>> adjList;

public:
    UndirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<pi>> (n+1);
    }

    void addEdge(int u, int v, long w)
    {
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<pi> getAdjacentToNode(int u){
        return adjList[u];
    }
};



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



int findMinimum(vector<int>& key, vector<bool>& mstSet);
vector<pair<int,int>> krushkals(UndirectedGraph graph);

vector<pair<int,int>> krushkals2(UndirectedGraph graph);


int main()
{
    int source;
/*
    UndirectedGraph graph(8);
    graph.addEdge(8,4,10);
    graph.addEdge(8,5,15);
    graph.addEdge(8,6,7);
    graph.addEdge(1,2,6);
    graph.addEdge(1,6,12);
    graph.addEdge(2,3,14);
    graph.addEdge(2,4,8);
    graph.addEdge(2,6,5);
    graph.addEdge(3,4,3);
    graph.addEdge(6,7,9);
*/

    UndirectedGraph graph(9);
    graph.addEdge(9,1,4);
    graph.addEdge(9,7,8);
    graph.addEdge(1,7,11);
    graph.addEdge(1,2,8);
    graph.addEdge(2,3,7);
    graph.addEdge(2,8,2);
    graph.addEdge(2,5,4);
    graph.addEdge(3,4,9);
    graph.addEdge(3,5,14);
    graph.addEdge(4,5,10);
    graph.addEdge(5,6,2);
    graph.addEdge(6,7,1);
    graph.addEdge(6,8,6);
    graph.addEdge(7,8,7);


/*
    UndirectedGraph graph(3);
    graph.addEdge(3,1,5);
    graph.addEdge(1,2,3);
    graph.addEdge(3,2,1);
*/

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();
    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(auto it : node)
            cout << it.first << " ";
    }

    vector<pair<int, int>> mst = krushkals2(graph);

    for(int i=0; i<mst.size(); i++)
        cout << "\n" << mst[i].first << " - " << mst[i].second;

}



// Method-1 --> Using Min-heap

vector<pair<int,int>> krushkals(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;      // min-heap
    UnionFind uf(n+1);
    vector<pair<int,int>> mst;
    int sum = 0;

    // Edges in Non-decreasing order in heap
    for(int u=1; u<=n; u++)
    {
        for(auto x: graph.getAdjacentToNode(u))
        {
            int v = x.first;
            int weight = x.second;

            pq.push({weight, u, v});
        }
    }

    cout << "\n Heap size = " << pq.size();
    int counter = n-1;

    while(!pq.empty() && counter > 0)
    {
        int weight = pq.top()[0];
        int u = pq.top()[1];
        int v = pq.top()[2];
        pq.pop();

        cout << "\n u = " << u << " v = " << v << " weight = " << weight;

        if(!uf.connected(u,v))
        {
            uf.unionSet(u, v);
            sum += weight;
            cout << " sum = "<< sum;
            counter--;
            mst.push_back({u,v});
        }

        else
            cout << " NOT included";
    }

    cout << "\n\nCost of MST = " << sum;
    return mst;
}



// Method-2 --> Using sorted array

vector<pair<int,int>> krushkals2(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<vector<int>> edges;                          // Sorted array
    UnionFind uf(n+1);
    vector<pair<int,int>> mst;
    int sum = 0;

    // Edges in Non-decreasing order in heap
    for(int u=1; u<=n; u++)
    {
        for(auto x: graph.getAdjacentToNode(u))
        {
            int v = x.first;
            int weight = x.second;

            edges.push_back({weight, u, v});
        }
    }

    sort(edges.begin(), edges.end());                   // sorting the edges by weights

    cout << "\n Vector size = " << edges.size();

    for(int i=0, counter = n-1; i<edges.size(), counter > 0; i++)
    {
        int weight = edges[i][0];
        int u = edges[i][1];
        int v = edges[i][2];

        cout << "\n u = " << u << " v = " << v << " weight = " << weight;

        if(!uf.connected(u,v))
        {
            uf.unionSet(u, v);
            sum += weight;
            cout << " sum = " << sum;
            counter--;
            mst.push_back({u,v});
        }

        else
            cout << " NOT included";
    }

    cout << "\n\nCost of MST = " << sum;
    return mst;
}
