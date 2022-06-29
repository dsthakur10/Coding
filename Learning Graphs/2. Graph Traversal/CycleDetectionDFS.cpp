
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<string>

using namespace std;

class UndirectedGraph{

    int nodes;
    vector<vector<int>> adjList;

public:
    UndirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<int>> (n+1);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<int> getAdjacentToNode(int u){
        return adjList[u];
    }
};


bool cycleDFS(UndirectedGraph graph);
bool isCycle(UndirectedGraph graph, vector<int>& visited, int u, vector<int>& parent);

bool cycleDFS2(UndirectedGraph graph);
bool isCycle2(UndirectedGraph graph, vector<int>& visited, int u, int parent);


int main()
{
/*
    UndirectedGraph graph(7);
    graph.addEdge(1,2);
    graph.addEdge(2,4);
    graph.addEdge(2,7);
    graph.addEdge(3,5);
    graph.addEdge(6,7);
    graph.addEdge(4,6);
*/


    // cycle
    UndirectedGraph graph(11);
    graph.addEdge(1,2);
    graph.addEdge(1,4);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(7,9);


/*
    // Acyclic
    UndirectedGraph graph(8);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(2,7);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(5,6);
    graph.addEdge(7,8);
*/

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

    cout << "\n\n DFS Cycle detection : ";

    if(cycleDFS2(graph))
        cout << "Cycle detected";
    else
        cout << "Acyclic";
}



bool cycleDFS(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> parent(n+1, 0);
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            if(isCycle(graph, visited, i, parent))        // in any connected component, if you find cycle, just return TRUE
                return true;
        }
    }

    return false;                           // return FALSE only if no component has a cycle
}


bool isCycle(UndirectedGraph graph, vector<int>& visited, int u, vector<int>& parent)
{
    visited[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
        {
            parent[x] = u;
            if(isCycle(graph, visited, x, parent))
                return true;
        }

        else if(parent[u] != x)
            return true;
    }

    return false;
}




bool cycleDFS2(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            if(isCycle2(graph, visited, i, -1))        // in any connected component, if you find cycle, just return TRUE
                return true;
        }
    }

    return false;                           // return FALSE only if no component has a cycle
}


bool isCycle2(UndirectedGraph graph, vector<int>& visited, int u, int parent)
{
    visited[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
        {
            if(isCycle2(graph, visited, x, u))
                return true;
        }

        else if(parent != x)
            return true;
    }

    return false;
}

