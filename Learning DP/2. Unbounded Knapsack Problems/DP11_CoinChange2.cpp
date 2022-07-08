/*

*Minimum number of coins to get the change*

Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm } valued coins,
How many minimum #coins can be used to make the change? The order of coins doesn’t matter.

For example,

For N = 4 and S = {1,2,3}, following ways change can be made: {1,1,1,1},{1,1,2},{2,2},{1,3}. Minimum #coins used are {2,2} & {1,3}. So output should be 2.
For N = 10 and S = {2, 5, 3, 6}, following ways change can be made: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}.Minimum #coins used are {5,5}. So, output should be 2.


*/


#include<iostream>
#include<vector>
#include<cstring>
#include<climits>

int coinChangeCoins( std::vector<int> denomination, int S, int N);            // Top-Down memoization
int coinChangeCoins2( std::vector<int> denomination, int S, int N);           // Bottom-Up


static int dp[101][1001];
//memset(dp, -1, sizeof(dp));                       / memset not working globally

int main()
{

    memset(dp, -1, sizeof(dp));
    int N, S;
    std::vector<int> denomination;


    std::cout << "\nEnter money for change: ";
    std::cin >> N;

    std::cout << "\nEnter number of type of coins: ";
    std::cin >> S;

    int x;
    std::cout << "\nEnter denominations of each coins: ";
    for(int i=0; i<S; i++)
    {
        std::cin >> x;
        denomination.push_back(x);
    }

    int counter = coinChangeCoins(denomination, S, N);
    std::cout << "\n\nTOP DOWN --- Minimum #coins = " << counter;

    counter = coinChangeCoins2(denomination, S, N);
    std::cout << "\n\nBOTTOM UP --- Maximum #ways = " << counter;

    return 0;

}




int coinChangeCoins( std::vector<int> denomination, int S, int N)
{
    if(N == 0)
        return 0;

    if(S == 0)
        return INT_MAX - 1;

    if(S == 1)
    {
        if(N % denomination[S-1] == 0)
            dp[S][N] = N / denomination[S-1];

        else
            dp[S][N] = INT_MAX - 1;
    }

    if(denomination[S-1] <= N)
        dp[S][N] = std::min( coinChangeCoins(denomination, S-1, N), 1 + coinChangeCoins(denomination, S, N-denomination[S-1]) );

    else
        dp[S][N] = coinChangeCoins(denomination, S-1, N);

    return dp[S][N];

}



int coinChangeCoins2( std::vector<int> denomination, int S, int N)
{
    int dp[S+1][N+1];


    for(int j=0; j<N+1; j++)
        dp[0][j] = INT_MAX - 1;

    for(int i=0; i<S+1; i++)
        dp[i][0] = 0;


    for(int j=1; j<N+1; j++)
    {
        if(j % denomination[0] == 0)
            dp[1][j] = j / denomination[0];

        else
            dp[1][j] = INT_MAX - 1;

    }


    for(int i=2; i<S+1; i++)
    {
        for(int j=1; j<N+1; j++)
        {
            if(denomination[i-1] <= j)
                dp[i][j] = std::min (dp[i-1][j], 1 + dp[i][j-denomination[i-1]]);

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[S][N];

}



// Method-2 -->

// TOP-DOWN

vector<vector<int>> dp;

int coinChange(vector<int>& coins, int amount) {

    int n = coins.size();
    dp = vector<vector<int>> (n+1, vector<int>(amount+1, -2));

    return minCoins(coins, n, amount);
}

int minCoins(vector<int>& coins, int n, int amount)
{
    if(amount == 0)     // amount used up but coins remaining
        return dp[n][amount] = 0;

    if(n == 0 && amount != 0)          // no coins left but amount remaining
        return dp[n][amount] = -1;

    if(dp[n][amount] != -2)
        return dp[n][amount];

    if(coins[n-1] <= amount)
    {
        int x = minCoins(coins, n-1, amount);   // DO NOT select
        int y = minCoins(coins, n, amount - coins[n-1]);    // select nth coin

        if(x == -1 && y == -1)
            dp[n][amount] = -1;

        else if(x == -1)
            dp[n][amount] = 1 + y;

        else if(y == -1)
            dp[n][amount] = x;

        else
            dp[n][amount] = min(x, 1 + y);

    }

    else
        dp[n][amount] = minCoins(coins, n-1, amount);

    return dp[n][amount];
}



// Method-3 --> Correct way of Aditya Verma's method (Method-1)

// TOP-DOWN

vector<vector<int>> dp;

int coinChange(vector<int>& coins, int amount) {

    int n = coins.size();
    dp = vector<vector<int>> (n+1, vector<int>(amount+1, -1));

    int x = minCoins(coins, n, amount);

    return (x == INT_MAX-1) ? -1 : x;

}

int minCoins(vector<int>& coins, int n, int amount)
{
    if(amount == 0)
        return 0;

    if(n == 0)
        return INT_MAX-1;

    if(dp[n][amount] != -1)
        return dp[n][amount];

    if(coins[n-1] <= amount)
        dp[n][amount] = min(1 + minCoins(coins, n, amount - coins[n-1]), minCoins(coins, n-1, amount));

    else
        dp[n][amount] = minCoins(coins, n-1, amount);

    return dp[n][amount];
}



// BOTTOM-UP

int coinChange(vector<int>& coins, int amount) {

    int n = coins.size();
    vector<vector<int>> dp (n+1, vector<int>(amount+1));

    for(int j = 0; j<amount+1; j++)
        dp[0][j] = INT_MAX-1;

    for(int i = 0; i<n+1; i++)
        dp[i][0] = 0;

    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<amount+1; j++)
        {
            if(coins[i-1] <= j)
                dp[i][j] = min (dp[i-1][j], 1 + dp[i][j-coins[i-1]]);

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    if(dp[n][amount] == INT_MAX-1)
        return -1;

    return dp[n][amount];
}
