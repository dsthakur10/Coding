// Time Needed to Inform All Employees

/*

A company has n employees with a unique ID for each employee from 0 to n - 1. The head of the company is the one with headID.

Each employee has one direct manager given in the manager array where manager[i] is the direct manager of the i-th employee,
manager[headID] = -1. Also, it is guaranteed that the subordination relationships have a tree structure.

The head of the company wants to inform all the company employees of an urgent piece of news.
He will inform his direct subordinates, and they will inform their subordinates, and so on until all employees know about
the urgent news.

The i-th employee needs informTime[i] minutes to inform all of his direct subordinates
(i.e., After informTime[i] minutes, all his direct subordinates can start spreading the news).

Return the number of minutes needed to inform all the employees about the urgent news.

*/


// Method-1 --> BOTTOM-UP DFS --> Brute force

// You are visiting higher level nodes multiple times --> for each leaf node, a traversal from leaf to root is done

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {

    int time = 0;

    for(int i=0; i<n; i++)
    {
        if(informTime[i] == 0)
            time = max(DFS(manager, informTime, i), time);
    }

    return time;
}

int DFS(vector<int>& manager, vector<int>& informTime, int id)
{
    if(manager[id] == -1)
        return informTime[id];

    return informTime[id] + DFS(manager, informTime, manager[id]);
}



// Method-2 --> BOTTOM-UP --> DFS DP on trees

// Store the total inform time at every employee node & use it later to avoid traversing the whole path.

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {

    vector<int> dp(n, -1);
    int time = 0;

    for(int i=0; i<n; i++)
    {
        if(informTime[i] == 0)
            time = max(DFS(manager, informTime, i, dp), time);
    }

    return time;
}

int DFS(vector<int>& manager, vector<int>& informTime, int id, vector<int>& dp)
{
    if(manager[id] == -1)
        return dp[id] = informTime[id];

    if(dp[id] != -1)
        return dp[id];

    dp[id] = informTime[id] + DFS(manager, informTime, manager[id], dp);
    return dp[id];
}


// Method-3 --> BOTTOM-UP DFS --> Optimized DFS DP version

// Store cumulative inform-time in the informTime[] array after calculating it for the first time.
// Make its manager[id] = -1 to stop recursing for the same path ever again.

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
    int time = 0;

    for(int i=0; i<n; i++)
    {
        if(informTime[i] == 0)
            time = max(DFS(manager, informTime, i), time);
    }

    return time;
}

int DFS(vector<int>& manager, vector<int>& informTime, int id)
{
    if(manager[id] == -1)
        return informTime[id];

    informTime[id] = informTime[id] + DFS(manager, informTime, manager[id]);
    manager[id] = -1;
    return informTime[id];
}




// Method-4 --> TOP-DOWN DFS --> Convert hierarchy given in manager[] to graph

// Do BFS or DFS in graph
// The time for a manager = max(manager's employees) + informTime[manager]

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {

    vector<vector<int>> graph(n, vector<int>());

    for(int i=0; i<manager.size(); i++)
    {
        int x = manager[i];
        if(x != -1)
            graph[x].push_back(i);
    }

    return DFS(graph, informTime, headID);

}

int DFS(vector<vector<int>>& graph, vector<int>& informTime, int id)
{
    int time = 0;
    for(int x: graph[id])
    {
        time = max(DFS(graph, informTime, x), time);
    }

    return informTime[id] + time;
}
