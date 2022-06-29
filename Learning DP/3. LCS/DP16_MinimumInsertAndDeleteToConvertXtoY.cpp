/*

Minimum number of deletions and insertions to transform one string into another.

Given two strings ‘str1’ and ‘str2’ of size m and n respectively.
The task is to remove/delete and insert the minimum number of characters from/in str1 to transform it into str2.
It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.

Input :
str1 = "heap", str2 = "pea"

Output :
Minimum Deletion = 2 and
Minimum Insertion = 1


p and h deleted from heap. Then, p is inserted at the beginning. One thing to note, though p was required yet it was removed/deleted first from its position and
then it is inserted to some other position. Thus, p contributes one to the deletion_count and one to the insertion_count.

*/

#include<iostream>
#include<string>
#include<cstring>
#include<vector>


int minInsertAndDelete(std::string X, std::string Y, int n, int m);        // top-down memoization
std::vector<int> minInsertAndDelete2(std::string X, std::string Y, int n, int m);       // bottom-up
int minInsertAndDelete3(std::string X, std::string Y, int n, int m);



static int dp[100][100];
static int ins[100][100];
static int del[100][100];


int main()
{
    int counter;
    memset(dp, -1, sizeof(dp));
    memset(ins, -1, sizeof(ins));
    memset(del, -1, sizeof(del));
    std::string X,Y;

    std::cout << "Enter string X:";
    std::cin >> X;

    std::cout << "\nEnter string Y:";
    std::cin >> Y;

    counter = minInsertAndDelete(X, Y, X.size(), Y.size());
    std::cout << "\n\nTOP-DOWN: Total number of operations = " << counter;
    std::cout << "\n\n Insert = " << ins[X.size()][Y.size()] << "\t Delete = " << del[X.size()][Y.size()];


    std::vector<int> mylist = minInsertAndDelete2(X, Y, X.size(), Y.size());
    std::cout << "\n\nBOTTOM-UP: Total number of operations = " << mylist[0];
    std::cout << "\n\n Insert = " << mylist[1] << "\t Delete = " << mylist[2];


    return 0;
}



int minInsertAndDelete(std::string X, std::string Y, int n, int m)
{
    if(n == 0)
    {
        dp[n][m] = m;
        ins[n][m] = m;
        del[n][m] = 0;

        return dp[n][m];
    }

    else if(m == 0)
    {
        dp[n][m] = n;
        ins[n][m] = 0;
        del[n][m] = n;

        return dp[n][m];
    }


    if(dp[n][m] != -1)
        return dp[n][m];


    else if(X[n-1] == Y[m-1])
    {
        dp[n][m] = minInsertAndDelete(X, Y, n-1, m-1);
        ins[n][m] = ins[n-1][m-1];
        del[n][m] = del[n-1][m-1];
    }

    else
    {
        int a = minInsertAndDelete(X, Y, n, m-1);
        int b = minInsertAndDelete(X, Y, n-1, m);

        if(a < b)
        {
            dp[n][m] = 1 + a;
            ins[n][m] = 1 + ins[n][m-1];
            del[n][m] = del[n][m-1];
        }

        else
        {
            dp[n][m] = 1 + b;
            ins[n][m] = ins[n-1][m];
            del[n][m] = 1 + del[n-1][m];
        }
    }

    return dp[n][m];
}



std::vector<int> minInsertAndDelete2(std::string X, std::string Y, int n, int m)
{
    int dp[n+1][m+1];
    int ins[n+1][m+1];
    int del[n+1][m+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<m+1; j++)
        {
            if(i == 0)
            {
                dp[i][j] = j;
                ins[i][j] = j;
                del[i][j] = 0;
            }


            else if(j == 0)
            {
                dp[i][j] = i;
                ins[i][j] = 0;
                del[i][j] = i;
            }


            else if(X[i-1] == Y[j-1])
            {
                dp[i][j] = dp[i-1][j-1];
                ins[i][j] = ins[i-1][j-1];
                del[i][j] = del[i-1][j-1];
            }


            else
            {
                if(dp[i][j-1] < dp[i-1][j])
                {
                    dp[i][j] = 1 + dp[i][j-1];
                    ins[i][j] = 1 + ins[i][j-1];
                    del[i][j] = del[i][j-1];
                }

                else
                {

                    dp[i][j] = 1 + dp[i-1][j];
                    ins[i][j] = ins[i-1][j];
                    del[i][j] = 1 + del[i-1][j];
                }

            }
        }
    }

    return { dp[n][m], ins[n][m], del[n][m] };
}


