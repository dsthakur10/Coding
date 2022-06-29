
// Detect cycle in Directed graph using DFS

#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<string>

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


bool cycleDFS(DirectedGraph graph);
bool isCycle(DirectedGraph graph, vector<int>& visited, int u, vector<int>& parent);


bool cycleDFS2(DirectedGraph graph);
bool isCycle2(DirectedGraph graph, vector<int>& visited, int u, vector<int>& dfsVisit);


int main()
{
    DirectedGraph graph(9);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(3,6);
    graph.addEdge(4,5);
    graph.addEdge(6,5);
    graph.addEdge(7,2);
    //graph.addEdge(7,8);
    //graph.addEdge(8,9);
    //graph.addEdge(9,7);

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

    if(cycleDFS(graph))
        cout << "Cycle detected";
    else
        cout << "Acyclic";
}



// Method-1 --> using parent array to traverse back all uptil either getting cycle or going back to start of this connected component

bool cycleDFS(DirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> parent(n+1, -1);
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


bool isCycle(DirectedGraph graph, vector<int>& visited, int u, vector<int>& parent)
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

        else
        {
            // u --> current node
            // x --> adjacent node (pre-visited)

            int temp = u;
            while(temp != -1 && temp != x)
                temp = parent[temp];

            if(temp == x)
                return true;
        }
    }

    return false;
}



// Method-2 --> Using DFSvisit[] array to find cycle in O(1) extra time.
// DFSvisit[] will keep track of nodes visited in "current DFS chain call".
// DFSvisit[] will let you know if a particular node is visited again in the same DFS call.
// As soon as your recursive call for a particular node gets over, reset dfsVisit[u] = 0

bool cycleDFS2(DirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> visited(n+1, 0);            // initializing visited with 0's
    vector<int> dfsVisit(n+1,0);

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            if(isCycle(graph, visited, i, dfsVisit))        // in any connected component, if you find cycle, just return TRUE
            {
                return true;
            }
        }

    }
    return false;                           // return FALSE only if no component has a cycle
}


bool isCycle2(DirectedGraph graph, vector<int>& visited, int u, vector<int>& dfsVisit)
{
    visited[u] = 1;
    dfsVisit[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
        {
            if(isCycle(graph, visited, x, dfsVisit))
                return true;
        }

        // Here dfsVisit[x] & visited[x] both are 1 --> This node is already traversed before in "current DFS chain call"
        // --> There is a cycle located at this point.

        else if(dfsVisit[x] == 1)
        {
            return true;
        }
    }

    dfsVisit[u] = 0;            // reseting dfsVisit after the traversing back (once this path is over)
    return false;
}
