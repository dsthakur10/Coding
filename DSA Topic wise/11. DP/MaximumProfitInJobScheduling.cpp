
/*

We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i], obtaining a profit[i].

You're given the startTime, endTime and profit arrays, return the maximum profit you can take such that there
are no two jobs in the subset with overlapping time range.

If you choose a job that ends at time X you will be able to start another job that starts at time X.

Example 1:
Input: startTime = [1,2,3,3], endTime = [3,4,5,6], profit = [50,10,40,70]
Output: 120
Explanation: The subset chosen is the first and fourth job.
We get profit of 120 = 50 + 70.

Example 2:
Input: startTime = [1,2,3,4,6], endTime = [3,5,10,6,9], profit = [20,20,100,70,60]
Output: 150
Explanation: The subset chosen is the first, fourth and fifth job.
Profit obtained 150 = 20 + 70 + 60.

Example 3:
Input: startTime = [1,1,1], endTime = [2,3,4], profit = [5,6,4]
Output: 6

*/



// Method-1 --> TLE


int maxValue = 0;
vector<int> dp;

int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit)
{
    int N = profit.size();
    dp = vector<int>(N, 0);

    vector<int> visited(N, 0);

    for(int i=0; i<N; i++)
        maxProfit(startTime, endTime, profit, i);

    //maxProfit(startTime, endTime, profit, 0);
    return maxValue;
}


int maxProfit(vector<int>& startTime, vector<int>& endTime, vector<int>& profit,
              int n)
{
    if(dp[n] != 0)
        return dp[n];

    int N = profit.size();

    for(int i=0; i<N; i++)
    {
        if(endTime[n] <= startTime[i])
        {
            int x = (dp[i] == 0) ?
                maxProfit(startTime, endTime, profit, i) : dp[i];

            dp[n] = max(dp[n], x);
        }
    }

    dp[n] += profit[n];
    maxValue = max(maxValue, dp[n]);

    return dp[n];
}


