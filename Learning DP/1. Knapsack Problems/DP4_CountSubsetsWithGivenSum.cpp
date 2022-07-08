
// Given an array arr[] of length N and an integer X, the task is to find the number of subsets with a sum equal to X.

#include<iostream>
#include<vector>
#include<cstring>

using namespace std;
static int dp[100][1000];

// This method works correctly only if we have positive integers in our array.
// Won't work if 0's are included in array.

int countSubsetSum(std::vector<int> set, int n, int sum);
int countSubsetSum2(std::vector<int> set, int n, int sum);


// This method works for every cases

int countSubsetSumModified(std::vector<int> set, int n, int sum);
int countSubsetSumModified2(std::vector<int> set, int n, int sum);


int main()
{
    memset(dp, -1, sizeof(dp));
    int n, sum;
    std::vector<int> arr;

    std::cout << "\nEnter number of elements available: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter non-negative integers: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    std::cout << "\nEnter sum value: ";
    std::cin >> sum;

    int counter = countSubsetSumModified2(arr,n,sum);
    std::cout << "\n\nTOP-DOWN --> #Subsets with sum = "<< sum << " : " << counter;

    //int counter2 = countSubsetSum2(arr,n,sum);
    //std::cout << "\n\nBOTTOM-UP --> #Subsets with sum = "<< sum << " : " << counter2;

    return 0;

}



// TOP - DOWN

/*
    Idea is pretty simple. Instead of putting TRUE/FALSE in the table, store the number of ways in which a sum X can be achieved.

    Starting with the base condition,
        #subsets for sum=0 --> 1 (DO NOT TAKE ANY ELEMENT)

        #subsets when n=0 --> 0 (With no more elements left, you cannot select any element. No way this is possible)

    Now, for filling rest of the table, sum all the number of ways in which we can get subset sum = X from ALL AVAILABLE CHOICES
        - SELECT the particular element i & subtract sum value & then add   dp[i-1][j - set[i-1]]
        - Also IGNORE it & add   dp[i-1][j]

*/


int countSubsetSum(std::vector<int> set, int n, int sum)
{
    if(sum == 0)
        return 1;

    if(n == 0)
        return 0;

    if(dp[n][sum] != -1)
        return dp[n][sum];

    if(set[n-1] <= sum)
        dp[n][sum] = countSubsetSum(set,n-1,sum) + countSubsetSum(set,n-1,sum-set[n-1]);

    else
        dp[n][sum] = countSubsetSum(set,n-1,sum);

    return dp[n][sum];

}



// BOTTOM - UP

int countSubsetSum2(std::vector<int> set, int n, int sum)
{
    int dp[n+1][sum+1];

    for(int j=0; j<sum+1; j++)
        dp[0][j] = 0;

    for(int i=0; i<n+1; i++)
        dp[i][0] = 1;

    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<sum+1; j++)
        {
            if(set[i-1] <= j)
                dp[i][j] = dp[i-1][j] + dp[i-1][j-set[i-1]];

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    return dp[n][sum];
}


// Consider the test case - nums[] : {0,0,0,0,1} sum = 1
// Here the sum can be 1 with different subsets having random #0's.
// But the old logic does not consider the presence of 0's as 0 don't add to result sum
// This can be fixed by changing the base conditions.

/*
    Case-1 : n == 0 | sum == 0
        --> You can always get sum=0 with any number of elements --> dp[0][0] = 1

    Case-2 : n == 0 | sum != 0  (initializing row)
        --> You cannot get required sum in any case if #elements in bag/set = 0 --> dp[0][sum] = 0

    Case-3 : n != 0 | sum = 0
        --> Here comes the modification. You do not need to initialize them with all 1's
        --> Calculate dp[n][0] like normal logic.
        --> Do not count it in base case. WHY ? --> Since there can be multiple ways of getting sum = 0
            & we need them all.
*/


// TOP-DOWN

int countSubsetSumModified(std::vector<int> set, int n, int sum)
{
    if(sum == 0 && n == 0)      // dp[0][0] = 1
        return 1;

    if(n == 0)                  // dp[0][j] = 0 ; j != 0
        return 0;

    if(dp[n][sum] != -1)
        return dp[n][sum];

    if(set[n-1] <= sum)
        dp[n][sum] = countSubsetSum(set,n-1,sum) + countSubsetSum(set,n-1,sum-set[n-1]);

    else
        dp[n][sum] = countSubsetSum(set,n-1,sum);

    return dp[n][sum];

}



// BOTTOM - UP

int countSubsetSumModified2(std::vector<int> set, int n, int sum)
{
    int dp[n+1][sum+1];

    dp[0][0] = 1;

    for(int j=1; j<sum+1; j++)
        dp[0][j] = 0;

    for(int i=1; i<n+1; i++)
    {
        for(int j=0; j<sum+1; j++)
        {
            if(set[i-1] <= j)
                dp[i][j] = dp[i-1][j] + dp[i-1][j-set[i-1]];

            else
                dp[i][j] = dp[i-1][j];
        }
    }

    for(int i=0; i<n+1; i++)
    {
        for(int j=0; j<sum+1; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    return dp[n][sum];
}
