/*

Given a rod of length n inches and an array of prices that includes prices of all pieces of size <= n.
Determine the maximum value obtainable by cutting up the rod and selling the pieces.

For example, if the length of the rod is 8 and the values of different pieces are given as the following, then the maximum obtainable value is 22
(by cutting in two pieces of lengths 2 and 6)

length   | 1   2   3   4   5   6   7   8
--------------------------------------------
price    | 1   5   8   9  10  17  17  20

*/



#include<iostream>
#include<vector>
#include<cstring>


int rodCutting( std::vector<int> len, std::vector<int> val, int L, int n);            // Top-Down memoization
int rodCutting2( std::vector<int> len, std::vector<int> val, int L, int n);           // Bottom-Up


static int dp[101][1001];
//memset(dp, -1, sizeof(dp));                       / memset not working globally

int main()
{

    memset(dp, -1, sizeof(dp));
    int n, L;
    std::vector<int> len;
    std::vector<int> val;


    std::cout << "\nEnter the size of rod: ";
    std::cin >> L;

    std::cout << "\nEnter number of segments allowed to be taken for rod: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter values of each segment: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        val.push_back(x);
    }

    std::cout << "\nEnter lengths of each possible segment: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        len.push_back(x);
    }

    int profit = rodCutting(len, val, L, n);
    std::cout << "\n\nTOP DOWN --- Maximum profit from rod-cutting = " << profit;

    profit = rodCutting2(len, val, L, n);
    std::cout << "\n\nBOTTOM UP --- Maximum profit from rod-cutting = " << profit;

    return 0;

}



/*
    Why to use L & n (#pieces-allowed) as table size ?

    --> L is length of the given rod & we have to make assumption on every possible cut
    --> n is #pieces allowed to cut for calculating maximum profit

    Not all the pieces (1,2,3,...L) will be allowed to cut.

    for eg.

        length   | 1   2   5   7   8
        -------------------------------
        price    | 2   7   10   18  20

    Here, cuts are allowed only for len = {1,2,5,7,8}

    In such cases, n != L

*/

int rodCutting( std::vector<int> len, std::vector<int> val, int L, int n)
{
    if(L == 0 || n == 0)
        return 0;

    if(dp[n][L] != -1)
        return dp[n][L];

    if(len[n-1] <= L)
        dp[n][L] = std::max( rodCutting(len, val, L, n-1), val[n-1] + rodCutting(len, val, L-len[n-1], n) );

    else
        dp[n][L] = rodCutting(len, val, L, n-1);

    return dp[n][L];

}




int rodCutting2( std::vector<int> len, std::vector<int> val, int L, int n)
{
    int dp[n+1][L+1];

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<L+1; j++)
        {
            if(i == 0 || j == 0)
                dp[i][j] = 0;

            else if(len[i-1] <= j)
                dp[i][j] = std::max( dp[i-1][j], val[i-1] + dp[i][j - len[i-1]] );

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[n+1][L+1];
}



// Case when every piece is allowed to use from 1 -> Length
// Here, there will be no need to store length[] array as every piece is allowed

// len[n-1] is nothing but length "n". So instead of using "len - length[n-1]", we can use "len - n" directly

    // function call --> maxPrice(price, n, n);


// TOP-DOWN

int maxPrice(int price[], int n, int len)
{
    if(n == 0)
        return 0;

    if(len == 0)
        return 0;

    if(dp[n][len] != -1)
        return dp[n][len];

    if(n <= len)
        dp[n][len] = max(maxPrice(price, n-1, len),
                    price[n-1] + maxPrice(price, n, len - n));
    else
        dp[n][len] = maxPrice(price, n-1, len);

    return dp[n][len];
}



// BOTTOM-UP
int cutRod(int price[], int n) {

    int dp[n+1][n+1];

    // i --> #pieces
    // j --> length of rod to be sold

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            if(i==0 || j==0)
                dp[i][j] = 0;

            else
            {
                if(i <= j)
                {
                    dp[i][j] = max(price[i-1] + dp[i][j-i], dp[i-1][j]);
                }

                else
                    dp[i][j] = dp[i-1][j];
            }
        }
    }

    return dp[n][n];
}
