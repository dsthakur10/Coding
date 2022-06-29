
// Dijkstra's algorithm for Single Source Shortest Path from source vertex to every other vertex with
// No negative-weight-cycle


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<unordered_set>
#include<climits>

using namespace std;
typedef pair<int, long> pi;
typedef pair<long, int> pli;        // <distance[u], u>

class UndirectedGraph{

    int nodes;
    vector<vector<pi>> adjList;

public:
    UndirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<pi>> (n+1);
    }

    void addEdge(int u, int v, long w)
    {
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<pi> getAdjacentToNode(int u){
        return adjList[u];
    }
};


vector<long> dijkstra(UndirectedGraph graph, int source);


int main()
{
    int source;

    UndirectedGraph graph(9);
    graph.addEdge(9,1,4);
    graph.addEdge(9,7,8);
    graph.addEdge(1,7,11);
    graph.addEdge(1,2,8);
    graph.addEdge(2,3,7);
    graph.addEdge(2,8,2);
    graph.addEdge(2,5,4);
    graph.addEdge(3,4,9);
    graph.addEdge(3,5,14);
    graph.addEdge(4,5,10);
    graph.addEdge(5,6,2);
    graph.addEdge(6,7,1);
    graph.addEdge(6,8,6);
    graph.addEdge(7,8,7);

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();
    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(auto it : node)
            cout << it.first << " ";
    }

    cout << "\n\nEnter source vertex: ";
    cin >> source;

    vector<long> distance = dijkstra(graph, source);

    for(int i=1; i<distance.size(); i++)
        cout << "\n" << source << " - " << i << " : " << distance[i];

    return 0;
}


// Method-1 --> Using Min-heap | Without using set S for storing visited nodes

/*
    1. Create a distance[] to keep track of SSSP. distance[source] = 0 distance[else] = INT_MAX
    2. Create a min-heap to store {distance[vertex], vertex} pair in increasing order.
    3. Initialize min-heap by pushing {distance[source], source}
    4. While min-heap IS NOT EMPTY:
        a. Pop the top element.
        b. Perform edge relaxation on neighbour of popped elements. --> Update the distance[neighbor]
        c. Push neighbors only if distance gets updated.
    5. Return distance[] array.

*/


// OPTIMIATION WRONG IN LEETCODE TEST CASES.

vector<long> dijkstra(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<long> distance(n+1, INT_MAX);
    distance[source] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    unordered_set<int> S;

    pq.push({distance[source], source});

    while(!pq.empty())
    {
        int cur = pq.top().second;
        pq.pop();
        pair<unordered_set<int>::iterator, bool> p = S.insert(cur);

        //if(p.second){

        // This will let us avoid duplicate entries (already visited nodes --> those whose final dist[] are found)
        // But Is it necessary ? NO --> Since even if we check for repeated nodes, their neighbors ain't getting
        // any better with high dist[cur] value.

        for(auto it: graph.getAdjacentToNode(cur))
        {
            int x = it.first;               // it[0]
            long weight = it.second;        // it[1]

            // if(S.find(x) == S.end()){

            // This will let us avoid checking for relaxation condition as the neighbor x is already in set S.

            if(distance[cur] + weight < distance[x])
            {
                distance[x] = distance[cur] + weight;
                pq.push({distance[x], x});
            }

        //}
        }
    // }
    }
    return distance;
}


// CORRECT WAY --> Optimized

vector<long> dijkstra(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<long> distance(n+1, INT_MAX);
    distance[source] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    pq.push({distance[source], source});

    while(!pq.empty())
    {
        int cur = pq.top().second;
        int curWeight = pq.top().first;
        pq.pop();

        if(curWeight > distance[cur])
            continue;

        for(auto it: graph.getAdjacentToNode(cur))
        {
            int x = it.first;               // it[0]
            long weight = it.second;        // it[1]


            if(distance[cur] + weight < distance[x])
            {
                distance[x] = distance[cur] + weight;
                pq.push({distance[x], x});
            }
        }
    }

    return distance;
}
