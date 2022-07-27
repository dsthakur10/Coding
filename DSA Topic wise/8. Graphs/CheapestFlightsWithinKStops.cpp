
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


// Method-1 --> WRONG APPROACH

// Problem of "Single Pair Shortest Path" which is a subset of "Single Source Shortest Path"
// Extra constraint given in the question : #stops between source & destination <= k


typedef pair<int, int> pi;

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

    vector<int> dist(n, INT_MAX);
    vector<int> hops(n, INT_MAX);
    priority_queue< vector<int>, vector<vector<int>>, greater<vector<int>> > pq;
                                                                        // {distance, vertex, stops}
    vector<vector<pi>> adj = buildGraph(flights, n);

    dist[src] = 0;
    pq.push({dist[src], src, -1});

    while(!pq.empty())
    {
        int curWeight = pq.top()[0];
        int cur = pq.top()[1];
        int stops = pq.top()[2];
        pq.pop();

        if(curWeight > dist[cur])
            continue;

        for(auto it : adj[cur])
        {
            int v = it.first;
            int weight = it.second;

            if(dist[cur] + weight < dist[v] && stops < k)
            {
                dist[v] = dist[cur] + weight;
                pq.push({dist[v], v, stops+1});
            }
        }
    }

    return dist[dst] == INT_MAX ? -1 : dist[dst];
}


vector<vector<pi>> buildGraph(vector<vector<int>>& edges, int n)
{
    vector<vector<pi>> adj(n, vector<pi>());

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        adj[u].push_back({v,w});
    }

    return adj;
}



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

/*
    Constraints for our problem:
        1. Minimum price of the path
        2. Atmost K stops between source & destination
    Because of constraint-2, we cannot use traditional Dijkstra which only checks for 1st constraint.
    We have to modify our algorithm to incorporate the 2nd constraint as well.
    Also, in terms of priority
        2nd constraint > 1st constraint
    Meaning, you CAN afford "costlier path" but CANNOT afford #stops > k.
    You CANNOT afford "cheaper path" with #stops > k.

    Hence, we will keep 2 arrays now --> distance[] | hops[]



*/
