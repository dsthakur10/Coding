#include <algorithm>
#include <iostream>
#include <queue>
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


vector<int> BFS(UndirectedGraph graph);

vector<int> BFS2(UndirectedGraph graph);
void BFStraversal(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &bfs);

int main()
{
    UndirectedGraph graph(7);

    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 7);
    graph.addEdge(3, 5);
    graph.addEdge(5, 7);
    graph.addEdge(4, 6);

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for (int i = 1; i <= 7; i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for (int x : node)
            cout << x << " ";
    }

    cout << "\n\n BFS traversal = ";
    vector<int> bfs = BFS(graph);
    for (int x : bfs)
        cout << x << " ";

    cout << "\n\n BFS2 traversal = ";
    bfs = BFS2(graph);
    for (int x : bfs)
        cout << x << " ";
}


// Time --> O(V+E) | Space --> O(V+E) + O(V) + O(V) {Adjacency list, queue, visited array}

vector<int> BFS(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<int> bfs;
    vector<int> visited(n + 1, 0); // initializing visited with 0's
    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            q.push(i);
            visited[i] = 1;
        }

        while (!q.empty())
        {
            int cur = q.front();
            q.pop();

            for (int x : graph.getAdjacentToNode(cur))
            {
                if (!visited[x])
                {
                    q.push(x);
                    visited[x] = 1;
                }
            }
            bfs.push_back(cur);
        }
    }

    return bfs;
}


vector<int> BFS2(UndirectedGraph graph)
{
    vector<int> bfs;
    int n = graph.getNumberOfNodes();
    vector<int> visited(n + 1, 0); // initializing visited with 0's

    for (int i = 1; i <= n; i++) // for-loop ensures correct traversal in case graph is disconnected
    {
        if (!visited[i])
        {
            BFStraversal(graph, visited, i, bfs);
        }
    }

    return bfs;
}


void BFStraversal(UndirectedGraph graph, vector<int> &visited, int u, vector<int> &bfs)
{
    queue<int> q;
    q.push(u);
    visited[u] = 1;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();

        for (int x : graph.getAdjacentToNode(cur))
        {
            if (!visited[x])
            {
                q.push(x);
                visited[x] = 1;
            }
        }
        bfs.push_back(cur);
    }
}
