/*

You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. YOU MAY COMPLETE AT MOST TWO TRANSACTIONS.

Note: You may not engage in multiple transactions simultaneously(i.e. you must sell the stock before you buy again).

Example 1:
Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions
at the same time. You must sell before buying again.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

*/


// WRONG approach

vector<vector<int>> dp;
int maxProfit(vector<int>& prices) {

    int n = prices.size();
    dp = vector<vector<int>> (n, vector<int> (2, -1));

    return solve(prices, 0, 1, 2);
}

int solve(vector<int>& prices, int n, int buy, int count)
{
    if(count == 0 || n == prices.size())
        return 0;

    if(dp[n][buy] != -1)
        return dp[n][buy];

    int profit;
    if(buy)
    {
        profit = max( -prices[n] + solve(prices, n+1, 0, count),
                      solve(prices, n+1, 1, count) );
    }

    else
    {
        profit = max( prices[n] + solve(prices, n+1, 1, count-1),
                      solve(prices, n+1, 0, count) );
    }

    return dp[n][buy] = profit;
}



// Correct approach

vector<vector<vector<int>>> dp;
int maxProfit(vector<int>& prices) {

    int n = prices.size();
    dp = vector<vector<vector<int>>>
        (n+1, vector<vector<int>> (3, vector<int> (2, -1)));

    return solve(prices, 0, 2, 1);
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

int maxProfit(vector<int>& prices) {

    int n = prices.size();
    int dp[n+1][3][2];

    // nth index --> profit = 0
    for(int j=0; j<=2;j++)
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
        for(int j=1; j<=2; j++)
        {
            dp[i][j][1] = max(-prices[i] + dp[i+1][j][0], dp[i+1][j][1]);

            dp[i][j][0] = max(prices[i] + dp[i+1][j-1][1], dp[i+1][j][0]);
        }
    }

    return dp[0][2][1];
}



// Space optimization

int maxProfit(vector<int>& prices) {

    int n = prices.size();
    vector<vector<int>> cur (3, vector<int>(2, 0));
    vector<vector<int>> after (3, vector<int>(2, 0));

    // nth index --> profit = 0
    for(int j=0; j<=2;j++)
    {
        after[j][0] = 0;
        after[j][1] = 0;
    }

    // count = 0 --> profit = 0
    after[0][0] = 0;
    after[0][1] = 0;

    for(int i=n-1; i>=0; i--)
    {
        for(int j=1; j<=2; j++)
        {
            cur[j][1] = max(-prices[i] + after[j][0], after[j][1]);
            cur[j][0] = max(prices[i] + after[j-1][1], after[j][0]);

            after[j][1] = cur[j][1];
            after[j][0] = cur[j][0];
        }
    }

    return cur[2][1];
}
