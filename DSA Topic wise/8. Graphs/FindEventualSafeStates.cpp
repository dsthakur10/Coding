// Find Eventual Safe States

/*
There is a directed graph of n nodes with each node labeled from 0 to n - 1.
The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of
nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting
from that node leads to a terminal node.

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.


Example 1:
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:
Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.


*/



// Safe node --> Every path from safe node must end up at terminal node

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

    vector<int> safe(graph.size());
    vector<int> visited(graph.size(), 0);
    vector<int> dfsVisit(graph.size(), 0);

    // check for terminal nodes & mark them visited as well as safe
    for(int i=0; i<graph.size(); i++)
    {
        if(graph[i].empty())
        {
            visited[i] = 1;
            safe[i] = 1;
        }
    }

    for(int i=0; i<graph.size(); i++)
    {
        if(!visited[i])
        {
            DFS(graph, safe, visited, dfsVisit, i);
        }
    }

    vector<int> result;
    for(int i=0; i<safe.size(); i++)
    {
        if(safe[i])
            result.push_back(i);
    }

    return result;
}

bool DFS(vector<vector<int>>& graph, vector<int>& safe, vector<int>& visited, vector<int>& dfsVisit, int u)
{
    visited[u] = 1;
    dfsVisit[u] = 1;

    for(int x : graph[u])
    {
        if(!visited[x])
        {
            // if at any point, cycle is detected in current DFS path --> mark node UNSAFE & return false
            if(!DFS(graph, safe, visited, dfsVisit, x))
            {
                //dfsVisit[u] = 0;
                safe[u] = 0;
                return false;
            }
        }

        else if(dfsVisit[x])     // detects cycle --> mark node UNSAFE & return false
        {
            //dfsVisit[x] = 0;
            safe[u] = 0;
            return false;
        }

        // VIMP step --> it will make your code run faster

        else if(safe[x] == 0)       // while traversing a cycle from new node you come across a node which is
                                        // already visited & is UNSAFE --> Mark this node as UNSAFE as well
            return false;
    }

    // reset dfsVisit[u] because this is actually a safe node & you might need to come back to this node in future
    dfsVisit[u] = 0;
    safe[u] = 1;
    return true;
}



// Method-2 --> Without using safe[]

vector<int> result;

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

    int n = graph.size();
    vector<int> visited(n, 0);
    vector<int> dfsVisit(n, 0);

    for(int i=0; i<n; i++)
    {
        if(visited[i] == 0)
        {
            DFS(graph, visited, dfsVisit, i);
        }

        // You have dfsVisit[i] = 0 iff the node is safe node as then only it can traverse all its neighbors
        // & can return to the last statement reseting dfsVisit[i]

        // For unsafe nodes, you will be returning false as soon as they got detected & hence their dfsVisit[i]
        // won't get reset.
        if(dfsVisit[i] == 0)
            result.push_back(i);
    }

    return result;
}


// DFS returns true --> safe state --> no cycle
bool DFS(vector<vector<int>>& graph, vector<int>& visited, vector<int>& dfsVisit, int u)
{
    visited[u] = 1;
    dfsVisit[u] = 1;

    for(int x : graph[u])
    {
        if(visited[x] == 0)
        {
            if(!DFS(graph, visited, dfsVisit, x))
            {
                return false;
            }
        }

        else if(dfsVisit[x] == 1)
        {
            return false;
        }
    }

    dfsVisit[u] = 0;
    return true;
}



// Method-3 --> BFS --> Topological sort

// Reverse the graph (terminal nodes will become starting nodes)
// Apply topological sort on this reversed graph to get required nodes with no cycle.

/*
WHY this works ??
// Terminal nodes are always safe nodes.

    --> This is because we need to start from nodes with outdegree = 0 (Terminal Nodes), and then move backwards
        to find safe nodes.
    --> We cannot move backward from terminal nodes (outdegree = 0), due to which we need to reverse edges.
    --> So, outdegree becomes indegree , and we can easily do topological sort using this.

    --> Reversing the edges will help us in classifying TERMINAL NODES => indegree = 0,
        and all safe nodes i.e nodes reachable from terminal nodes, that are not in a cycle.

    --> Also, doing topological sort will exclude all nodes that are present in a cyclic path.
    --> So, topological sort will give us all nodes that are either terminal or there is a path to terminal nodes.

*/

vector<int> topo;

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {

    int n = graph.size();
    vector<vector<int>> reverseGraph(n);

    for(int i=0; i<n; i++)
    {
        for(int x : graph[i])
            reverseGraph[x].push_back(i);
    }

    topoSort(reverseGraph);
    sort(topo.begin(), topo.end());
    return topo;
}

void topoSort(vector<vector<int>>& graph)
{
    topo.clear();
    queue<int> q;
    int n = graph.size();
    vector<int> indegree(n, 0);

    for(int i=0; i<n; i++)
    {
        for(int x : graph[i])
            indegree[x]++;
    }

    for(int i=0; i<n; i++)
    {
        if(indegree[i] == 0)
            q.push(i);
    }

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        topo.push_back(cur);

        for(int x : graph[cur])
        {
            indegree[x]--;
            if(indegree[x] == 0)
                q.push(x);
        }
    }
}
