// Number of Provinces

/*
There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b,
and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are
directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

*/


// Method-1 --> Disjoint-set --> Creating edges[] to store edges

int findCircleNum(vector<vector<int>>& isConnected)
{
    int n = isConnected.size();
    vector<vector<int>> edges;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(isConnected[i][j])
                edges.push_back({i,j});
        }
    }

    UnionFind uf(n);

    int provinces = n;
    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        if(!uf.connected(u, v))
        {
            uf.unionSet(u,v);
            provinces--;
        }
    }

    return provinces;
}



// Method-2 --> Disjoint-Set Optimization --> Without creating edges[] array.

int findCircleNum(vector<vector<int>>& isConnected)
{
    int n = isConnected.size();
    int provinces = n;
    UnionFind uf(n);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(isConnected[i][j] && !uf.connected(i,j))
            {
                uf.unionSet(i,j);
                provinces--;
            }
        }
    }

    return provinces;

/*
    unordered_set<int> us;
    for(int i=0; i<n; i++)
    {
        cout << uf.root[i] << " ";
        us.insert(uf.root[i]);
    }

    return us.size();
*/
    // DONOT DO THIS to find #connected components -->
    // This is completely wrong --> Since rank of nodes might differ according to different criteria

}



// Method-3 --> BFS

int findCircleNum(vector<vector<int>>& isConnected) {

    int n = isConnected.size();
    int provinces = 0;
    vector<int> visited(n, 0);

    for(int u=0; u<n; u++)
    {
        if(!visited[u])
        {
            BFS(isConnected, visited, u);
            provinces++;
        }
    }

    return provinces;
}


void BFS(vector<vector<int>>& isConnected, vector<int>& visited, int node)
{
    int n = isConnected.size();
    visited[node] = 1;

    queue<int> q;
    q.push(node);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int v = 0; v < n; v++)
        {
            if(!visited[v] && isConnected[u][v])
            {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
}



// Method-4 --> DFS

int findCircleNum(vector<vector<int>>& isConnected) {

    int n = isConnected.size();
    int provinces = 0;
    vector<int> visited(n, 0);

    for(int u=0; u<n; u++)
    {
        if(!visited[u])
        {
            DFS(isConnected, visited, u);
            provinces++;
        }
    }

    return provinces;
}


void DFS(vector<vector<int>>& isConnected, vector<int>& visited, int u)
{
    int n = isConnected.size();
    visited[u] = 1;

    for(int v = 0; v < n; v++)
    {
        if(!visited[v] && isConnected[u][v])
            DFS(isConnected, visited, v);
    }

}
