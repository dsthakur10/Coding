/*

You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve.
YOU MAY COMPLETE AS MANY TRANSACTIONS AS YOU LIKE (i.e. buy one and sell one share of the stock multiple times)
with the following restrictions:

AFTER YOU SELL YOUR STOCK, YOU CANNOT BUY STOCK ON THE NEXT DAY (i.e., cooldown one day).

Note: You may not engage in multiple transactions simultaneously (i.e. you must sell the stock before you buy again)

Example 1:
Input: prices = [1,2,3,0,2]
Output: 3
Explanation: transactions = [buy, sell, cooldown, buy, sell]

Example 2:
Input: prices = [1]
Output: 0

*/



// TOP-DOWN

vector<vector<int>> dp;
int maxProfit(vector<int>& prices) {

    int n = prices.size();
    dp = vector<vector<int>> (n+1, vector<int>(2, -1));

    return solve(prices, 0, 1);

}

int solve(vector<int>& prices, int n, int buy)
{
    if(n >= prices.size())
        return 0;

    if(dp[n][buy] != -1)
        return dp[n][buy];

    int profit;
    if(buy)
        profit = max(-prices[n] + solve(prices, n+1, 0),
                    solve(prices, n+1, 1));

    else
        profit = max(prices[n] + solve(prices, n+2, 1),
                    solve(prices, n+1, 0));

    return dp[n][buy] = profit;
}



// BOTTOM-UP

vector<vector<int>> dp;
int maxProfit(vector<int>& prices) {

    int n = prices.size();
    dp = vector<vector<int>> (n+2, vector<int>(2, 0));

    dp[n+1][0] = 0;
    dp[n+1][0] = 0;
    dp[n][0] = 0;
    dp[n][1] = 0;

    for(int i=n-1; i>=0; i--)
    {
        dp[i][1] = max(-prices[i] + dp[i+1][0], dp[i+1][1]);
        dp[i][0] = max(prices[i] + dp[i+2][1], dp[i+1][0]);
    }

    return dp[0][1];
}



// Space optimized

int maxProfit(vector<int>& prices) {

    int n = prices.size();

    int afterSell = 0, afterBuy = 0, cooldownBuy = 0;
    int buy, sell;

    for(int i=n-1; i>=0; i--)
    {
        buy = max(-prices[i] + afterSell, afterBuy);
        sell = max(prices[i] + cooldownBuy, afterSell);

        cooldownBuy = afterBuy;
        afterBuy = buy;
        afterSell = sell;
    }

    return buy;
}
