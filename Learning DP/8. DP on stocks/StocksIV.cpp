/*

You are given an integer array prices where prices[i] is the price of a given stock on the ith day,
and an integer k.

Find the maximum profit you can achieve. YOU MAY COMPLETE AT MOST K TRANSACTIONS.

Note: You may not engage in multiple transactions simultaneously(i.e. you must sell the stock before you buy again).

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

*/


// TOP-DOWN

vector<vector<vector<int>>> dp;

int maxProfit(int k, vector<int>& prices) {

    int n = prices.size();
    dp = vector<vector<vector<int>>>
        (n+1, vector<vector<int>> (k+1, vector<int> (2, -1)));

    return solve(prices, 0, k, 1);
}

int solve(vector<int>& prices, int n, int count, int buy)
{
    if(count == 0 || n == prices.size())
        return dp[n][count][buy] = 0;

    if(dp[n][count][buy] != -1)
        return dp[n][count][buy];

    int profit;
    if(buy)
    {
        profit = max( -prices[n] + solve(prices, n+1, count, 0),
                      solve(prices, n+1, count, 1) );
    }

    else
    {
        profit = max( prices[n] + solve(prices, n+1, count-1, 1),
                      solve(prices, n+1, count, 0) );
    }

    return dp[n][count][buy] = profit;
}


// BOTTOM-UP

int maxProfit(int k, vector<int>& prices) {

    int n = prices.size();
    int dp[n+1][k+1][2];

    // nth index --> profit = 0
    for(int j=0; j<=k;j++)
    {
        dp[n][j][0] = 0;
        dp[n][j][1] = 0;
    }

    // count = 0 --> profit = 0
    for(int i=0; i<n; i++)
    {
        dp[i][0][0] = 0;
        dp[i][0][1] = 0;
    }

    for(int i=n-1; i>=0; i--)
    {
        for(int j=1; j<=k; j++)
        {
            dp[i][j][1] = max(-prices[i] + dp[i+1][j][0], dp[i+1][j][1]);

            dp[i][j][0] = max(prices[i] + dp[i+1][j-1][1], dp[i+1][j][0]);
        }
    }

    return dp[0][k][1];
}



// Space optimization

int maxProfit(int k, vector<int>& prices) {

    int n = prices.size();
    vector<vector<int>> cur (k+1, vector<int>(2, 0));
    vector<vector<int>> after (k+1, vector<int>(2, 0));

    // nth index --> profit = 0
    for(int j=0; j<=k;j++)
    {
        after[j][0] = 0;
        after[j][1] = 0;
    }

    // count = 0 --> profit = 0
    after[0][0] = 0;
    after[0][1] = 0;

    for(int i=n-1; i>=0; i--)
    {
        for(int j=1; j<=k; j++)
        {
            cur[j][1] = max(-prices[i] + after[j][0], after[j][1]);
            cur[j][0] = max(prices[i] + after[j-1][1], after[j][0]);

            after[j][1] = cur[j][1];
            after[j][0] = cur[j][0];
        }
    }

    return cur[k][1];
}
