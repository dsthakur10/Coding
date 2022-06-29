/*

Given : Given 2 strings X & Y, determine if either one is subsequence of the other.

eg:
Input: X = ADXCPY
       Y = AXP

Output: TRUE

*/


#include<iostream>
#include<string>
#include<cstring>
#include<vector>


int LCS(std::string X, std::string Y, int n, int m);
bool seqPatternMatching(std::string X, std::string Y, int n, int m);

static int dp[100][100];

int main()
{
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    std::cout << "\nEnter string Y:";
    std::cin >> Y;

    bool flag = LCS(X, Y, X.size(), Y.size());
    std::cout << "\n\n" << (X.size() < Y.size() ? X : Y) << " is a subsequence of " << (X.size() < Y.size() ? Y : X) << " : " << std::boolalpha << flag;

    return 0;
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



bool seqPatternMatching(std::string X, std::string Y, int n, int m)
{
    int result = LCS(X, Y, n, m);

    if(result == std::min (n, m))
        return true;

    else
        return false;
}
