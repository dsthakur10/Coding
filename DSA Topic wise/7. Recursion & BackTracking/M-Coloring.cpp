
/*

Given an undirected graph(Adjacency matrix) with N nodes and an M colors. The task is to determine if the graph can
be colored with at most M colors such that no two adjacent vertices of the graph are colored with the same color.
Here coloring of a graph means the assignment of colors to all vertices.

Example 1:

Input:
N = 4
M = 3
E = 5
Edges[] = {(0,1),(1,2),(2,3),(3,0),(0,2)}
Output: 1
Explanation: It is possible to colour the given graph using 3 colours.

Example 2:
Input:
N = 3
M = 2
E = 3
Edges[] = {(0,1),(1,2),(0,2)}
Output: 0

*/


bool graphColoring(bool graph[101][101], int m, int n) {
    vector<int> visited(n, 0);

    return mColor(graph, visited, m, n);
}


bool mColor(bool graph[101][101], vector<int>& visited, int m, int n)
{
    for(int i=0; i<n; i++)
    {
        if(visited[i] == 0)
        {
            for(int k=1; k<=m; k++)
            {
                if(isSafe(graph, visited, k, n, i))
                {
                    visited[i] = k;

                    if(mColor(graph, visited, m, n))
                        return true;

                    visited[i] = 0;
                }
            }
            return false;
        }
    }

    return true;
}



bool isSafe(bool graph[101][101], vector<int>& visited, int color, int n, int node)
{
    for(int i = 0; i<n; i++)
    {
        if(graph[node][i] && visited[i] == color)
            return false;
    }

    return true;
}




// Method-2 --> Traverse every node recursively in order.

bool graphColoring(bool graph[101][101], int m, int n) {

    vector<int> visited(n, 0);

    return mColor(graph, visited, m, n, 0);
}


bool mColor(bool graph[101][101], vector<int>& visited, int m, int n, int node)
{
    // node = n DOES NOT EXIST --> Every other nodes has been visited & colored with given constraints
    if(node == n)
        return true;

    if(visited[node] == 0)          // if not colored
    {
        for(int k=1; k<=m; k++)         // try out every possible color
        {
            if(isSafe(graph, visited, k, n, node))
            {
                visited[node] = k;

                if(mColor(graph, visited, m, n, node+1))        // recursively color next node
                    return true;

                visited[node] = 0;                      // restore previous state while backtracking
            }
        }
        return false;           // no choice worked --> atleast 1 collision in every color
    }

    return true;
}


bool isSafe(bool graph[101][101], vector<int>& visited, int color, int n, int node)
{
    for(int i = 0; i<n; i++)
    {
        if(graph[node][i] && visited[i] == color)
            return false;
    }

    return true;
}
