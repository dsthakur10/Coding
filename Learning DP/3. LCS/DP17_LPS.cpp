// Given a sequence, find the length of the longest palindromic subsequence in it.

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>


// Method-1 --> using LCS
int LCS(std::string X, std::string Y, int n, int m);
int LPS(std::string X, int n);

// Method-2 --> Directly
int LPS(std::string X, std::string Y, int n, int m);        // top-down memoization
int LPS2(std::string X, std::string Y, int n, int m);       // bottom-up

// Method-3 --> Directly (TLE in TOP-DOWN)

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



int LPS(std::string X, int n)
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


// Method-2 --> TLE in TOP-DOWN

vector<vector<int>> dp;
int longestPalindromeSubseq(string s) {

    int n = s.size();
    dp = vector<vector<int>>(n+1, vector<int>(n+1, -1));

    return lps(s, 0, n);
}

int lps(string X, int m, int n)
{
    if(m == X.size())
        return 0;

    if(n == 0)
        return 0;

    if(dp[m][n] != -1)
        return dp[m][n];

    if(X[m] == X[n-1])
        dp[m][n] = 1 + lps(X, m+1, n-1);

    else
        dp[m][n] = max(lps(X, m+1, n), lps(X, m, n-1));

    return dp[m][n];
}



// BOTTOM-UP working fine

vector<vector<int>> dp;
int longestPalindromeSubseq(string s) {

    int n = s.size();
    int dp[n+1][n+1];

    for(int i=n; i>=0; i--)             // X
    {
        for(int j=0; j<n+1; j++)        // Y
        {
            if(i == n || j == 0)
                dp[i][j] = 0;

            else if(s[i] == s[j-1])
                dp[i][j] = 1 + dp[i+1][j-1];

            else
                dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
        }
    }

    return dp[0][n];
}


