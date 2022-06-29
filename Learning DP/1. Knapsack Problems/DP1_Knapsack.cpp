#include<iostream>
#include<vector>
#include<cstring>

int knapSack( std::vector<int> wt, std::vector<int> val, int W, int n);         // Top-Down memoization
int knapSack2( std::vector<int> wt, std::vector<int> val, int W, int n);         // Bottom-Up


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

    int profit = knapSack2(wt, val, W, n);

    std::cout << "\n\nMaximum profit of knapsack = " << profit;
}



// TOP - DOWN

int knapSack( std::vector<int> wt, std::vector<int> val, int W, int n)
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
        dp[n][W] = std::max((knapSack(wt, val, W, n-1)),  val[n-1] + (knapSack(wt, val, W-wt[n-1], n-1)));

    else
        dp[n][W] = knapSack(wt, val, W, n-1);

    return dp[n][W];
}



// BOTTOM - UP

int knapSack2( std::vector<int> wt, std::vector<int> val, int W, int n)
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
                dp[i][j] = std::max( dp[i-1][j],  val[i-1] + dp[i-1][j - wt[i-1]] );

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[n][W];

}
