/*
Equal sum Partition problem is to determine whether a given set can be partitioned into two subsets such that the sum of elements in both subsets is the same.

Partitions are --> mutually exclusive & exhaustive sets

A UNION B = S
A INTERSECTION B = NULL

*/



#include<iostream>
#include<vector>
#include<cstring>


bool isSubsetSum(std::vector<int> set, int n, int sum);
bool canPartition(std::vector<int> set);


int main()
{
    int n, sum;
    std::vector<int> arr;

    std::cout << "\nEnter number of array elements: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter non-negative integers: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    bool flag = canPartition(arr);
    std::cout << "\n\nPartition possible = " << std::boolalpha << flag;

    return 0;

}



bool isSubsetSum(std::vector<int> set, int n, int sum)
{
    bool dp[n+1][sum+1];

    // value of dp[i][j] will be true if there is a subset of set[0..i-1] with sum equal to j


    // j == 0 && i == 0 will still yield TRUE

    for(int j=0; j<sum+1; j++)                                // initialization
        dp[0][j] = false;

    for(int i=0; i<n+1; i++)
        dp[i][0] = true;


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

    return dp[n][sum];
}



/*
        ΣA =  ΣB =  (ΣS)/2      --> Equal sum partition
        This implies  ΣS must be even.

        If  ΣS is odd, you cannot have 2 equal sum partitions --> return FALSE

        Given the  ΣS is even, do we have to find subset sum of 2 partitions having sum =  ΣS/2 ?? ---> NO

        Because, if one of the partition(A) has sum  (ΣS)/2, other partition(B) will also have same sum because of the definition of S & will contain all the elements not in A

*/


bool canPartition(std::vector<int> set)
{
    int sum = 0;
    int n = set.size();

    for(int i=0; i<n; i++)
        sum += set[i];

    if(sum %2 == 1)                         // return false if sum is odd
        return false;

    return isSubsetSum(set,n,sum/2);        // find if there exists subset-sum of set S with sum value =  (ΣS)/2

}
