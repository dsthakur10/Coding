#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class UndirectedGraph
{

    int nodes;
    vector<vector<int>> adjList;

public:
    UndirectedGraph(int n)
    {
        nodes = n;
        adjList = vector<vector<int>>(n + 1);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    int getNumberOfNodes()
    {
        return nodes;
    }

    vector<int> getAdjacentToNode(int u)
    {
        return adjList[u];
    }
};


vector<int> DFS(UndirectedGraph graph);
void DFStraversal(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &dfs);

vector<int> DFS2(UndirectedGraph graph);
void DFStraversal2(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &dfs);

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

    UndirectedGraph graph(5);
    graph.addEdge(5, 1);
    graph.addEdge(5, 2);
    graph.addEdge(5, 4);
    graph.addEdge(4, 3);


    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for (int i = 1; i <= graph.getNumberOfNodes(); i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for (int x : node)
            cout << x << " ";
    }

    cout << "\n\n DFS traversal = ";
    vector<int> dfs = DFS(graph);
    for (int x : dfs)
        cout << x << " ";

    cout << "\n\n DFS2 traversal = ";
    dfs = DFS2(graph);
    for (int x : dfs)
        cout << x << " ";
}


// Method-1 --> Recursive method

vector<int> DFS(UndirectedGraph graph)
{
    vector<int> dfs;
    int n = graph.getNumberOfNodes();
    vector<int> visited(n + 1, 0); // initializing visited with 0's

    for (int i = 1; i <= n; i++) // for-loop ensures correct traversal in case graph is disconnected
    {
        if (!visited[i])
        {
            DFStraversal(graph, visited, i, dfs);
        }
    }

    return dfs;
}


void DFStraversal(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &dfs)
{
    visited[u] = 1;
    dfs.push_back(u);

    for (int x : graph.getAdjacentToNode(u))
    {
        if (!visited[x])
        {
            DFStraversal(graph, visited, x, dfs);
        }
    }
}


// Method-2 --> Iterative method - Using stack

vector<int> DFS2(UndirectedGraph graph)
{
    vector<int> dfs;
    int n = graph.getNumberOfNodes();
    vector<int> visited(n + 1, 0); // initializing visited with 0's

    for (int i = 1; i <= n; i++) // for-loop ensures correct traversal in case graph is disconnected
    {
        if (!visited[i])
        {
            DFStraversal2(graph, visited, i, dfs);
        }
    }

    return dfs;
}


void DFStraversal2(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &dfs)
{
    stack<int> st;
    st.push(u);
    visited[u] = 1;

    while (!st.empty())
    {
        int cur = st.top();
        st.pop();
        dfs.push_back(cur);

        for (int x : graph.getAdjacentToNode(cur))
        {
            if (!visited[x])
            {
                visited[x] = 1;
                st.push(x);
            }
        }
    }
}
