/*

    Longest Repeating Subsequence

Given a string, find the length of the longest repeating subsequence such that the two subsequences don’t have same string character at the same position,
i.e., any i’th character in the two subsequences shouldn’t have the same index in the original string.


Input: str = "AABEBCDD"
Output: 3

Input: str = "abc"
Output: 0

There is no repeating subsequence

Input: str = "aab"
Output: 1

The two subssequence are 'a'(first) and 'a'(second).
Note that 'b' cannot be considered as part of subsequence as it would be at same index in both.

Input: str = "aabb"
Output: 2

Input: str = "axxxy"
Output: 2

*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>


int LRS(std::string X, std::string Y, int n, int m);        // top-down memoization
int LRS2(std::string X, std::string Y, int n, int m);       // bottom-up

static int dp[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    Y = X;

    counter = LRS(X, Y, X.size(), Y.size());
    std::cout << "\n\nTOP-DOWN: Length of LRS = " << counter;

    counter = LRS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of LRS = " << counter;

    return 0;
}




int LRS(std::string X, std::string Y, int n, int m)
{
    if(n == 0 || m==0)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1] && n != m)
        dp[n][m] = 1 + LRS(X, Y, n-1, m-1);

    else
        dp[n][m] = std::max( LRS(X, Y, n, m-1), LRS(X, Y, n-1, m) );

    return dp[n][m];
}




int LRS2(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 0;

            else if(X[i-1] == Y[j-1] && i != j)
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = std::max (dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];
}

