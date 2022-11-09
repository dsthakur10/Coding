
// Bellman-Ford algorithm for Single Source Shortest Path from source vertex to every other vertex.
// NOTE: Graph may contain Negative-weight-cycle --> Detect it & return false. Else return SSSP[] array


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

class DirectedGraph{

    int nodes;
    vector<vector<pi>> adjList;

public:
    DirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<pi>> (n+1);
    }

    void addEdge(int u, int v, long w)
    {
        adjList[u].push_back({v,w});
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<pi> getAdjacentToNode(int u){
        return adjList[u];
    }
};


bool BellmanFord(DirectedGraph graph, int source, vector<long>& distance);


int main()
{
    int source;
/*
    DirectedGraph graph(9);
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
*/

    DirectedGraph graph(5);
    graph.addEdge(1,2,-1);
    graph.addEdge(1,3,4);
    graph.addEdge(2,3,3);
    graph.addEdge(2,4,2);
    graph.addEdge(2,5,2);
    graph.addEdge(4,2,1);
    graph.addEdge(4,3,5);
    graph.addEdge(5,4,-3);


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

    vector<long> distance(graph.getNumberOfNodes()+1, INT_MAX);
    bool isNegWeightCycle = BellmanFord(graph, source, distance);

    if(isNegWeightCycle)
        cout << "\n\nNegative weight Cycle exists";

    else
    {
        for(int i=1; i<distance.size(); i++)
            cout << "\n" << source << " - " << i << " : " << distance[i];
    }
    return 0;
}



bool BellmanFord(DirectedGraph graph, int source, vector<long>& distance)
{
    int n = graph.getNumberOfNodes();

    distance[source] = 0;

    for(int i=1; i<n; i++)              // N-1 rounds
    {
        for(int u=1; u<=n; u++)
        {
            for(auto x : graph.getAdjacentToNode(u))
            {
                int v = x.first;
                long weight = x.second;

                if(distance[u] != INT_MAX && distance[u] + weight < distance[v])
                    distance[v] = distance[u] + weight;
            }
        }
    }

    for(int u=1; u<=n; u++)           // Nth round
    {
        for(auto x : graph.getAdjacentToNode(u))
        {
            int v = x.first;
            int weight = x.second;

            if(distance[u] + weight < distance[v])
                return true;
        }
    }

    return false;
}
