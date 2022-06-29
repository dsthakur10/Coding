/*

*Maximum number of ways to get the change*

Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm } valued coins,
How many ways can we make the change? The order of coins doesn’t matter.

For example,

For N = 4 and S = {1,2,3}, there are four solutions: {1,1,1,1},{1,1,2},{2,2},{1,3}.     So output should be 4.
For N = 10 and S = {2, 5, 3, 6}, there are five solutions: {2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}.      So the output should be 5.


*/


#include<iostream>
#include<vector>
#include<cstring>


int coinChangeWays( std::vector<int> denomination, int S, int N);            // Top-Down memoization
int coinChangeWays2( std::vector<int> denomination, int S, int N);           // Bottom-Up


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

    int ways = coinChangeWays(denomination, S, N);
    std::cout << "\n\nTOP DOWN --- Maximum #ways = " << ways;

    ways = coinChangeWays2(denomination, S, N);
    std::cout << "\n\nBOTTOM UP --- Maximum #ways = " << ways;

    return 0;

}




int coinChangeWays( std::vector<int> denomination, int S, int N)
{
    if(N == 0)
        return 1;

    if(S == 0)
        return 0;

    if(dp[S][N] !=-1)
        return dp[S][N];

    if(denomination[S-1] <= N)
        dp[S][N] = coinChangeWays(denomination, S-1, N) + coinChangeWays(denomination, S, N-denomination[S-1]);

    else
        dp[S][N] = coinChangeWays(denomination, S-1, N);

    return dp[S][N];
}




int coinChangeWays2( std::vector<int> denomination, int S, int N)
{
    int dp[S+1][N+1];

    for(int j=0; j<N+1; j++)
        dp[0][j] = 0;

    for(int i=0; i<S+1; i++)
        dp[i][0] = 1;

    for(int i=1; i<S+1; i++)
    {
        for(int j=1; j<N+1; j++)
        {
            if(denomination[i-1] <= j)
                dp[i][j] = dp[i-1][j] + dp[i][j-denomination[i-1]];

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[S][N];
}

