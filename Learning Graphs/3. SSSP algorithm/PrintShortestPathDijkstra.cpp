

// Find the shortest path from source to destination --> Here, source = 1 | destination = N

// edges = m
// vertices = n

typedef pair<int, int> pi;
vector<int> result;

vector<int> shortestPath(int n, int m, vector<vector<int>>& edges) {

    vector<vector<pi>> adj(n+1);

    for(int i=0; i<m; i++)
    {
        adj[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        adj[edges[i][1]].push_back({edges[i][0], edges[i][2]});
    }

    set<pair<int, int>> sett;
    vector<int> distance(n+1, INT_MAX);
    vector<int> parent(n+1, -1);
    distance[1] = 0;
    parent[1] = -1;

    sett.insert({distance[1], 1});

    while(!sett.empty())
    {
        auto it = *(sett.begin());
        int cur = it.second;
        int curWeight = it.first;
        sett.erase(sett.begin());

        for(auto it: adj[cur])
        {
            int x = it.first;               // it[0]
            int weight = it.second;        // it[1]

            if(distance[cur] + weight < distance[x])
            {
                // delete old entry if it exists
                sett.erase({distance[x], x});

                // update distance & parent --> relax edge
                distance[x] = distance[cur] + weight;
                parent[x] = cur;

                // enter new entry
                sett.insert({distance[x], x});
            }
        }
    }

    // this implies node-n is unreachable from node-1
    if(distance[n] == INT_MAX)
        return {-1};

    int temp = n;
    while(temp != 1)
    {
        result.push_back(temp);
        temp = parent[temp];
    }

    result.push_back(1);
    reverse(result.begin(), result.end());
    return result;
}
