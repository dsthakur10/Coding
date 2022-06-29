/*
SCS --> Shortest Common Supersequence

Given two strings X and Y, the task is to find the length of the shortest string that has both X and Y as subsequences.

Input:   X = "geek",  Y = "eke"
Output: 5

String "geeke" has both string "geek" and "eke" as subsequences. NOTE: "gekek" can also be shortest supersequence for given strings

Input:   X = "AGGTAB",  Y = "GXTXAYB"
Output:  9

String "AGXGTXAYB" has both string "AGGTAB" and "GXTXAYB" as subsequences.

*/


#include<iostream>
#include<string>
#include<cstring>
#include<vector>

int LCS(std::string X, std::string Y, int n, int m);

int SCS(std::string X, std::string Y, int n, int m);        // top-down memoization
int SCS2(std::string X, std::string Y, int n, int m);       // bottom-up
int SCS3(std::string X, std::string Y, int n, int m);


//int SCS(std::string X, std::string Y, int n, int m);

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


    counter = SCS(X, Y, X.size(), Y.size());
    std::cout << "\n\nTOP-DOWN: Length of SCS = " << counter;

    counter = SCS2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Length of SCS = " << counter;

    counter = SCS3(X, Y, X.size(), Y.size());
    std::cout << "\n\nLength of SCS = " << counter;

    return 0;

}


/*

int SCS(std::string X, std::string Y, int n, int m)
{
    std::string scs = (X.size() >= Y.size()) ? X : Y;           // stores largest of 2
    std::string temp = (X.size() >= Y.size()) ? Y : X;          // stores smallest of 2

    int i = temp.size()-1;
    int j = scs.size()-1;

    while(i>=0 && j>=0)
    {
        if(temp[i] == scs[j])
        {
            i--;
            j--;
        }

        else
        {
            j--;
        }
    }

    if(i >= 0)
        scs.insert(0,temp,0,i+1);

    return scs.size();
}


*/



int SCS(std::string X, std::string Y, int n, int m)
{
    if(n == 0)
        return m;

    if(m == 0)
        return n;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1])
        dp[n][m] = 1 + SCS(X, Y, n-1, m-1);

    else
        dp[n][m] = 1 + std::min( SCS(X, Y, n, m-1) , SCS(X, Y, n-1, m) );

    return dp[n][m];
}



int SCS2(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0)
                dp[i][j] = j;

            else if(j==0)
                dp[i][j] = i;

            else if(X[i-1] == Y[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = 1 + std::min ( dp[i-1][j], dp[i][j-1] );

        }
    }

    return dp[n][m];
}



int SCS3(std::string X, std::string Y, int n, int m)
{
    int result = n + m - LCS(X, Y, n, m);

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
