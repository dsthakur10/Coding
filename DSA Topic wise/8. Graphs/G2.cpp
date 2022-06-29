
// Course Schedule II

/*

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1.
You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that
you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.

Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them.
If it is impossible to finish all courses, return an empty array.

Example 1:
Input: numCourses = 2, prerequisites = [[1,0]]
Output: [0,1]
Explanation: There are a total of 2 courses to take. To take course 1 you should have finished course 0.
So the correct course order is [0,1].

Example 2:
Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
Output: [0,2,1,3]
Explanation: There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2.
Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

Example 3:
Input: numCourses = 1, prerequisites = []
Output: [0]

*/



vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {

    vector<int> topo;
    vector<vector<int>> adj(numCourses);

    for(int i=0; i<prerequisites.size(); i++)
    {
        adj[prerequisites[i][1]].push_back(prerequisites[i][0]);
    }

    if(topological(adj, topo))
        return {};

    return topo;
}


bool topological(vector<vector<int>> adj, vector<int>& topo)
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
        topo.push_back(cur);

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



// Method-2 --> DFS topological sort --> TLE

vector<int> topo;

vector<int> findOrder2(int numCourses, vector<vector<int>>& prerequisites)
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
            if(!topological2(adj, visited, dfsVisit, i))
                return {};
        }
    }

    reverse(topo.begin(), topo.end());
    return topo;
}


bool topological2(vector<vector<int>>& adj, vector<int>& visited, vector<int>& dfsVisit, int u)
{
    dfsVisit[u] = 1;
    visited[u] = 1;

    for(int x: adj[u])
    {
        if(!visited[x])
            if(!topological2(adj, visited, dfsVisit, x))
        {
                return false;
        }

        else if(dfsVisit[x])
            return false;
    }

    dfsVisit[u] = 0;
    topo.push_back(u);
    return true;
}




// WORKING MODEL


stack<int> S;
vector<int> V;
vector<int> P;
bool cycle;
map<int, vector<int> > G;

void DFS(int n)
{
    for(int i=0;i<n;++i)
    {
        if(!V[i]) DFS_recur(i);
    }
}

void DFS_recur(int curr)
{
    if(cycle) return;

    V[curr] = true;
    P[curr] = true;

    for(int i : G[curr])
    {
        if(P[i] == true) cycle = true;
        if(!V[i]) DFS_recur(i);
    }

    S.push(curr);
    P[curr] = false;
}

vector<int> findOrder(int n, vector<vector<int>>& prerequisites)
{
    vector<int> Ans;
    V.assign(n, false);
    P.assign(n, false);
    cycle = false;
    for(auto i : prerequisites)
    {
        G[i[1]].push_back(i[0]);
    }

    DFS(n);

    while(!S.empty())
    {
        Ans.push_back(S.top());
        S.pop();
    }

    if(cycle) return {};
    return Ans;
}
