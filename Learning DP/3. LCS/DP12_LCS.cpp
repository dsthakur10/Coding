/*

Give two strings 'X' & 'Y', find the longest common subsequence.

LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.

*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>


int LCS(std::string X, std::string Y, int n, int m);        // top-down memoization
int LCS2(std::string X, std::string Y, int n, int m);       // bottom-up

static int dp[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    std::cout << "\nEnter string Y:";
    std::cin >> Y;

    counter = LCS(X, Y, X.size(), Y.size());
    std::cout << "\n\nTOP-DOWN: Length of LCS = " << counter;

    counter = LCS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of LCS = " << counter;

    return 0;
}




int LCS(std::string X, std::string Y, int n, int m)
{
    if(n == 0 || m==0)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1])
        dp[n][m] = 1 + LCS(X, Y, n-1, m-1);

    else
        dp[n][m] = std::max( LCS(X, Y, n, m-1), LCS(X, Y, n-1, m) );

    return dp[n][m];
}




int LCS2(std::string X, std::string Y, int n, int m)
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
