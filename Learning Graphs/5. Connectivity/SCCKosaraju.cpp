
// Find all the Strongly connected components of directed graph in O(V+E) using Kosaraju's algorithm

/*
    A directed graph is strongly connected if there is a path between all pairs of vertices.
    A strongly connected component (SCC) of a directed graph is a maximal strongly connected subgraph.
*/


#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<string>
#include<unordered_map>

using namespace std;

class DirectedGraph{

    int nodes;
    vector<vector<int>> adjList;

public:
    DirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<int>> (n+1);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<int> getAdjacentToNode(int u){
        return adjList[u];
    }
};


void transposeGraph(DirectedGraph graph, DirectedGraph& reverseGraph);

void calculateFinishTime(DirectedGraph graph, vector<int>& visited, priority_queue<pair<int, int>>& finishTime, int u);
void calculateFinishTime2(DirectedGraph graph, vector<int>& visited, stack<int>& finishTime, int u);

void calculateSCC(DirectedGraph reverseGraph, vector<int>& visited, int u);

int kosarajuSCC(DirectedGraph graph);


int main()
{
/*
    // Acyclic
    DirectedGraph graph(6);
    graph.addEdge(5,2);
    graph.addEdge(5,6);
    graph.addEdge(4,1);
    graph.addEdge(4,6);
    graph.addEdge(2,3);
    graph.addEdge(3,1);
*/

/*
    DirectedGraph graph(11);
    graph.addEdge(1,2);
    graph.addEdge(1,4);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(8,9);
    graph.addEdge(9,7);
*/
/*
    DirectedGraph graph(5);
    graph.addEdge(1,5);
    graph.addEdge(2,1);
    graph.addEdge(5,2);
    graph.addEdge(5,3);
    graph.addEdge(3,4);
*/

    DirectedGraph graph(8);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(2,5);
    graph.addEdge(2,6);
    graph.addEdge(3,4);
    graph.addEdge(3,7);
    graph.addEdge(4,3);
    graph.addEdge(4,8);
    graph.addEdge(5,1);
    graph.addEdge(5,6);
    graph.addEdge(6,7);
    graph.addEdge(7,6);
    graph.addEdge(7,8);
    graph.addEdge(8,8);


    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

    int numberOfComponents = kosarajuSCC(graph);

    cout << "\n\n Number of Components = " << numberOfComponents;
    return 0;
}



int kosarajuSCC(DirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    int components = 0;
    vector<int> visited(n+1, 0);
    //priority_queue<pair<int, int>> finishTime;        // to store finished time of a vertex (after exploring that particular vertex)
    stack<int> finishTime;
    for(int i=1; i<=n; i++)
    {
        if(!visited[i])
            calculateFinishTime2(graph, visited, finishTime, i);
    }

    DirectedGraph reverseGraph(n);
    transposeGraph(graph, reverseGraph);

    cout << "\n\nReversed Graph:";
    for(int i=1; i<=reverseGraph.getNumberOfNodes(); i++)
    {
        vector<int> node = reverseGraph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

/*
    //cout << "\n Size of heap = "<< finishTime.size();
    while(!finishTime.empty())
    {
        int u = finishTime.top().second;
        finishTime.pop();

        if(visited[u])
        {
            calculateSCC(reverseGraph, visited, u);
            components++;
        }
    }
*/

    while(!finishTime.empty())
    {
        int u = finishTime.top();
        finishTime.pop();

        if(visited[u])
        {
            calculateSCC(reverseGraph, visited, u);
            components++;
        }
    }

    return components;
}


// Using "Max-heap" to sort vertices in the DECREASING order of FINISH times

void calculateFinishTime(DirectedGraph graph, vector<int>& visited, priority_queue<pair<int, int>>& finishTime, int u)
{
    static int counter = 0;
    visited[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
            calculateFinishTime(graph, visited, finishTime, x);
    }

    counter++;
    finishTime.push({counter, u});
}


// Using "stack" to store vertices in DECREASING order of finish time.

void calculateFinishTime2(DirectedGraph graph, vector<int>& visited, stack<int>& finishTime, int u)
{
    visited[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
            calculateFinishTime2(graph, visited, finishTime, x);
    }

    finishTime.push(u);
}



void calculateSCC(DirectedGraph reverseGraph, vector<int>& visited, int u)
{
    visited[u] = 0;

    for(int x : reverseGraph.getAdjacentToNode(u))
    {
        if(visited[x])
            calculateSCC(reverseGraph, visited, x);
    }
}



void transposeGraph(DirectedGraph graph, DirectedGraph& reverseGraph)
{
    int n = graph.getNumberOfNodes();
    for(int i=1; i<=n; i++)
    {
        for(int j : graph.getAdjacentToNode(i))
            reverseGraph.addEdge(j,i);
    }
}
