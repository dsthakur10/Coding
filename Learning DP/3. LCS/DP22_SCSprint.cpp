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
#include<algorithm>


// Method-1 --> 2 tables are used --> dp[][] to store length & str[][] to store strings --> TLE

int SCS(std::string X, std::string Y, int n, int m);        // top-down memoization
std::string SCS(std::string X, std::string Y, int n, int m);       // bottom-up

// Method-2 --> 1 table --> Calculate SCS & then backtrack from dp[m][n] to get the string printed
string SCS2(string X, string Y, int n, int m);

// Method-3 --> 1 table --> Calculate LCS & then backtrack...
std::string SCS3(std::string X, std::string Y, int n, int m);


//int SCS(std::string X, std::string Y, int n, int m);

static int dp[100][100];
static std::string scs[100][100];

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
    std::cout << "\n\nTOP-DOWN: SCS = " << scs[X.size()][Y.size()];

    std::cout << "\n\nBOTTOM-UP: SCS = " << SCS2(X, Y, X.size(), Y.size());

    std::cout << "\n\nSCS = " << SCS3(X, Y, X.size(), Y.size());

    return 0;

}



int SCS(std::string X, std::string Y, int n, int m)
{
    if(n == 0)
    {
        dp[n][m] = m;
        scs[n][m].append(Y, 0, m);
    }

    if(m == 0)
    {
        dp[n][m] = n;
        scs[n][m].append(X, 0, n);
    }

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1])
    {
        dp[n][m] = 1 + SCS(X, Y, n-1, m-1);
        scs[n][m] = scs[n-1][m-1] + X[n-1];
    }

    else
    {
        int a = SCS(X, Y, n, m-1);
        int b = SCS(X, Y, n-1, m);

        if(a < b)
        {
            dp[n][m] = 1 + a;
            scs[n][m] = scs[n][m-1] + Y[m-1];
        }

        else
        {
            dp[n][m] = 1 + b;
            scs[n][m] = scs[n-1][m] + X[n-1];
        }
    }


    return dp[n][m];
}



std::string SCS(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];
    std::string scs[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0)
            {
                dp[i][j] = j;
                scs[i][j].append(Y, 0, j) ;
            }

            else if(j==0)
            {
                dp[i][j] = i;
                scs[i][j].append(X, 0, i) ;
            }

            else if(X[i-1] == Y[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
                scs[i][j] = scs[i-1][j-1] + X[i-1];
            }

            else
            {
                if(dp[i][j-1] < dp[i-1][j])
                {
                    dp[i][j] = 1 + dp[i][j-1];
                    scs[i][j] = scs[i][j-1] + Y[j-1];
                }

                else
                {
                    dp[i][j] = 1 + dp[i-1][j];
                    scs[i][j] = scs[i-1][j] + X[i-1];
                }
            }

        }
    }

    return scs[n][m];
}



// Method-2 --> Find SCS --> Backtracks from dp[m][n] all the way back & then reverse the string

string scs2(string X, string Y, int m, int n)
{
    int dp[m+1][n+1];

    for(int i=0; i<m+1; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            if(i == 0)
                dp[i][j] = j;

            else if(j == 0)
                dp[i][j] = i;

            else if(X[i-1] == Y[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1]);
        }
    }

    string str;
    int i = m, j = n;

    while(i > 0 && j > 0)
    {
        if(X[i-1] == Y[j-1])
        {
            str += X[i-1];
            i--;
            j--;
        }

        else if(dp[i-1][j] < dp[i][j-1])
        {
            str += X[i-1];
            i--;
        }

        else
        {
            str += Y[j-1];
            j--;
        }
    }

    while(i > 0)
    {
        str += X[i-1];
        i--;
    }

    while(j > 0)
    {
        str += Y[j-1];
        j--;
    }

    reverse(str.begin(), str.end());
    return str;
}


// Method-3 --> Find LCS --> Backtrack from dp[n][m] all the way till n = 0 || m = 0 & reverse the string

string scs2(string X, string Y, int m, int n)
{
    int dp[m+1][n+1];

    // LCS
    for(int i=0; i<m+1; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            if(i == 0)
                dp[i][j] = 0;

            else if(j == 0)
                dp[i][j] = 0;

            else if(X[i-1] == Y[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    //cout << "lcs = " << dp[m][n];
    string str;

    int i = m, j = n;
    while(i > 0 && j > 0)
    {
        if(X[i-1] == Y[j-1])
        {
            str += X[i-1];
            i--;
            j--;
        }

        else if(dp[i-1][j] > dp[i][j-1])
        {
            str += X[i-1];
            i--;
        }

        else
        {
            str += Y[j-1];
            j--;
        }
    }

    while(i > 0)
    {
        str += X[i-1];
        i--;
    }

    while(j > 0)
    {
        str += Y[j-1];
        j--;
    }

    reverse(str.begin(), str.end());
    return str;
}
