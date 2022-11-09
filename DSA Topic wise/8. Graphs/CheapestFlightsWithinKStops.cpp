
// Cheapest Flights Within K Stops

/*
There are n cities connected by some number of flights. You are given an array flights where flights[i] =
[fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with AT MOST K STOPS.
If there is no such route, return -1.

Example 1:


Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
Example 2:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.
Example 3:


Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.


*/


/*
The key difference with the classic Dijkstra algo : We don't maintain the global optimal distance to each node,
i.e. ignore below optimization:

alt = dist[u] + length(u, v)
if alt < dist[v]:

Because there could be routes which are having shorter length but pass more stops, and those routes don't necessarily
constitute the best route in the end. To deal with this, rather than maintaining the optimal routes with 0..K stops for
each node, THE SOLUTION SIMPLY PUT ALL POSSIBLE ROUTES INTO THE PRIORITY QUEUE, so that all of them has a chance to
be processed. IMO, this is the most brilliant part.

And the solution simply returns the first qualified route, it's easy to prove this must be the best route

*/

// Because we are using a minHeap based on cost(fuel price), we are always going to be prioritizing the cheaper route
// (within the constraints of k). so when we get a path that has more steps than the prev visited path,
// we disregard it because we have previously already found a path that's cheaper in cost and fewer in steps.

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
    // create adjacency list
    unordered_map<int,vector<pair<int, int>>> adjList;
    for( auto f : flights )
        adjList[f[0]].push_back( { f[1], f[2] } );

    // minHeap based on cost of distance from source
    priority_queue< vector<int>, vector<vector<int>>, greater<vector<int>> > minHeap;

    minHeap.push( { 0, src, 0 } );              // cost, vertex, hops

    vector<int> dist(n, INT_MAX);               //to avoid TLE --> stores #hops needed to reach vertex v from source

    while( !minHeap.empty() ) {
        auto t = minHeap.top();
        minHeap.pop();
        int cost = t[0];
        int curr = t[1];
        int stop = t[2];

        if( curr == dst )
            return cost;

        if(stop > K )
            continue;

        if(dist[curr]<stop)                     //Optimization to avoid TLE
            continue;

        dist[curr]=stop;

        for( auto next : adjList[curr] )
            minHeap.push( { cost+next.second, next.first, stop+1 });
    }

    return -1;
}



// Own Method

typedef pair<int, int> pi;
typedef pair<int, pair <int, int>> ppi;

vector<vector<pi>> buildGraph(vector<vector<int>>& flights, int n)
{
    vector<vector<pi>> adj(n);

    for(int i=0; i<flights.size(); i++)
    {
        adj[flights[i][0]].push_back({flights[i][1], flights[i][2]});
    }

    return adj;
}

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

    vector<vector<pi>> adj = buildGraph(flights, n);
    queue<ppi> q;
    vector<int> dist(n, INT_MAX);

    dist[src] = 0;
    q.push({0, {src, 0}});

    while(!q.empty())
    {
        auto cur = q.front();
        q.pop();

        int curStops = cur.first;
        int curNode = cur.second.first;
        int curDist = cur.second.second;

        if(curStops > k)
            continue;

        for(auto it : adj[curNode])
        {
            int x = it.first;
            int weight = it.second;

            // if(dist[x] > dist[curNode] + weight && curStops <= k)
            if(dist[x] > curDist + weight && curStops <= k)
            {
                dist[x] = curDist + weight;
                q.push({curStops+1, {x, dist[x]}});
            }
        }
    }

    if(dist[dst] == INT_MAX)
        return -1;

    return dist[dst];
}
