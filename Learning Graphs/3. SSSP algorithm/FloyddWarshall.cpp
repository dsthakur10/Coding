// FloydWarshall Algorithm
// All Pairs Shortest Path

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<unordered_set>
#include<climits>

using namespace std;
typedef pair<int, long> pi;

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


vector<vector<int>> FloydWarshall(DirectedGraph G);

int main()
{
    DirectedGraph graph(5);
    graph.addEdge(1,2,3);
    graph.addEdge(1,3,8);
    graph.addEdge(1,5,-4);
    graph.addEdge(2,4,1);
    graph.addEdge(2,5,7);
    graph.addEdge(3,2,4);
    graph.addEdge(4,1,2);
    graph.addEdge(4,3,-5);
    graph.addEdge(5,4,6);

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();
    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(auto it : node)
            cout << it.first << " ";
    }

    vector<vector<int>> APSP = FloydWarshall(graph);

    cout << "\n APSP:";
    for(int i=0; i<APSP.size(); i++)
    {
        cout << "\n";
        for(int j=0; j<APSP[0].size(); j++)
        {
            cout << APSP[i][j] << " ";
        }
    }

    return 0;
}



vector<vector<int>> FloydWarshall(DirectedGraph G)
{
    int n = G.getNumberOfNodes();
    vector<vector<int>> dist(n+1, vector<int>(n+1, INT_MAX));

    // Create a weight matrix for given graph

    for(int u=1; u<=n; u++)
    {
        dist[u][u] = 0;             // No self-loops allowed

        for(auto x : G.getAdjacentToNode(u))
        {
            int v = x.first;
            long weight = x.second;

            dist[u][v] = weight;
        }
    }

    cout << "\n Matrix:";
    for(int i=0; i<dist.size(); i++)
    {
        cout << "\n";
        for(int j=0; j<dist[0].size(); j++)
        {
            cout << dist[i][j] << " ";
        }
    }

    // No need for extra matrix to store previous results. Storing in the same matrix would just be fine.

    vector<vector<int>> temp;
    for(int k=1; k<=n; k++)
    {
        temp = dist;
        for(int i=1; i<=n ; i++)
        {
            for(int j=1; j<=n; j++)
            {
                // avoid overflow of INF + INF

                if(temp[i][k] != INT_MAX && temp[k][j] != INT_MAX)
                    dist[i][j] = min(temp[i][j], temp[i][k] + temp[k][j]);
            }
        }
    }

    return dist;
}
