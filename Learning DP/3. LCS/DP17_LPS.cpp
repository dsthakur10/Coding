// Given a sequence, find the length of the longest palindromic subsequence in it.

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>


int LCS(std::string X, std::string Y, int n, int m);

int LPS(std::string X, std::string Y, int n, int m);        // top-down memoization
int LPS2(std::string X, std::string Y, int n, int m);       // bottom-up
int LPS3(std::string X, int n);

static int dp[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    Y = X;

    counter = LPS(X, Y, X.size()-1, 0);
    std::cout << "\n\nTOP-DOWN: Length of LPS = " << counter;

    counter = LPS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of LPS = " << counter;

    return 0;
}



int LPS(std::string X, std::string Y, int n, int m)
{
    if(n == 0)
        return 0;

    if(m == Y.size())
        return 0;

    if(m > n)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    else if(n == m)
        dp[n][m] = 1;

    else if(X[n] == Y[m])
        dp[n][m] = 2 + LPS(X, Y, n-1, m+1);

    else
        dp[n][m] = std::max ( LPS(X, Y, n-1, m) , LPS(X, Y, n, m+1) );

    return dp[n][m];

}



int LPS2(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
        dp[i][0] = 0;

    for(int j=0; j<n+1; j++)
        dp[0][j] = 0;

    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<=n+1-k ; i++)
        {
            int j = i+k-1;

            if(i==j)
                dp[i][j] = 1;

            else if(X[i] == Y[j])
                dp[i][j] = 2 + dp[i+1][j-1];

            else
                dp[i][j] = std::max ( dp[i+1][j] , dp[i][j-1] );
        }
    }

    return dp[1][n];
}




int LPS3(std::string X, int n)
{

    std::string Y = X;
    reverse(Y.begin(), Y.end());

    int result = LCS(X, Y, n, n);

    return result;

}



int LCS(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 0;

            else if(X[i-1] == Y[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = std::max (dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];
}
