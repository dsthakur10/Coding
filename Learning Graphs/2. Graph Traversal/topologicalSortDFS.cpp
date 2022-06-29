
// Topological sort using DFS

/*

The algorithm loops through each node of the graph, in an ARBITRARY ORDER, initiating a depth-first search
that terminates when it hits any node that has already been visited
since the beginning of the topological sort or the node has no outgoing edges.
(i.e. a leaf node)

*/

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


vector<int> DFS(DirectedGraph graph);

vector<int> topologicalDFS(DirectedGraph graph);
void topological(DirectedGraph graph, vector<int>& visited, int u, vector<int>& topo);

int main()
{

    DirectedGraph graph(6);
    graph.addEdge(5,2);
    graph.addEdge(5,6);
    graph.addEdge(4,1);
    graph.addEdge(4,6);
    graph.addEdge(2,3);
    graph.addEdge(3,1);


/*
    DirectedGraph graph(11);
    graph.addEdge(1,2);
    graph.addEdge(1,4);
    graph.addEdge(2,3);
    graph.addEdge(3,4);
    graph.addEdge(4,5);
    graph.addEdge(6,7);
    graph.addEdge(7,8);
    graph.addEdge(7,9);
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
/*
    cout << "\n\n DFS traversal = ";
    vector<int> dfs = DFS(graph);
    for(int x : dfs)
        cout << x << " ";
*/

    cout << "\n\n Topological Sort = ";
    vector<int> dfs = topologicalDFS(graph);
    for(int x : dfs)
        cout << x << " ";

}


/*

2 differences between DFS & topological sort are:
    1. In DFS, we store the element as soon as we visit it & then perform recursive calls on its immediate neighbor,
        while in topological sort, we perform recursive calls first & store the element in the end
        (when this recursive call is about to end)
        The reason for this is because if u->v->w is an edge then w,v,u must come in order as we are gonna
        reverse the array.

    2. In DFS, we return the array of stored elements directly, while in topological sorting,
        we return the reversed array.

*/

vector<int> topologicalDFS(DirectedGraph graph)
{
    vector<int> topo;
    int n = graph.getNumberOfNodes();
    vector<int> visited(n+1, 0);            // initializing visited with 0's

    for(int i=1; i<=n; i++)                 // for-loop ensures correct traversal in case graph is disconnected
    {
        if(!visited[i])
        {
            topological(graph, visited, i, topo);
        }
    }

    reverse(topo.begin(), topo.end());
    return topo;
}



void topological(DirectedGraph graph, vector<int>& visited, int u, vector<int>& topo)
{
    visited[u] = 1;

    for(int x : graph.getAdjacentToNode(u))
    {
        if(!visited[x])
        {
            topological(graph, visited, x, topo);
        }
    }

    topo.push_back(u);
}
