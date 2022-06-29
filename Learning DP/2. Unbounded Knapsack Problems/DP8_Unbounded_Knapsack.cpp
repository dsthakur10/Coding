/*

Unlimited use of same instance allowed.

If an item is rejected, it cannot be used anytime in future.
If an item is selected, it can be used again anytime in future until it is rejected.

*/


#include<iostream>
#include<vector>
#include<cstring>


int unboundedKnapSack( std::vector<int> wt, std::vector<int> val, int W, int n);            // Top-Down memoization
int unboundedKnapSack2( std::vector<int> wt, std::vector<int> val, int W, int n);           // Bottom-Up


static int dp[101][1001];
//memset(dp, -1, sizeof(dp));                       / memset not working globally

int main()
{

    memset(dp, -1, sizeof(dp));
    int n, W;
    std::vector<int> wt;
    std::vector<int> val;

    std::cout << "\nEnter number of items available: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter values of each items: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        val.push_back(x);
    }

    std::cout << "\nEnter weights of each items: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        wt.push_back(x);
    }

    std::cout << "\nEnter the capacity of knapsack: ";
    std::cin >> W;

    int profit = unboundedKnapSack2(wt, val, W, n);

    std::cout << "\n\nMaximum profit of knapsack = " << profit;
}



// TOP - DOWN

int unboundedKnapSack( std::vector<int> wt, std::vector<int> val, int W, int n)
{
    if(n==0 || W==0)                // base case --> weight = 0 || #items = 0 --> No more items can be added
        return 0;

    if(dp[n][W] != -1)              // available in table
        return dp[n][W];

                                    // if weight[i] < available capacity --> Either select or drop the items
                                            // SELECT --> subtract wt[i] weight from capacity W & add val[i] to profit.
                                            // Drop --> ignore that object. Pick the next element
                                    // Select the option that yields maximum value.
    if(wt[n-1] <= W)
        dp[n][W] = std::max((unboundedKnapSack(wt, val, W, n-1)),  val[n-1] + (unboundedKnapSack(wt, val, W-wt[n-1], n)));

    else
        dp[n][W] = unboundedKnapSack(wt, val, W, n-1);

    return dp[n][W];
}



// BOTTOM - UP

int unboundedKnapSack2( std::vector<int> wt, std::vector<int> val, int W, int n)
{

    int dp[n+1][W+1];

/*
    for(int i=0 ; i<n+1; i++)               // initialization
        dp[i][0] = 0;

    for(int j=0; j<W+1; j++)
        dp[0][j] = 0;

*/

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<W+1; j++)
        {
            if(i == 0 || j==0)
                dp[i][j] = 0;

            else if(wt[i-1] <= j)
                dp[i][j] = std::max( dp[i-1][j],  val[i-1] + dp[i][j - wt[i-1]] );

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[n][W];

}
