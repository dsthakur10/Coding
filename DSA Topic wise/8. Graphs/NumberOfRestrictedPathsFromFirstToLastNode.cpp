
/*

There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph
has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that
there is an edge between nodes ui and vi with weight equal to weighti.

A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end
and there is an edge between zi and zi+1 where 0 <= i <= k-1.

The distance of a path is the sum of the weights on the edges of the path.

    Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x.
    A restricted path is a path that also satisfies that "distanceToLastNode(zi) > distanceToLastNode(zi+1)"
    where 0 <= i <= k-1.

Return the number of restricted paths from NODE 1 TO NODE N.
Since that number may be too large, return it modulo 10^9 + 7.

Example 1:

Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
Output: 3
Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
1) 1 --> 2 --> 5
2) 1 --> 2 --> 3 --> 5
3) 1 --> 3 --> 5

*/


// LOGIC:

/*

    1. Create the graph. You can use a multitude of different data structures but you want to add all the edges
        in an undirected manner and keep track of the weights (you will use them later).

    2. Using Dijkstra's algorithm create the shortest path distance between vertex n and all other nodes.
        Now we have all the shortest paths from each node to the end, we will call this distanceToEnd(node)

    3. Start a DFS traversal from the start node 1 and travel as many different paths that you can.
        HOWEVER the requirement is that you can only move from a node to its neighbor if
        distanceToEnd(node) > distanceToEnd(neighbor)

        It is possible that we can travel multiple paths that reach the same node in its path,
        so we save those calculations for faster lookups --> DP table

*/


// n nodes --> 1 to n
// edges[i] --> [u, v, weight]

typedef pair<int, int> pi;
typedef pair<long long, int> pli;

int mod = 1e9 + 7;
vector<int> dp;

vector<vector<pi>> buildGraph(int n, vector<vector<int>>& edges)
{
    vector<vector<pi>> graph(n+1);

    for(auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];

        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight});
    }

    return graph;
}


int DFS(vector<vector<pi>>& graph, vector<long long>& dist, int u, int n)
{
    if(u == n)
        return dp[n] = 1;

    if(dp[u] != -1)
        return dp[u];

    int temp = 0;
    for(auto it : graph[u])
    {
        int v = it.first;

        if(dist[u] > dist[v])
            temp = ((temp % mod) + (DFS(graph, dist, v, n) % mod)) % mod;
    }

    temp = temp % mod;
    return dp[u] = temp;
}


int countRestrictedPaths(int n, vector<vector<int>>& edges) {

    dp = vector<int>(n+1, -1);
    vector<vector<pi>> graph = buildGraph(n, edges);
    vector<long long> dist(n+1, LLONG_MAX);
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[n] = 0;
    pq.push({0, n});

    while(!pq.empty())
    {
        long long curWeight = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if(curWeight > dist[cur])
            continue;

        for(auto it : graph[cur])
        {
            int x = it.first;
            int weight = it.second;

            if(weight + dist[cur] < dist[x])
            {
                dist[x] = weight + dist[cur];
                pq.push({dist[x], x});
            }
        }
    }

    // start with node-1 (given in problem statement)
    return DFS(graph, dist, 1, n);

}
