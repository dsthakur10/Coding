
// Network Delay Time

/*

You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges
times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to
travel from source to target.

We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal.
If it is impossible for all the n nodes to receive the signal, return -1

*/


// Method-1 --> Dijkstra
typedef pair<int, int> pi;

int networkDelayTime(vector<vector<int>>& times, int n, int k) {

    vector<int> dist(n+1, INT_MAX);
    priority_queue<pi, vector<pi>, greater<pi>> pq;

    vector<vector<pi>> adj = buildGraph(times, n);

    dist[k] = 0;
    pq.push({dist[k], k});

    while(!pq.empty())
    {
        int cur = pq.top().second;
        int curWeight = pq.top().first;
        pq.pop();

        if(curWeight > dist[cur])
            continue;

        for(auto it : adj[cur])
        {
            int v = it.first;
            int weight = it.second;

            if(dist[cur] + weight < dist[v])
            {
                dist[v] = dist[cur] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    int minimum = INT_MIN;
    for(int i=1; i<dist.size(); i++)
    {
        minimum = max(dist[i], minimum);
    }

    return (minimum == INT_MAX ? -1 : minimum);
}

vector<vector<pi>> buildGraph(vector<vector<int>>& edges, int n)
{
    vector<vector<pi>> adj(n+1, vector<pi>());

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        adj[u].push_back({v,w});
    }

    return adj;
}
