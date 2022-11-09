/*



*/


// TYPE - 1 --> All paths from source to destination in minimum possible cost


typedef pair<int, int> pi;

void printPaths(vector<vector<int>>& graph, vector<int>& output,
                int source, int target, int distance, vector<vector<int>>& paths)
{
    cout << "source = " << source << " destination = " << target << " distance = " << distance << "\n";

    if(distance < 0)
        return;

    if(source == target && distance == 0)
    {
        cout << "\n INSIDE \n";
        paths.push_back(output);
        return;
    }

    for(int x : graph[source])
    {
        output.push_back(x);
        printPaths(graph, output, x, target, distance-1, paths);
        output.pop_back();
    }
}


vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

    int n = graph.size();
    vector<vector<int>> paths;
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<int> dist(n, INT_MAX);

    dist[0] = 0;
    pq.push({0,0});
    while(!pq.empty())
    {
        int cur = pq.top().second;
        int curDist = pq.top().first;
        pq.pop();

        if(curDist > dist[cur])
            continue;

        for(int x : graph[cur])
        {
            if(dist[x] > dist[cur] + 1)
            {
                dist[x] = dist[cur] + 1;
                pq.push({dist[x], x});
            }
        }
    }

    vector<int> output;
    output.push_back(0);
    printPaths(graph, output, 0, n-1, dist[n-1], paths);

    return paths;
}


// TYPE - 2 --> All paths from source to destination (no matter the distance)

// DFS

typedef pair<int, int> pi;

void printPaths(vector<vector<int>>& graph, vector<int>& output,
                int source, int target, vector<vector<int>>& paths)
{
    cout << "source = " << source << " destination = " << target << "\n";

    if(source == target)
    {
        cout << "\n INSIDE \n";
        paths.push_back(output);
        return;
    }

    for(int x : graph[source])
    {
        output.push_back(x);
        printPaths(graph, output, x, target, paths);
        output.pop_back();
    }
}


vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

    int n = graph.size();
    vector<vector<int>> paths;
    vector<int> output;
    output.push_back(0);

    printPaths(graph, output, 0, n-1, paths);

    return paths;
}



// Type-3 BFS

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {

    int n = graph.size();
    vector<vector<int>> paths;
    queue<vector<int>> q;

    q.push({0});
    while(!q.empty())
    {
        int N = q.size();

        while(N > 0)
        {
            vector<int> cur = q.front();
            q.pop();
            N--;
            int last = cur.back();

            if(last == n-1)
            {
                paths.push_back(cur);
                continue;
            }

            for(int x : graph[last])
            {
                cur.push_back(x);
                q.push(cur);
                cur.pop_back();
            }
        }
    }

    return paths;
}
