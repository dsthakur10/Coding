/*

Given a set of integers, the task is to divide it into two sets S1 and S2 such that the ABSOLUTE DIFFERENCE BETWEEN THEIR SUMS IS MINIMUM.
If there is a set S with n elements, then if we assume Subset1 has m elements, Subset2 must have n-m elements and the value of abs(sum(Subset1) – sum(Subset2)) should be minimum.

*/

#include<iostream>
#include<vector>
#include<cstring>
#include<climits>

static int dp[101][1001];


int minimumSubsetSumDifference(std::vector<int> set, int n);
void SubsetSum2(std::vector<int> set, int n, int sum);


int main()
{
    memset(dp, 0, sizeof(dp));
    int n;
    std::vector<int> arr;

    std::cout << "\nEnter number of items available: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter non-negative integers: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    int minimumDiff = minimumSubsetSumDifference(arr,n);
    std::cout << "\n\nMinimum Subset sum possible = " << minimumDiff;

    return 0;

}




void SubsetSum2(std::vector<int> set, int n, int sum)
{
    //int dp[n+1][sum+1];

    // value of dp[i][j] will be true if there is a subset of set[0..i-1] with sum equal to j


    // j == 0 && i == 0 will still yield TRUE

    for(int j=0; j<sum+1; j++)                                // initialization
        dp[0][j] = 0;

    for(int i=0; i<n+1; i++)
        dp[i][0] = 1;


    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<sum+1; j++)
        {
            if(set[i-1] <= j)
                dp[i][j] = dp[i-1][j] || dp[i-1][j - set[i-1]];

            else
                dp[i][j] = dp[i-1][j];
        }
    }

}



/*
        |S1 - S2| must be minimum. Also, S1 + S2 = ΣS.
        Let S1 < S2. We have to find minimum value of S2 - S1 = ΣS - 2*S1. Our task boils down to maximizing the value S1 that will yield minimum overall value for 'ΣS - 2*S1'

        Now look over all th possible values which S1 can take ranging from  0 to ΣS/2

        Why uptill only ΣS/2 ??
            --> Because if S1 has covered all the values from 0 to ΣS/2, the other half (remaining values) will be covered by S2. S1 + S2 = ΣS
            --> Also because of the assumption S1 < S2 , we cannot take any value which is > ΣS/2 which eventually makes ΣS - 2*S1 negative

        For subset sum S1, we want to find if there exists subset with possible values 0,1,2,.....,ΣS/2
            --> this can be done by calling a single function subsetSum() that will create a DP table for every sum values from 0 to ΣS

        What do we want from the DP table ?
            --> We only want last row because it contains every subset sum from 0-ΣS using any of the n given elements (subset formation)

        Now, push in the vector - every sum value which has TRUE in its cell in DP table.
        Calculate ΣS - 2*vec[i] for every value that was pushed in the vector & return the minimum of them.


*/


int minimumSubsetSumDifference(std::vector<int> set, int n)
{
    int sum = 0, minimum = INT_MAX;
    std::vector<int> candidates;

    for(int i=0; i<n ;i++)
        sum += set[i];

    SubsetSum2(set,n,sum);

/*
    for(int j=0; j<=sum/2; j++)
    {
        if(dp[n][j] == 1)
            candidates.push_back(j);
    }

    for(int i=0; i< candidates.size(); i++)
        minimum = std::min(minimum, sum-2*candidates[i]);
*/

    for(int j=sum/2; j>=0 ; j--)
    {
        if(dp[n][j] == 1)
        {
            minimum = sum - 2*j;
            break;
        }
    }

    return minimum;
}
