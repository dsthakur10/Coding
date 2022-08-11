
// Number of Operations to Make Network Connected

/*
There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network
where connections[i] = [ai, bi] represents a connection between computers ai and bi.
Any computer can reach any other computer directly or indirectly through the network.

You are given an initial computer network connections. You can extract certain cables between two
directly connected computers, and place them between any pair of disconnected computers to make them
directly connected.

Return the minimum number of times you need to do this in order to make all the computers connected.
If it is not possible, return -1
*/


// Method-1 Disjoint-Set

// Keep track of 2 things:
//      1. Components --> number of connected components in graph
//      2. cables --> Edges forming cycle (NOT cut edge)
// You select cables & hand it over to any 2 disconnected components.
// minimum #ways to distribute extra cables to get the graph connected = components - 1
// But you do need to check if you have got enough #cables (cables <= components-1)

int makeConnected(int n, vector<vector<int>>& connections) {

    UnionFind uf(n+1);
    int components = n;
    int cables = 0;

    for(int i=0; i<connections.size(); i++)
    {
        int u = connections[i][0];
        int v = connections[i][1];

        if(!uf.connected(u,v))
        {
            uf.unionSet(u,v);
            components--;
        }

        else
            cables++;
    }

    if(components-1 > cables)
        return -1;
    else
        return components - 1;
}




// Method-2 --> DFS
// How to find components ? --> #times DFS() is called in main() function
// How to find extra cables ? --> #times cycle detected in graph
//      --> (visited[x]=1) && (parent[cur] != x) && (parent != -1)
// (parent != -1) is to stop our function calculate same cyclic edge twice
// (ONLY FOR Starting edge of particular DFS call from main() function).

int components = 0;
int cables = 0;

vector<vector<int>> buildGraph(vector<vector<int>> edges, int n)
{
    vector<vector<int>> adj(n);

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;
}


int makeConnected(int n, vector<vector<int>>& connections) {

    vector<vector<int>> adj = buildGraph(connections, n);
    vector<int> visited(n, 0);

    for(int i=0; i<n; i++)
    {
        if(!visited[i])
        {
            DFS(adj, visited, i, -1);
            components++;
        }
    }

    if(components-1 > cables)
        return -1;
    else
        return components - 1;
}


void DFS(vector<vector<int>>& adj, vector<int>& visited, int node, int parent)
{
    visited[node] = 1;

    for(int x : adj[node])
    {
        if(!visited[x])
            DFS(adj, visited, x, node);

        else if(x != parent && parent != -1)
            cables++;
    }
}



// Method-3 --> DFS | Without maintaining cables
// The only condition you need to be checking: #edges >= n-1
// In a graph with K components --> minimum #edges = n-k {(n-1) - k-1)}
// n-1 --> minimum #edges for graph to be connected {graph is a tree}
// k-1 --> minimum #edges for all the K components to be connected
// our concern is to check if we have minimum #edges to get this graph connected --> connections.size() >= n-1

int components = 0;

vector<vector<int>> buildGraph(vector<vector<int>> edges, int n)
{
    vector<vector<int>> adj(n);

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;
}

int makeConnected(int n, vector<vector<int>>& connections) {

    vector<vector<int>> adj = buildGraph(connections, n);
    vector<int> visited(n, 0);

    for(int i=0; i<n; i++)
    {
        if(!visited[i])
        {
            DFS(adj, visited, i, -1);
            components++;
        }
    }

    if(connections.size() < n-1)
        return -1;

    return components - 1;
}

void DFS(vector<vector<int>>& adj, vector<int>& visited, int node, int parent)
{
    visited[node] = 1;

    for(int x : adj[node])
    {
        if(!visited[x])
            DFS(adj, visited, x, node);
    }
}



// LATEST

int makeConnected(int n, vector<vector<int>>& connections) {

    int x = connections.size();     // total cables in given graph
    int k = n;                      // #connected components

    // if #cables given < minimum #cables needed to make a graph connected, return -1
    if(x < n-1)
        return -1;

    UnionFind uf(n);

    for(int i=0; i<x; i++)
    {
        int u = connections[i][0];
        int v = connections[i][1];

        if(!uf.connected(u, v))
        {
            uf.unionSet(u, v);
            k--;
        }
    }

    return k-1;
}
