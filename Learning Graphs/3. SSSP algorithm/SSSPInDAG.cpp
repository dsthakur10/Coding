// SSSP in DAG

/*
    1. We initialize distances to all vertices as infinite and distance to source as 0,
    2. Then we find a topological sorting of the graph.
    3. Once we have topological order (or linear representation), we one by one process all vertices in topological order.
       For every vertex being processed, we update distances of its adjacent using distance of current vertex.

*/


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<climits>

using namespace std;
typedef pair<int, long> pi;

class DirectedGraph{

    int nodes;
    vector<vector<pi>> adjList;

public:
    DirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<pi>> (n+1);
    }

    void addEdge(int u, int v, long w)
    {
        adjList[u].push_back({v,w});
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<pi> getAdjacentToNode(int u){
        return adjList[u];
    }
};


vector<int> topologicalBFS(DirectedGraph graph);
vector<int> SSSPInDAG(DirectedGraph graph, int source);

int main()
{
    int source;
    DirectedGraph graph(6);
    graph.addEdge(6,1,2);
    graph.addEdge(6,4,1);
    graph.addEdge(1,2,3);
    graph.addEdge(4,2,2);
    graph.addEdge(4,5,4);
    graph.addEdge(2,3,6);
    graph.addEdge(5,3,1);


    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();
    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(auto it : node)
            cout << it.first << " ";
    }

    cout << "\n\nEnter source vertex : ";
    cin >> source;

    cout << "\n\n SSSP : ";
    vector<int> distance = SSSPInDAG(graph, source);
    for(int i = 1; i<distance.size(); i++)
        cout << "\n" << source << " - " << i << " : " << distance[i];

    return 0;
}



vector<int> topologicalBFS(DirectedGraph graph)
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
        for(auto it: graph.getAdjacentToNode(i))
            indegree[it.first]++;
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

        for(auto it : graph.getAdjacentToNode(cur))
        {
            indegree[it.first]--;
            if(!indegree.empty() && indegree[it.first] == 0)
            {
                q.push(it.first);
                indegree.erase(it.first);
            }
        }
    }

    return topo;
}




vector<int> SSSPInDAG(DirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<int> distance(n+1, INT_MAX);
    vector<int> topo;
    queue<int> q;

    cout << "\n\n Topological Sort = ";
    topo = topologicalBFS(graph);

    distance[source] = 0;

/*
    // skipping all the vertices that occur before source vertex in topological ordering. WHY ? --> They can't be reached from source

    int startIndex;
    for(int i=0; i<topo.size(); i++)
    {
        if(topo[i] == source)
        {
            startIndex = i;
            break;
        }
    }

    // starting the edge relaxation from source node

    for(int i=startIndex; i<topo.size(); i++)
    {
        for(auto it : graph.getAdjacentToNode(topo[i]))
        {
            int x = it.first;
            int weight = it.second;

            if(distance[topo[i]] + weight < distance[x])
            {
                distance[x] = distance[topo[i]] + weight;
            }
        }
    }

*/

    // Avoid the nodes before source in topological order by using "distance[i] == infinity".
    // Only source node will have distance = 0 in the beginning.

    for(int i=0; i<topo.size(); i++)
    {
        if(distance[topo[i]] != INT_MAX)
        {
            for(auto it : graph.getAdjacentToNode(topo[i]))
            {
                int x = it.first;
                int weight = it.second;

                if(distance[topo[i]] + weight < distance[x])
                {
                    distance[x] = distance[topo[i]] + weight;
                }
            }
        }
    }

    return distance;
}
