
// Prim's algorithm for MST

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<string>
#include<unordered_set>
#include<climits>

using namespace std;
typedef pair<int, long> pi;
typedef pair<long, int> pli;        // <distance[u], u>

class UndirectedGraph{

    int nodes;
    vector<vector<pi>> adjList;

public:
    UndirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<pi>> (n+1);
    }

    void addEdge(int u, int v, long w)
    {
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<pi> getAdjacentToNode(int u){
        return adjList[u];
    }
};


int findMinimum(vector<int>& key, vector<bool>& mstSet);
vector<int> prims(UndirectedGraph graph, int source);

vector<int> prims2(UndirectedGraph graph, int source);

int main()
{
    int source;
/*
    UndirectedGraph graph(8);
    graph.addEdge(8,4,10);
    graph.addEdge(8,5,15);
    graph.addEdge(8,6,7);
    graph.addEdge(1,2,6);
    graph.addEdge(1,6,12);
    graph.addEdge(2,3,14);
    graph.addEdge(2,4,8);
    graph.addEdge(2,6,5);
    graph.addEdge(3,4,3);
    graph.addEdge(6,7,9);
*/

    UndirectedGraph graph(9);
    graph.addEdge(9,1,4);
    graph.addEdge(9,7,8);
    graph.addEdge(1,7,11);
    graph.addEdge(1,2,8);
    graph.addEdge(2,3,7);
    graph.addEdge(2,8,2);
    graph.addEdge(2,5,4);
    graph.addEdge(3,4,9);
    graph.addEdge(3,5,14);
    graph.addEdge(4,5,10);
    graph.addEdge(5,6,2);
    graph.addEdge(6,7,1);
    graph.addEdge(6,8,6);
    graph.addEdge(7,8,7);


/*
    UndirectedGraph graph(3);
    graph.addEdge(3,1,5);
    graph.addEdge(1,2,3);
    graph.addEdge(3,2,1);
*/

    cout << "Number of nodes in given graph = " << graph.getNumberOfNodes();
    cout << "\nGraph edges: ";

    for(int i=1; i<=graph.getNumberOfNodes(); i++)
    {
        vector<pi> node = graph.getAdjacentToNode(i);

        cout << "\nNode-" << i << " : ";
        for(auto it : node)
            cout << it.first << " ";
    }

    cout << "\n\nEnter source vertex: ";
    cin >> source;

    vector<int> parent = prims2(graph, source);

    for(int i=1; i<parent.size(); i++)
        cout << "\n" << i << " - " << parent[i];

    return 0;
}



// Method-1 --> Brute force --> Time = O(V^2 + E) | Space = O(VE + V + V + V)

/*
    We will maintain 3 arrays: parent, key, mstSet
        1. parent[] --> store parent of current node
        2. key[] --> weight of node from its parent
        3. mstSet[] --> boolean array to indicate if a node is already taken into MST formation (to avoid cycle in MST)

    Initialize
*/


int findMinimum(vector<long>& key, vector<bool>& mstSet)
{
    int minimumIndex = 0;
/*
    for(int i=1; i<key.size(); i++)
    {
        if(!mstSet[i] && key[i] < key[minimumIndex])
        {
            minimumIndex = i;
        }
    }
*/
    int minimumIndex = 0, mini = INT_MAX;
    for(int i=0; i<key.size(); i++)
    {
        if(!mstSet[i] && key[i] < mini)
        {
            minimumIndex = i;
            mini = key[i];
        }
    }

    mstSet[minimumIndex] = true;
    return minimumIndex;
}


vector<int> prims(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<int> parent(n+1, -1);
    vector<long> key(n+1, INT_MAX);
    vector<bool> mstSet(n+1, false);
    key[source] = 0;

    // iterate only N-1 times because a graph with N nodes has MST with N-1 edges
    for(int count=1; count<n; count++)
    {
        int cur = findMinimum(key, mstSet);

        for(auto it: graph.getAdjacentToNode(cur))
        {
            int x = it.first;
            long weight = it.second;

            cout << "\n" << x << " - " << weight ;
            if(!mstSet[x] && weight < key[x])
            {
                parent[x] = cur;
                key[x] = weight;
            }
        }
    }

    int sum = 0;
    for(int i=1; i<key.size(); i++)
        sum += key[i];

    cout << "\n sum of mst = " << sum;
    return parent;
}



// Method-2 --> Min-heap to make searching minimum key value log(V) instead of V --> Time = O(V+E)logV

// Run the loop till all the nodes have been visited
// because in the brute code we checked for mstSet[node] == false while computing the minimum
// but here we simply take the minimal from the priority queue, so a lot of times a node might be taken twice
// hence its better to keep running till all the nodes have been taken.


vector<int> prims2(UndirectedGraph graph, int source)
{
    int n = graph.getNumberOfNodes();
    vector<int> parent(n+1, -1);
    vector<long> key(n+1, INT_MAX);
    vector<bool> mstSet(n+1, false);
    key[source] = 0;
    priority_queue<pli, vector<pli>, greater<pli>> pq;

    pq.push({0,source});

    //for(int count=1; count<n; count++)
    while(!pq.empty())
    {
        int cur = pq.top().second;
        pq.pop();

        if(mstSet[cur])                 // avoids solving for unnecessary repeated nodes that are in min-heap
            continue;


        mstSet[cur] = true;

        cout << "\ncur = " << cur << " --> ";
        for(auto it: graph.getAdjacentToNode(cur))
        {
            int x = it.first;
            long weight = it.second;

            //cout << " " << x << " - " << weight << " | " ;
            if(!mstSet[x] && weight < key[x])
            {
                parent[x] = cur;
                key[x] = weight;
                pq.push({key[x],x});
                cout << " " << x << " - " << weight << " | " ;
            }
        }
    }

    int sum = 0;
    for(int i=1; i<key.size(); i++)
        sum += key[i];

    cout << "\n sum of mst = " << sum;
    return parent;
}
