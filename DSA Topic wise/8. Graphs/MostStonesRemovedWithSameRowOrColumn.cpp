/*

On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone

A stone can be removed if it shares either same row or same column as another stone that has not been removed.

Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone,
return the largest possible number of stones that can be removed.

*/


// Logic
// Imagine each stone as node in graph. A stone is connected to another stone if it shares same x or y coordinate.
// Thus our task is to find #connected components in graph. Each connected component in graph can offer you 1 stone.
// Since our task is to find maximum #stones that can be removed, we can remove all stones from
// each component but 1
// Hence result = N - #components


// Method-1 --> DFS (slower method)

vector<vector<int>> buildGraph(vector<vector<int>>& stones)
{
    int n = stones.size();
    vector<vector<int>> adj(n);

    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    return adj;
}


void DFS(vector<vector<int>>& adj, vector<int>& visited, int u)
{
    visited[u] = 1;

    for(int x : adj[u])
    {
        if(!visited[x])
            DFS(adj, visited, x);
    }
}


int removeStones(vector<vector<int>>& stones) {

    int n = stones.size();
    vector<vector<int>> adj = buildGraph(stones);
    vector<int> visited(n, 0);

    int components = 0;
    for(int i=0; i<n; i++)
    {
        if(!visited[i])
        {
            DFS(adj, visited, i);
            components++;
        }
    }

    return n - components;
}



// Method-2 --> DSU

int removeStones(vector<vector<int>>& stones) {

    int n = stones.size();
    UnionFind uf(n);

    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(stones[i][0] == stones[j][0] || stones[i][1] == stones[j][1])
            {
                uf.unionSet(i, j);
            }
        }
    }

    // set will store the root of each connected component --> giving 1 stone for every component
    unordered_set<int> components;

    for(int i=0; i<n; i++)
    {
        components.insert(uf.find(i));
    }

    return n - components.size();
}
