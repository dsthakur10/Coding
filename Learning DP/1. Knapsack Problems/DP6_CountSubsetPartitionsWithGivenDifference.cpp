
// Given an array arr[] of length N and an integer X, the task is to find the number of subsets with a differnce equal to X.

#include<iostream>
#include<vector>
#include<cstring>

static int dp[100][1000];

int countSubsetSum2(std::vector<int> set, int n, int sum);

int countSubsetPartitionsDifference(std::vector<int> set, int n, int diff);

int main()
{
    memset(dp, -1, sizeof(dp));
    int n, diff;
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

    std::cout << "\nEnter difference value: ";
    std::cin >> diff;

    int counter = countSubsetPartitionsDifference(arr,n,diff);
    std::cout << "\n\n#Subset partitions with difference = "<< diff << " : " << counter;


    return 0;

}




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



/*
        We want to find all the subset partitions where difference between sum of subsets in partition = given value

        S1 + S2 = ΣS
        S1 - S2 = diff

        On solving, we get S1 = (ΣS + diff)/2

        So basically we need to find all the subsets with sum = (ΣS + diff)/2 --> countSubsetSum() function

*/


int countSubsetPartitionsDifference(std::vector<int> set, int n, int diff)
{
    int sum=0;

    for(int i=0; i<n; i++)
        sum += set[i];

    int counter = countSubsetSum2(set,n,(sum+diff)/2);

    return counter;
}
