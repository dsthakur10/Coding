// Possible Bipartition

/*

We want to split a group of n people (labeled from 1 to n) into two groups of any size.
Each person may dislike some other people, and they should not go into the same group.

Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the
person labeled ai does not like the person labeled bi,
return true if it is possible to split everyone into two groups in this way.

*/


vector<vector<int>> buildGraph(vector<vector<int>>& edges, int n)
{
    vector<vector<int>> adj(n+1, vector<int>());

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    return adj;
}


// BFS
bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

    vector<vector<int>> adj = buildGraph(dislikes, n);
    vector<char> color(n+1, 'W');

    for(int i=1; i<=n; i++)
    {
        if(color[i] == 'W')
        {
            if(!BFS(adj, color, i))
                return false;
        }
    }

    return true;
}


bool BFS(vector<vector<int>>& adj, vector<char>& color, int u)
{
    color[u] = 'R';
    queue<int> q;
    q.push(u);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int x : adj[cur])
        {
            if(color[x] == 'W')
            {
                color[x] = (color[cur] == 'R' ? 'G' : 'R');
                q.push(x);
            }

            else if(color[x] == color[cur])
                return false;
        }
    }

    return true;
}


// DFS

bool possibleBipartition(int n, vector<vector<int>>& dislikes) {

    vector<vector<int>> adj = buildGraph(dislikes, n);
    vector<char> color(n+1, 'W');

    for(int i=1; i<=n; i++)
    {
        if(color[i] == 'W')
        {
            color[i] = 'R';
            if(!DFS(adj, color, i))
                return false;
        }
    }

    return true;
}


bool DFS(vector<vector<int>>& adj, vector<char>& color, int u)
{
    for(int x : adj[u])
    {
        if(color[x] == 'W')
        {
            color[x] = (color[u] == 'R' ? 'G' : 'R');
            if(!DFS(adj, color, x))
                return false;
        }

        else if(color[x] == color[u])
            return false;
    }

    return true;
}
