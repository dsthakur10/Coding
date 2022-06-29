
// Detect cycle in Directed graph using BFS --> Kahn's algorithm will be used

// If Topological sort DOES NOT exist <--> Graph is cyclic

/*

First vertex in topological sorting is always a vertex with in-degree as 0 (a vertex with no in-coming edges).
A DAG has at least one vertex with in-degree 0 and one vertex with out-degree 0.

1. Compute in-degree (number of incoming edges) for each of the vertex present in the DAG and initialize the count
    of visited nodes as 0.
2. Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
3. Remove a vertex from the queue (Dequeue operation) and then.
    a. Increment count of visited nodes by 1.
    b. Decrease in-degree by 1 for all its neighbouring nodes.
    c. If in-degree of a neighbouring nodes is reduced to zero, then add it to the queue.
4. Repeat Step 3 until the queue is empty.
5. If COUNT OF VISITED NODES != NUMBER OF NODES, then topological sort not possible for given graph --> GRAPH IS CYCLIC

*/


#include<iostream>
#include<vector>
#include<queue>
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


bool topologicalBFS(DirectedGraph graph);

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


    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

    bool found = topologicalBFS(graph);

    if(found)
        cout << "\n\n Cycle detected";
    else
        cout << "\n\n Acyclic";

    return 0;
}



bool topologicalBFS(DirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    int visit = 0;
    vector<int> topo;
    unordered_map<int, int> indegree;
    queue<int> q;

    for(int i=1; i<=n ; i++)
        indegree[i] = 0;

    for(int i=1; i<=n ; i++)
    {
        for(int x: graph.getAdjacentToNode(i))
            indegree[x]++;
    }

    auto it = indegree.begin();
    while(it != indegree.end())
    {
        if(it->second == 0)
        {
            q.push(it->first);
            it = indegree.erase(it);
        }

        else
            it++;
    }

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        topo.push_back(cur);

        visit++;

        for(int x : graph.getAdjacentToNode(cur))
        {
            indegree[x]--;
            if(!indegree.empty() && indegree[x] == 0)
            {
                q.push(x);
                indegree.erase(x);
            }
        }
    }

    if(visit == n)
        return false;

    else
        return true;
}
