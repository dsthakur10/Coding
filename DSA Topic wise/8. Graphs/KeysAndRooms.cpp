
// Keys and rooms


// Why this is WRONG ? --> You are unlocking a room without having a key by using default for loop in main function

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    vector<int> visited(rooms.size(), 0);

    for(int i=0; i<rooms.size(); i++)
    {
        if(!visited[i])
        {
            DFS(rooms, visited, i);
        }

    }

    for(int x : visited)
    {
        if(x == 0)
            return false;
    }

    return true;
}

void DFS(vector<vector<int>>& rooms, vector<int>& visited, int u)
{
    visited[u] = 1;

    for(int x : rooms[u])
    {
        if(!visited[x])
            DFS(rooms, visited, x);
    }
}



// Method-1 DFS

bool canVisitAllRooms(vector<vector<int>>& rooms) {
    vector<int> visited(rooms.size(), 0);
    vector<int> found(rooms.size(), 0);

    DFS(rooms, visited, 0);

    for(int x : visited)
    {
        if(x == 0)
            return false;
    }

    return true;
}

void DFS(vector<vector<int>>& rooms, vector<int>& visited, int u)
{
    visited[u] = 1;

    for(int x : rooms[u])
    {
        if(!visited[x])
        {
            DFS(rooms, visited, x);
        }
    }
}



// Method-2 BFS

 bool canVisitAllRooms(vector<vector<int>>& rooms) {
    vector<int> visited(rooms.size(), 0);
    vector<int> found(rooms.size(), 0);

    BFS(rooms, visited, 0);

    for(int x : visited)
    {
        if(x == 0)
            return false;
    }

    return true;
}

void BFS(vector<vector<int>>& rooms, vector<int>& visited, int u)
{
    visited[u] = 1;
    queue<int> q;
    q.push(u);

    while(!q.empty())
    {
        int cur = q.front();
        q.pop();

        for(int x : rooms[cur])
        {
            if(!visited[x])
            {
                q.push(x);
                visited[x] = 1;
            }

        }
    }
}
