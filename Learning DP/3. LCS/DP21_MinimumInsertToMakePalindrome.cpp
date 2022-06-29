/*

Given string X, the task is to find the minimum number of characters to be inserted to convert it to a palindrome.

Examples:

ab: Number of insertions required is  1  i.e. bab
aa: Number of insertions required is  0  i.e. aa
abcd: Number of insertions required is  3  i.e. dcbabcd
abcda: Number of insertions required is  2  i.e. adcbcda which is the same as the number of insertions in the substring bcd(Why?).
abcde: Number of insertions required is  4  i.e. edcbabcde

*/


#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>



int LCS(std::string X, std::string Y, int n, int m);

int minInsertPalindrome(std::string X, std::string Y, int n, int m);        // top-down memoization
int minInsertPalindrome2(std::string X, std::string Y, int n, int m);       // bottom-up
int minInsertPalindrome3(std::string X, int n);

static int dp[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    Y = X;

    counter = minInsertPalindrome(X, Y, X.size()-1, 0);
    std::cout << "\n\nTOP-DOWN: Minimum #insertions = " << counter;
/*
    counter = LPS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of LPS = " << counter;
*/

    counter = minInsertPalindrome3(X, X.size());
    std::cout << "\n\nMinimum #insertions = " << counter;

    return 0;
}



int minInsertPalindrome(std::string X, std::string Y, int n, int m)
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
        dp[n][m] = 0;

    else if(X[n] == Y[m])
        dp[n][m] = minInsertPalindrome(X, Y, n-1, m+1);

    else
        dp[n][m] = 1 + std::min ( minInsertPalindrome(X, Y, n-1, m) , minInsertPalindrome(X, Y, n, m+1) );

    return dp[n][m];

}









int minInsertPalindrome3(std::string X, int n)
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
