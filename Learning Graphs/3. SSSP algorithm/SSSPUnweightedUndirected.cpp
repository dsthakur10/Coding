
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<utility>
#include<climits>

using namespace std;
typedef pair<int, long> pi;

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

    int getWeight(){

        for(int i=1; i<=nodes; i++)
        {
            vector<pi> vec = getAdjacentToNode(i);
            if(!vec.empty())
                return vec[0].second;
        }

        return -1;
    }
};


vector<int> BFS(UndirectedGraph graph, int source);

vector<int> BFS2(UndirectedGraph graph, int source);

int main()
{
    UndirectedGraph graph(9);

    int weight;
    cout << "Enter uniform weights of edges: ";
    cin >> weight;

    graph.addEdge(9,1,weight);
    graph.addEdge(9,3,weight);
    graph.addEdge(1,2,weight);
    graph.addEdge(1,3,weight);
    graph.addEdge(2,6,weight);
    graph.addEdge(3,4,weight);
    graph.addEdge(4,5,weight);
    graph.addEdge(5,6,weight);
    graph.addEdge(6,7,weight);
    graph.addEdge(6,8,weight);
    graph.addEdge(7,8,weight);

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=9; i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);
        cout << "\nNode-" << i << " : ";
        for(auto x : node)
            cout << x.first << " ";
    }

    int source;
    cout << "\n\n Enter SOURCE vertex: ";
    cin >> source;
    cout << "\n\n Single source shortest path from vertex-" << source << " : ";

    vector<int> SSSP = BFS2(graph, source);
    for(int i=1; i<SSSP.size(); i++)
        cout << "\n" << source << " --> " << i << " = " << SSSP[i];

    return 0;
}



// Time --> O(V+E) | Space --> O(V+E) + O(V) + O(V) {Adjacency list, queue, visited array}

vector<int> BFS(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<int> SSSP(n+1, INT_MAX);         // Initially, all the nodes from source node are disconnected, i.e. distance = infinity
    vector<int> visited(n+1, 0);            // initializing visited with 0's
    queue<int> q;

    q.push(source);
    visited[source] = 1;
    SSSP[source] = 0;

    while(!q.empty())
    {
        int cur = q.front();
        int level = SSSP[cur]+1;
        q.pop();

        for(auto it : graph.getAdjacentToNode(cur))
        {
            int x = it.first;
            int weight = it.second;
            if(!visited[x])
            {
                q.push(x);
                visited[x] = 1;
                SSSP[x] = level;
            }

            else
                SSSP[x] = min(level, SSSP[x]);
        }
    }

    for(int i=1; i<SSSP.size(); i++)
    {
        int weight = graph.getWeight();
        if(SSSP[i] != INT_MAX)
            SSSP[i] *= weight;
    }

    return SSSP;
}




vector<int> BFS2(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<int> SSSP(n+1, INT_MAX);         // Initially, all the nodes from source node are disconnected, i.e. distance = infinity
    queue<int> q;

    q.push(source);
    SSSP[source] = 0;
    int weight = graph.getWeight();

    cout << "\n";
    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(auto it : graph.getAdjacentToNode(cur))
        {
            int x = it.first;
            if(SSSP[cur] + weight < SSSP[x])            // if new weight is better than current, push the neighbor & update weight
            {
                SSSP[x] = SSSP[cur] + weight;
                q.push(x);
            }

        /*
            x(any node) will only be pushed once. WHY ??

            In unweighted graphs, SSSP is decided by the levels of nodes w.r.t. source node.
            1st level nodes --> neighbors of source
            2nd level nodes --> neighbors of neighbors of source
            so on....
            The relaxation occurs only once that too at node's respective levels. Because the graph is unweighted.
            Hence the weight via other greater levels DOES NOT count since distance ain't getting better.

            Consider the scenario of source = 9 & node = 5
            Path-1: 9 - 3 - 4 - 5       (distance = 3)
            Path-2: 9 - 1 - 2 - 6 - 5   (distance = 4)

            Node-5 is 3rd level node. So it will be encountered at level 3 first than at any other levels. This automatically
            assigns distance[5] = 3.
            When it gets encountered at 4th level via Node-6, it is at level-4 & so current distance > old one.
            Hence it DOES NOT get into the if() condition.
        */
        }
    }

    return SSSP;
}
