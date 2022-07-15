/*

Ninja is planing this ‘N’ days-long training schedule. Each day, he can perform any one of these three activities.
(Running, Fighting Practice or Learning New Moves). Each activity has some merit points on each day.

As Ninja has to improve all his skills, he CAN’T DO THE SAME ACTIVITY IN TWO CONSECUTIVE DAYS.
Can you help Ninja find out the maximum merit points Ninja can earn?

You are given a 2D array of size N*3 ‘POINTS’ with the points corresponding to each day and activity. Your task is to calculate the maximum number of merit points that Ninja can earn.
Example :
POINTS’ array = [[1,2,5], [3 ,1 ,1] ,[3,3,3]]
OUTPUT: 11 (5 + 3 + 3)

*/


// TOP-DOWN

vector<vector<int>> dp;

int solve(vector<vector<int>> &points, int n, int k)
{
    if(n == 0)
        return 0;

    if(dp[n][k] != -1)
        return dp[n][k];

    dp[n][k] = points[n-1][k] +
               max(solve(points, n-1, (k+1)%3), solve(points, n-1, (k+2)%3));

    return dp[n][k];
}

int ninjaTraining(int n, vector<vector<int>> &points)
{
    dp = vector<vector<int>> (n+1, vector<int>(3, -1));
    int maxSum;
    int A1 = solve(points, n, 0);
    int A2 = solve(points, n, 1);
    int A3 = solve(points, n, 2);

    maxSum = max(A1, A2);
    maxSum = max(maxSum, A3);

    return maxSum;
}


// BOTTOM-UP

int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n+1, vector<int>(3));
    int maxSum;
    dp[0][0] = 0;
    dp[1][0] = 0;
    dp[2][0] = 0;

    for(int i=1; i<n+1; i++)
    {
        for(int j=0; j<3; j++)
            dp[i][j] = points[i-1][j] +
                       max(dp[i-1][(j+1)%3], dp[i-1][(j+2)%3]);
    }

    int A1 = dp[n][0];
    int A2 = dp[n][1];
    int A3 = dp[n][2];

    maxSum = max(A1, A2);
    maxSum = max(maxSum, A3);

    return maxSum;
}
