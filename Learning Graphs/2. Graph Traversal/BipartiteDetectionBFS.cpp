
// Check if the "given graph is bipartite" <--> "Graph is 2-colorable"
// BFS method

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



/*
    3 colors :
        White --> Unvisited
        Red --> source
        Green --> neighbor of source

    1. Initially, all the vertices are of WHITE color.
    2. Assign RED color to the source vertex (putting into set U).
    3. Color all the neighbors with GREEN color (putting into set V).
    4. Color all neighbor’s neighbor with RED color (putting into set U).
    5. This way, assign color to all vertices such that it satisfies all the constraints of m-way coloring problem where m = 2.
    6. While assigning colors, if we find a neighbor which is colored with same color as current vertex,
        then the graph cannot be colored with 2 vertices (or graph is not Bipartite)
*/


bool isBipartite(UndirectedGraph graph)
{
    int n = graph.getNumberOfNodes();
    vector<char> color(n+1, 'W');

    for(int i=1; i<=n; i++)
    {
        if(color[i] == 'W')
        {
            if(!checkBipartite(graph, color, i))        // return false if anyone component is even non-bipartite
                return false;
        }
    }

    return true;            // return true if all the components are bipartite
}


bool checkBipartite(UndirectedGraph graph, vector<char>& color, int u)
{
    queue<int> q;

    color[u] = 'R';
    q.push(u);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int x : graph.getAdjacentToNode(cur))
        {
            if(color[x] == 'W')
            {
                color[x] = (color[cur] == 'R' ? 'G' : 'R');
                q.push(x);
            }

            else if(color[cur] == color[x])
                return false;
        }
    }

    return true;
}
