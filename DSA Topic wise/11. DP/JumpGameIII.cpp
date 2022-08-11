
vector<int> visited;

bool canReach(vector<int>& arr, int start) {

    int n = arr.size();
    visited = vector<int> (n, 0);

    return solve(arr, start);
}

int solve(vector<int>& arr, int n)
{
    int len = arr.size();

    if(n >= len || n < 0)
        return 0;

    if(arr[n] == 0)
        return 1;

    if(visited[n])
        return 0;

    visited[n] = 1;
    int flag = solve(arr, n + arr[n]) || solve(arr, n - arr[n]);
    visited[n] = 0;

    return flag;
}


// O(1) SPACE


bool canReach(vector<int>& arr, int start) {

    int n = arr.size();

    return solve(arr, start);
}

int solve(vector<int>& arr, int n)
{
    int len = arr.size();

    if(n >= len || n < 0)
        return 0;

    if(arr[n] == 0)
        return 1;

    if(arr[n] < 0)
        return 0;

    int jump = arr[n];
    arr[n] = -arr[n];       // make it negative

    bool flag = solve(arr, n + jump) || solve(arr, n - jump);

    arr[n] = -arr[n];       // make it positive back again

    return flag;
}
