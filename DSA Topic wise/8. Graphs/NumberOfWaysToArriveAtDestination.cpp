
/*

You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between
some intersections. The inputs are generated such that you can reach any intersection from any other intersection
and that there is at most one road between any two intersections.

You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road
between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can
travel from intersection 0 to intersection n - 1 in the shortest amount of time.

Return the number of ways you can arrive at your destination in the shortest amount of time.
Since the answer may be large, return it modulo 109 + 7.


*/

int mod = (int)(1e9 + 7);
typedef pair<long long, int> pl;
typedef pair<int, int> pi;

vector<vector<pi>> buildGraph(int n, vector<vector<int>>& roads)
{
    vector<vector<pi>> graph(n);

    for(int i=0; i<roads.size(); i++)
    {
        graph[roads[i][0]].push_back({roads[i][1], roads[i][2]});
        graph[roads[i][1]].push_back({roads[i][0], roads[i][2]});
    }

    return graph;
}

int countPaths(int n, vector<vector<int>>& roads) {

    vector<vector<pi>> adj = buildGraph(n, roads);

    priority_queue<pl, vector<pl>, greater<pl>> pq;
    vector<long long> dist(n, LLONG_MAX);
    vector<long long> ways(n, 0);

    dist[0] = 0;
    ways[0] = 1;
    pq.push({0,0});
    while(!pq.empty())
    {
        int cur = pq.top().second;
        int curDist = pq.top().first;
        pq.pop();

        if(curDist > dist[cur])
            continue;

        for(auto it : adj[cur])
        {
            int x = it.first;
            int weight = it.second;

            if(dist[x] > dist[cur] + weight)
            {
                dist[x] = dist[cur] + weight;
                pq.push({dist[x], x});
                ways[x] = ways[cur];
            }

            else if(dist[x] == dist[cur] + weight)
                ways[x] = (ways[x] + ways[cur]) % mod;
        }
    }

    return ways[n-1] % mod;
}
