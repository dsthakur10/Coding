
// Given two strings ‘X’ and ‘Y’, find the length of the longest common substring.

#include<iostream>
#include<string>
#include<cstring>
#include<vector>


int LCsubstring(std::string X, std::string Y, int n, int m, int& counter);        // top-down memoization
int LCsubstring2(std::string X, std::string Y, int n, int m);       // bottom-up

static int dp[100][100];

int main()
{
    int counter = 0;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    std::cout << "\nEnter string Y:";
    std::cin >> Y;

    LCsubstring(X, Y, X.size(), Y.size(), counter);
    std::cout << "\n\nTOP-DOWN: Length of Longest Common SUBSTRING = " << counter;

    int result = LCsubstring2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of Longest Common SUBSTRING = " << result;

    return 0;
}



int LCsubstring(std::string X, std::string Y, int n, int m, int& counter)
{
    //static int counter = 0;

    if(n == 0 || m == 0)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1])
    {
        dp[n][m] = 1 + LCsubstring(X, Y, n-1, m-1,counter);
        counter = std::max(counter, dp[n][m]);
    }

    else
    {
        dp[n][m] = 0;
        counter = std::max(LCsubstring(X, Y, n-1, m, counter), counter);
        counter = std::max(LCsubstring(X, Y, n, m-1, counter), counter);
    }

    return dp[n][m];

}



int LCsubstring2(std::string X, std::string Y, int n, int m)
{
    int counter = 0;
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
        dp[i][0] = 0;

    for(int j=0; j<m+1; j++)
        dp[0][j] = 0;

    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<m+1; j++)
        {
            if(X[i-1] == Y[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
                counter = std::max(counter, dp[i][j]);
            }

            else
                dp[i][j] = 0;
        }
    }

    return counter;
}
