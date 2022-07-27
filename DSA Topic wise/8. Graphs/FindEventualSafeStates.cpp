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
        //     if(DFS(graph, safe, visited, dfsVisit, i))
        //         safe[i] = 1;

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
            // if at any point, cycle is detected in current DFS path --> return false & mark node UNSAFE
            if(!DFS(graph, safe, visited, dfsVisit, x))
            {
                safe[u] = 0;
                dfsVisit[u] = 0;
                return false;
            }
        }

        else if(dfsVisit[x])     // detects cycle --> return false & mark node UNSAFE
        {
            safe[x] = 0;
            dfsVisit[x] = 0;
            return false;
        }

        // VIMP step
        else if(safe[x] == 0)       // while traversing a cycle from new node you come across a node which is already visited & is UNSAFE --> Mark this node as UNSAFE as well
            return false;
    }

    dfsVisit[u] = 0;
    safe[u] = 1;
    return true;
}
