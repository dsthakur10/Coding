/*

You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee
representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay
the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again)

*/


// TOP-DOWN --> TLE

vector<vector<int>> dp;

int maxProfit(vector<int>& prices, int fee) {
    int n = prices.size();
    dp = vector<vector<int>> (n, vector<int>(2, -1));

    return solve(prices, 0, 1, fee);
}

int solve(vector<int>& prices, int n, int buy, int fee)
{
    if(n == prices.size())
        return 0;

    if(dp[n][buy] != -1)
        return dp[n][buy];

    int profit;
    if(buy)         // you can buy the stock
    {
        profit = max(-prices[n] + solve(prices, n+1, 0, fee),
                     solve(prices, n+1, 1, fee));
    }

    else            // sell the stock
    {
        profit = max(prices[n] - fee + solve(prices, n+1, 1, fee),
                     solve(prices, n+1, 0, fee));
    }

    dp[n][buy] = profit;
    cout << dp[n][buy] << " ";
    return dp[n][buy];
}


// BOTTOM-UP

int maxProfit(vector<int>& prices, int fee) {

    int n = prices.size();
    int dp[n+1][2];

    dp[n][0] = 0;
    dp[n][1] = 0;

    for(int i = n-1; i>=0; i--)
    {
        // buy
        dp[i][1] = max(-prices[i] + dp[i+1][0], dp[i+1][1]);

        // sell
        dp[i][0] = max(prices[i] - fee + dp[i+1][1], dp[i+1][0]);
    }

    return dp[0][1];
}



// Space optimized

int maxProfit(vector<int>& prices, int fee) {

    int n = prices.size();

    int afterSell = 0, afterBuy = 0;
    int sell, buy;

    for(int i = n-1; i>=0; i--)
    {
        buy = max(-prices[i] + afterSell, afterBuy);
        sell = max(prices[i] - fee + afterBuy, afterSell);
        afterBuy = buy;
        afterSell = sell;
    }

    return buy;
}
