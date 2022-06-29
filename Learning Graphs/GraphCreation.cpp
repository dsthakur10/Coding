#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<string>

using namespace std;

/*
struct edge{

    int u,v;
};

set<int> nodes;
set<edge> edges;

*/


class UndirectedGraph
{
    int nodes;                                  // number of nodes in graph object
    vector<vector<int>> adjList;                // outer vector is for every node | inner vector is for neighbors of given node

    vector<vector<pair<int, long long>>> adjListWeight;

public:
    UndirectedGraph(int n){                             // constructor to create an object graph

        nodes = n;
        adjList = vector<vector<int>>(n+1);             // 0th node is kept unused

        adjListWeight = vector<vector<pair<int, long long>>>(n+1);
    }


    void addEdge(int u, int v){
                                                        // edge u-v implies u is neighbor of v & vice versa
        adjList[u].push_back(v);
        adjList[v].push_back(u);                        // remove this in case of directed graphs
    }

    void addEdgeWeight(int u, int v, long long w=1){
                                                        // adjListWeight[u] --> neighbors of node u along with their edge weights
        adjListWeight[u].push_back({v,w});
        adjListWeight[v].push_back({u,w});              // adjListWeight[u].first --> neighbor
                                                        // adjListWeight[u].second --> edge weight
    }


    int getNumberOfNodes(){
        return nodes;
    }


    vector<int> getAdjacentToNode(int u){
        return adjList[u];                              // returns neighbors of given node u
    }

    vector<pair<int,long long>> getAdjacentToNodeWithWeight(int u){
        return adjListWeight[u];
    }

};


int main()
{
    UndirectedGraph myGraph(6);

    cout << "Type-1 graph (Without edge weights)\n";
    myGraph.addEdge(1,2);
    myGraph.addEdge(1,5);
    myGraph.addEdge(2,3);
    myGraph.addEdge(5,4);
    myGraph.addEdge(3,4);
    myGraph.addEdge(4,6);

    cout << "\nNumber of Nodes = " << myGraph.getNumberOfNodes();
    for(int i=1; i<=6; i++)
    {
        vector<int> adj = myGraph.getAdjacentToNode(i);

        std::cout << "\nNode " << i << " : ";
        for(int x : adj)
            std::cout << x << " ";

    }


    UndirectedGraph myGraph2(6);

    cout << "\n\nType-2 graph (Edge weights)\n";
    myGraph2.addEdgeWeight(1,2,4);
    myGraph2.addEdgeWeight(1,5,6);
    myGraph2.addEdgeWeight(2,3,10);
    myGraph2.addEdgeWeight(5,4,5);
    myGraph2.addEdgeWeight(3,4,3);
    myGraph2.addEdgeWeight(4,6,14);

    cout << "\nNumber of Nodes = " << myGraph2.getNumberOfNodes();

    for(int i=1; i<=6; i++)
    {
        vector<pair<int,long long>> adj = myGraph2.getAdjacentToNodeWithWeight(i);

        std::cout << "\nNode " << i << " : ";
        for(auto x : adj)
            std::cout << x.first << " ";

    }


    cout << "\n\nEdge weights:";
    for(int i=1; i<=6; i++)
    {
        vector<pair<int,long long>> adj = myGraph2.getAdjacentToNodeWithWeight(i);

        std::cout << "\nNode " << i << " : ";
        for(auto x : adj)
            std::cout << "Weight[" << i << ", " << x.first << "] = " << x.second << " | ";

    }
}
