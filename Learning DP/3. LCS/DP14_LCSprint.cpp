
/*

Give two strings 'X' & 'Y', find the longest common subsequence.

LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
LCS for input Sequences “AGGTAB” and “GXTXAYB” is “GTAB” of length 4.

*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>


int LCS(std::string X, std::string Y, int n, int m);                // top-down memoization --> returns length but stores LCS in global variable
std::string LCS2(std::string X, std::string Y, int n, int m);       // bottom-up   --> returns LCS, not stored globally

std::string LCS3(std::string X, std::string Y, int n, int m);     // bottom-up --> Calculate string in reverse order by tracking back from dp[n][m] to dp[0][0]/dp[0][1]/dp[1][0]

static int dp[100][100];
static std::string lcs[100][100];

int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    //memset(lcs, '\0', sizeof(lcs));

    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    std::cout << "\nEnter string Y:";
    std::cin >> Y;

    counter = LCS(X, Y, X.size(), Y.size());
    std::cout << "\n\nTOP-DOWN: Length of LCS = " << counter;
    std::cout << "\n\nTOP-DOWN: LCS = " << lcs[X.size()][Y.size()];


    std::cout << "\n\nBOTTOM-UP: LCS2 = " << LCS2(X, Y, X.size(), Y.size());

    std::cout << "\n\nBOTTOM-UP: LCS3 = " << LCS3(X, Y, X.size(), Y.size());

    return 0;
}




int LCS(std::string X, std::string Y, int n, int m)
{
    if(n == 0 || m == 0)
        return 0;

    if(dp[n][m] != -1)
        return dp[n][m];

    if(X[n-1] == Y[m-1])
    {
        dp[n][m] = 1 + LCS(X, Y, n-1, m-1);
        lcs[n][m] = lcs[n-1][m-1] + X[n-1];
        //lcs[n][m] = lcs[n-1][m-1];
        //lcs[n][m] = lcs[n][m].append(1,X[n-1]);
    }

    else
    {
        int a = LCS(X, Y, n, m-1);
        int b = LCS(X, Y, n-1, m);

        if(a > b)
        {
            dp[n][m] = a;
            lcs[n][m] = lcs[n][m-1];
        }

        else
        {
            dp[n][m] = b;
            lcs[n][m] = lcs[n-1][m];
        }
    }

    return dp[n][m];
}




std::string LCS2(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];
    std::string lcs[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i==0 || j==0)
            {
                dp[i][j] = 0;
                lcs[i][j] = "\0";
            }

            else if(X[i-1] == Y[j-1])
            {
                dp[i][j] = 1 + dp[i-1][j-1];
                lcs[i][j] = lcs[i-1][j-1];
                lcs[i][j] = lcs[i][j].append(1,X[i-1]);
            }

            else
            {
                if(dp[i-1][j] > dp[i][j-1])
                {
                    dp[i][j] = dp[i-1][j];
                    lcs[i][j] = lcs[i-1][j];
                }

                else
                {
                    dp[i][j] = dp[i][j-1];
                    lcs[i][j] = lcs[i][j-1];
                }
            }
        }
    }

    return lcs[n][m];
}



std::string LCS3(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];
    std::string lcs;

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

    int i=n, j=m;

    while(i > 0 && j > 0)                   // starting from dp[n][m] back to dp[0][j] OR dp[i][0]
    {
        if(X[i-1] == Y[j-1])                    // append the character if the match is found
        {
            lcs += X[i-1];
            i--;
            j--;
        }

        else                                    // select the cell which has maximum value {either on the left OR on above}
        {
            if(dp[i-1][j] > dp[i][j-1])
                i--;

            else
                j--;
        }
    }

    reverse(lcs.begin(),lcs.end());             // Since we track back in reverse order, we need to reverse the string to get original LCS.

    return lcs;
}
