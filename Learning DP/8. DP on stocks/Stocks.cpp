/*

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the
future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

Example 1:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.

Example 2:
Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.

*/


// Method-1 --> O(n) time | O(n) space --> DP

// Calculate minimumSoFar from left & maximumSoFar from right --> return max(maxSoFar[i+1] - minSoFar[i])
// minimumSoFar[i] will return minimum of all prices from (0-i).
// maximumSoFar[i] will return maximum of all prices from (i - n-1).

int maxProfit(vector<int>& prices)
{
    int n = prices.size(), diff = 0;
    int mindp[n], maxdp[n];

    mindp[0] = prices[0];
    for(int i=1; i<n; i++)
        mindp[i] = min(mindp[i-1], prices[i]);

    maxdp[n-1] = prices[n-1];
    for(int i=n-2; i>=0; i--)
        maxdp[i] = max(maxdp[i+1], prices[i]);

    for(int i=0; i<n-1; i++)
        diff = max(diff, maxdp[i+1] - mindp[i]);

    return diff;
}


// Method-2 --> O(1) space
// Keep track of minimum so far using single variable.
// Profit = max(profit, prices[i] - minimum)

int maxProfit(vector<int>& prices) {

    int n = prices.size(), profit = 0;

    int minimum = prices[0];
    for(int i=1; i<n; i++)
    {
        profit = max(profit, prices[i] - minimum);

        minimum = min(minimum, prices[i]);
    }

    return profit;
}
