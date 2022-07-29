/*

You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where
edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing
that edge succProb[i].

Given two nodes start and end, find the path with the maximum probability of success to go from start to end and
return its success probability.

If there is no path from start to end, return 0.

Example 1:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
Output: 0.25000
Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.

Example 2:
Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.3], start = 0, end = 2
Output: 0.30000

Example 3:
Input: n = 3, edges = [[0,1]], succProb = [0.5], start = 0, end = 2
Output: 0.00000
Explanation: There is no path between 0 and 2.

*/


// LOGIC --> Change in traditional Dijkstra
/*
    1. Here, we want to maximize the probability of reaching end vertex from source vertex instead of minimizing
        the cost.
    2. Use Max-heap instead of Min-heap because we want maximum probability of path.
    3. Initialize distance[] with 0 (minimum value) rather than DBL_MAX (maximum possible value)
    4. dist[start] = 1 --> probability of reaching start --> start = 1
    5. We don't sum edge weights here. We multiply edge weights (since edge weights are probability)

*/

typedef pair<double, int> pdi;
typedef pair<int, double> pid;

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    vector<vector<pid>> adj(n);

    for(int i=0; i<edges.size(); i++)
    {
        adj[edges[i][0]].push_back({edges[i][1], succProb[i]});
        adj[edges[i][1]].push_back({edges[i][0], succProb[i]});
    }

    //priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    priority_queue<pdi> pq;                                     // max-heap
    vector<double> dist(n, 0);                          // initialize with 0

    dist[start] = 1;                                    // source vertex probability = 1 (start --> start)
    pq.push({dist[start], start});

    while(!pq.empty())
    {
        int cur = pq.top().second;
        double curWeight = pq.top().first;
        pq.pop();

        for(auto it : adj[cur])
        {
            int x = it.first;
            double weight = it.second;

            if(dist[cur] * weight > dist[x])            // multiply probability to get maximum possible probability
            {
                dist[x] = dist[cur] * weight;
                pq.push({dist[x], x});
            }
        }
    }

    return dist[end];
}



// optimization --> return dist[end] as soon as it appears on TOP of PQ

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    vector<vector<pid>> adj(n);

    for(int i=0; i<edges.size(); i++)
    {
        adj[edges[i][0]].push_back({edges[i][1], succProb[i]});
        adj[edges[i][1]].push_back({edges[i][0], succProb[i]});
    }

    //priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    priority_queue<pdi> pq;
    vector<double> dist(n, 0);

    dist[start] = 1;
    pq.push({dist[start], start});

    while(!pq.empty())
    {
        int cur = pq.top().second;
        double curWeight = pq.top().first;
        pq.pop();

        if(cur == end)
            return curWeight;

        for(auto it : adj[cur])
        {
            int x = it.first;
            double weight = it.second;

            if(dist[cur] * weight > dist[x])
            {
                dist[x] = dist[cur] * weight;
                pq.push({dist[x], x});
            }
        }
    }

    return 0;
}
