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

int LCS(std::string X, std::string Y, int n, int m);

int SCS(std::string X, std::string Y, int n, int m);        // top-down memoization
std::string SCS2(std::string X, std::string Y, int n, int m);       // bottom-up
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



std::string SCS2(std::string X, std::string Y, int n, int m)
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




std::string SCS3(std::string X, std::string Y, int n, int m)
{
    std::string scs;
    int dp[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0)
                dp[i][j] = 0;

            else if(j==0)
                dp[i][j] = 0;

            else if(X[i-1] == Y[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = std::max ( dp[i-1][j], dp[i][j-1] );

        }
    }


    int i = n, j = m;

    while(i > 0 && j > 0)
    {
        if(X[i-1] == Y[j-1])
        {
            scs += X[i-1];
            i--;
            j--;
        }

        else
        {
            if(dp[i-1][j] > dp[i][j-1])
            {
                scs += X[i-1];
                i--;
            }

            else
            {
                scs += Y[j-1];
                j--;
            }
        }
    }

    reverse(scs.begin(), scs.end());

    if(i > 0)
        scs.insert(0, X, 0, i);

    if(j > 0)
        scs.insert(0, Y, 0, j);

    return scs;

}
