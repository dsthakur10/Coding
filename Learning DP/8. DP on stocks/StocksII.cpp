/*

You are given an integer array prices where prices[i] is the price of a given stock on the ith day.

On each day, you may decide to buy and/or sell the stock.
YOU CAN ONLY HOLD AT MOST ONE SHARE OF THE STOCK AT ANY TIME.
However, you can buy it then immediately sell it on the same day.

Find and return the maximum profit you can achieve.

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
Total profit is 4 + 3 = 7.

Example 2:
Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Total profit is 4.

Example 3:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: There is no way to make a positive profit, so we never buy the stock to achieve the maximum profit of 0.

*/


// Method - 1

/*

You can have as many buys & sells of stocks but with the constraint: YOU CAN ONLY HOLD ONE STOCK.
You cannot keep buying stocks without selling the already purchased stock.
    --> DP on subsequences
    --> Need to keep track of buy/sell of given stock. --> another variable to maintain apart from given stock

    If you hold a stock (dp[i][0]), you got 2 choices:
        1. Sell at current day price    --> price[i] + dp[i+1][1]   --> add the price of selling + pick next stock
        2. Wait for next day            --> dp[i+1][0]              --> hold it & sell on the next day

    If you do NOT hold a stock (dp[i][1]), you again got 2 choice:
        1. Pick the stock at current price -->  -price[i] + dp[i+1][0]  --> subtract the price of purchasing
        2. Do NOT pick                     -->  dp[i+1][1]              --> purchase on the next day

    At any time, you have to pick the maximum of 2 choices available

For 0th day, you have got complete liberty to buy the stock. (You cannot sell the stock on 0th day without buying)

*/

// TOP-DOWN --> O(n) time | O(n) space

vector<vector<int>> dp;
int maxProfit(vector<int>& prices) {
    int n = prices.size();
    dp = vector<vector<int>> (n, vector<int>(2, -1));

    return solve(prices, 0, 1);
}

int solve(vector<int>& prices, int n, int buy)
{
    if(n == prices.size())
        return 0;

    if(dp[n][buy] != -1)
        return dp[n][buy];

    int profit;
    if(buy)         // you may buy the stock
    {
        profit = max(-prices[n] + solve(prices, n+1, 0), solve(prices, n+1, 1));
    }

    {
    else            // you may sell the stock
        profit = max(prices[n] + solve(prices, n+1, 1), solve(prices, n+1, 0));
    }

    return dp[n][buy] = profit;
}


// BOTTOM-UP --> O(n) time | O(n) space

int maxProfit(vector<int>& prices) {

    int n = prices.size();
    int dp[n+1][2];

    dp[n][0] = 0;
    dp[n][1] = 0;

    for(int i = n-1; i>=0; i--)
    {
        // buy
        dp[i][1] = max(-prices[i] + dp[i+1][0], dp[i+1][1]);

        // sell
        dp[i][0] = max(prices[i] + dp[i+1][1], dp[i+1][0]);
    }

    return dp[0][1];
}



// Space optimized --> O(n) time | O(1) space

int maxProfit(vector<int>& prices) {

    int n = prices.size();

    int nextBuy = 0, nextSell = 0;
    int buy, sell;

    for(int i = n-1; i>=0; i--)
    {
        buy = max(-prices[i] + nextSell, nextBuy);
        sell = max(prices[i] + nextBuy, nextSell);

        nextSell = sell;
        nextBuy = buy;
    }

    return buy;
}
