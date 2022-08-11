
// WRONG approach

vector<int> dp;
vector<int> visited;

int minJumps(vector<int>& arr) {

    int n = arr.size();
    dp = vector<int> (n, -1);
    visited = vector<int> (n, 0);

    return solve(arr, 0);
}

int solve(vector<int>& arr, int n)
{
    int len = arr.size();

    if(n >= len || n < 0)
        return INT_MAX;

    if(n == len-1)
        return 0;

    if(visited[n])
        return INT_MAX;

    if(dp[n] != -1)
        return dp[n];

    visited[n] = 1;
    int steps;

    int a = solve(arr, n+1);
    int b = solve(arr, n-1);
    steps = min(a, b);

    for(int i=0; i<len; i++)
    {
        if(visited[i])
            continue;

        if(i != n && arr[n] == arr[i])
            steps = min(steps, solve(arr, i));
    }

    visited[n] = 0;
    return dp[n] = (steps == INT_MAX) ? INT_MAX : 1 + steps;
}


// BFS method
