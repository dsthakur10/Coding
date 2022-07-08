/*

Given a string of size ‘n’. The task is to remove or delete the minimum number of characters from the string so that the resultant string is a palindrome.

Note: The order of characters should be maintained

Input : aebcbda
Output : 2

Remove characters 'e' and 'd'. Resultant string will be 'abcba' which is a palindromic string

Input : geeksforgeeks
Output : 8

*/


#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>


// Method-1 --> Using LCS
int LCS(std::string X, std::string Y, int n, int m);
int minDeletePalindrome3(std::string X, int n);


int minDeletePalindrome(std::string X, std::string Y, int n, int m);        // top-down memoization
int minDeletePalindrome2(std::string X, std::string Y, int n, int m);       // bottom-up

static int dp[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    Y = X;

    counter = minDeletePalindrome(X, Y, X.size()-1, 0);
    std::cout << "\n\nTOP-DOWN: Minimum #deletions = " << counter;
/*
    counter = LPS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of LPS = " << counter;
*/

    counter = minDeletePalindrome3(X, X.size());
    std::cout << "\n\nMinimum #deletions = " << counter;

    return 0;
}


// Method-1 --> Using LCS

int minDeletePalindrome3(std::string X, int n)
{

    std::string Y = X;
    reverse(Y.begin(), Y.end());

    int result = LCS(X, Y, n, n);

    return n - result;

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


// Method-2 --> TLE

int minDeletePalindrome(std::string X, int m, int n)
{
    if(m == X.size())
        return 0;

    if(n == 0)
        return 0;

    if(m > n)
        return 0;

    if(dp[m][n] != -1)
        return dp[m][n];

    if(m+1 == n)
        dp[m][n] = 0;

    else if(X[m] == X[n-1])
        dp[m][n] = minDeletePalindrome(X, m+1, n-1);

    else
        dp[m][n] = 1 + min( minDeletePalindrome(X, m+1, n) ,
                            minDeletePalindrome(X, m, n-1) );

    return dp[m][n];

}
