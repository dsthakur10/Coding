#include<iostream>
#include<vector>
#include<queue>
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


// using parent array
bool cycleBFS(UndirectedGraph graph);

bool cycleBFS2(UndirectedGraph graph);
bool isCycle2(UndirectedGraph graph, vector<int>& visited, int u, vector<int>& parent);


// using a single parent node alongside current node. (pair)

bool cycleBFS3(UndirectedGraph graph);
bool isCycle3(UndirectedGraph graph, vector<int>& visited, int u);


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

/*
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
*/


    // Acyclic
    UndirectedGraph graph(8);
    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(2,7);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(5,6);
    graph.addEdge(7,8);


    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

    cout << "\n\n BFS Cycle detection : ";

    if(cycleBFS3(graph))
        cout << "Cycle detected";
    else
        cout << "Acyclic";
}




bool cycleBFS(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    queue<int> q;
    vector<int> parent(n+1, 0);
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            visited[i] = 1;
            q.push(i);

            while(!q.empty())
            {
                int cur = q.front();
                q.pop();

                for(int x : graph.getAdjacentToNode(cur))
                {
                    if(!visited[x])
                    {
                        parent[x] = cur;
                        visited[x] = 1;

                        q.push(x);
                    }

                    else if(parent[cur] != x)               // return TRUE if any one component has got cycle in it.
                        return true;
                }
            }
        }
    }

    return false;                           // return FALSE only if no component has a cycle
}




bool cycleBFS2(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> parent(n+1, 0);
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            if(isCycle2(graph, visited, i, parent))        // in any connected component, if you find cycle, just return TRUE
                return true;
        }
    }

    return false;                           // return FALSE only if no component has a cycle
}



bool isCycle2(UndirectedGraph graph, vector<int>& visited, int u, vector<int>& parent)
{
    queue<int> q;
    visited[u] = 1;
    q.push(u);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int x : graph.getAdjacentToNode(cur))
        {
            if(!visited[x])
            {
                parent[x] = cur;
                visited[x] = 1;

                q.push(x);
            }

            else if(parent[cur] != x)
                return true;
        }
    }

    return false;
}



// Method-3 --> Using single parent node rather than creating whole parent array. Store pair <node, parent> in queue

bool cycleBFS3(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            if(isCycle3(graph, visited, i))        // in any connected component, if you find cycle, just return TRUE
            {
                return true;
            }
        }
    }
    return false;                           // return FALSE only if no component has a cycle

}



bool isCycle3(UndirectedGraph graph, vector<int>& visited, int u)
{
    queue<pair<int, int>> q;        // <node, parent>
    visited[u] = 1;
    q.push({u, -1});

    while(!q.empty())
    {
        int cur = q.front().first;
        int curParent = q.front().second;
        q.pop();

        for(int x : graph.getAdjacentToNode(cur))
        {
            if(!visited[x])
            {
                visited[x] = 1;
                q.push({x, cur});
            }

            else if(curParent != x)
                return true;
        }
    }

    return false;
}
