
// Check if the "given graph is bipartite" <--> "Graph is 2-colorable"
// DFS method

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



bool isBipartite(UndirectedGraph graph);
bool checkBipartite(UndirectedGraph graph, vector<char>& color, int u);


int main()
{
    UndirectedGraph graph(7);

    graph.addEdge(1,2);
    graph.addEdge(2,3);
    graph.addEdge(2,7);
    graph.addEdge(3,5);
    graph.addEdge(5,7);
    graph.addEdge(4,6);

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();

    cout << "\nGraph edges: ";

    for(int i=1; i<=7; i++)
    {
        vector<int> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(int x : node)
            cout << x << " ";
    }

    bool isBip = isBipartite(graph);

    if(isBip)
        cout << "\n Bipartite graph";
    else
        cout << "\n Graph is NOT bipartite";

    return 0;
}




bool isBipartite(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<char> color(n+1, 'W');

    for(int i=1; i<=n; i++)
    {
        if(color[i] == 'W')
        {
            color[i] = 'R';
            if(!checkBipartite(graph, color, i))
                return false;
        }
    }

    return true;
}



bool checkBipartite(UndirectedGraph graph, vector<char>& color, int u)
{
    for(int x : graph.getAdjacentToNode(u))
    {
        if(color[x] == 'W')
        {
            color[x] = (color[u] == 'R' ? 'G' : 'R');
            if(!checkBipartite(graph, color, x))
                return false;
        }

        else if(color[x] == color[u])
            return false;
    }

    return true;
}
