
// Course Schedule

/*

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false

Example 1:
    Input: numCourses = 2, prerequisites = [[1,0]]
    Output: true

    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0. So it is possible.

Example 2:
    Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
    Output: false

    Explanation: There are a total of 2 courses to take.
    To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1.
    So it is impossible.


NOTE: All the pairs prerequisites[i] are unique.

*/

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<string>
#include<unordered_map>

using namespace std;

class DirectedGraph{

    int nodes;
    vector<vector<int>> adjList;

public:
    DirectedGraph(int n){
        nodes = n;
        adjList = vector<vector<int>> (n+1);
    }

    void addEdge(int u, int v)
    {
        adjList[u].push_back(v);
    }

    int getNumberOfNodes(){
        return nodes;
    }

    vector<int> getAdjacentToNode(int u){
        return adjList[u];
    }
};




// Method-1 --> BFS topological sort to check whether cycle exists
// cycleDetectionBFS

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

    vector<vector<int>> adj(numCourses);

    for(int i=0; i<prerequisites.size(); i++)
    {
        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }

    if(isCycle(adj))
        return false;

    return true;
}


bool isCycle(vector<vector<int>> adj)
{
    queue<int> q;
    vector<int> indegree(adj.size(), 0);
    int visit = 0;

    for(int i=0; i<adj.size(); i++)
    {
        for(int x : adj[i])
            indegree[x]++;
    }

    for(int i=0; i<adj.size(); i++)
    {
        if(indegree[i] == 0)
            q.push(i);
    }

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();
        visit++;
        //topo.push_back(cur);

        for(int x : adj[cur])
        {
            indegree[x]--;

            if(indegree[x] == 0)
                q.push(x);
        }
    }

    if(visit != adj.size())
        return true;

    return false;
}



// Method-2 --> Idea is to check whether a cycle exists in Directed graph.
// cycleDetectionDFS --> DFS to check cycle in Directed Graph --> TLE

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    vector<vector<int>> adj(numCourses);
    vector<int> visited(numCourses, 0);
    vector<int> dfsVisit(numCourses, 0);

    for(int i=0; i<prerequisites.size(); i++)
    {
        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }

    for(int i=0; i<adj.size(); i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            if(isCycle(adj, visited, dfsVisit, i))
                return false;
        }
    }

    return true;
}


bool isCycle(vector<vector<int>> adj, vector<int>& visited, vector<int>& dfsVisit, int u)
{
    dfsVisit[u] = 1;

    for(int x: adj[u])
    {
        if(!visited[x])
        {
            visited[x] = 1;
            if(isCycle(adj, visited, dfsVisit, x))
                return true;
        }

        else if(dfsVisit[x])
            return true;
    }

    dfsVisit[u] = 0;
    return false;
}





bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    vector<vector<int>> adj(numCourses);
    vector<int> visited(numCourses, 0);
    vector<int> dfsVisit(numCourses, 0);

    for(int i=0; i<prerequisites.size(); i++)
    {
        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }

    for(int i=0; i<adj.size(); i++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            if(!isAcyclic(adj, visited, dfsVisit, i))
                return false;
        }
    }

    return true;
}


bool isAcyclic(vector<vector<int>>& adj, vector<int>& visited, vector<int>& dfsVisit, int u)
{
    dfsVisit[u] = 1;

    for(int x: adj[u])
    {
        if(!visited[x])
        {
            visited[x] = 1;
            if(!isAcyclic(adj, visited, dfsVisit, x))
                return false;
        }

        else if(dfsVisit[x])
            return false;
    }

    dfsVisit[u] = 0;
    return true;
}




// Working DFS Solutions:

// TYPE-1

typedef vector<vector<int>> graph;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
{
    graph g = buildGraph(numCourses, prerequisites);
    vector<bool> todo(numCourses, false), done(numCourses, false);

    for (int i = 0; i < numCourses; i++)
    {
        if (!done[i] && !acyclic(g, todo, done, i))
            return false;
    }
    return true;
}


graph buildGraph(int numCourses, vector<vector<int>>& prerequisites)
{
    graph g(numCourses);

    for (auto p : prerequisites)
        g[p[1]].push_back(p[0]);

    return g;
}


bool acyclic(graph& g, vector<bool>& todo, vector<bool>& done, int node)
{
    if (todo[node])
        return false;

    if (done[node])
        return true;

    todo[node] = done[node] = true;
    for (int v : g[node])
    {
        if (!acyclic(g, todo, done, v))
            return false;
    }

    todo[node] = false;
    return true;
}




// TYPE-2

unordered_map<int, vector<int>> G;
vector<bool> visited;
vector<bool> onPath;
bool hasCircle = false;

bool canFinish(int numCourses, vector<vector<int>>& req) {
    visited = vector<bool>(numCourses, false);
    onPath = vector<bool>(numCourses, false);

    buildGraph(req);

    // traverse the Graph
    for (int i = 0; i < numCourses; i++)
        if (!visited[i]) dfs(i);

    if (hasCircle) return false;

    return true;
}

void dfs(int s) {

    visited[s] = true;
    onPath[s] = true; // choose

    // G[s] is the adjacent vertices of s
    // In other word, G[s] is the pre-required courses
    for (int w : G[s]) {
        if      (hasCircle)   { return; }
        else if (!visited[w]) { dfs(w); }
        else if (onPath[w])   { hasCircle = true; } // find circle
    }

    onPath[s] = false; // unchoose
}

void buildGraph(vector<vector<int>> req) {
    for (auto p : req) {
        int target = p[0];
        int required = p[1];

        if (G.count(target) == 0)
            G[target] = vector<int>();

        G[target].push_back(required);
    }
}
