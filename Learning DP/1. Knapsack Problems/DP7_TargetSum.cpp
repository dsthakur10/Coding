/*

You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".

Return the number of different expressions that you can build, which evaluates to target

*/


#include<iostream>
#include<vector>
#include<cstring>

static int dp[100][1000];

int countSubsetSum2(std::vector<int> set, int n, int sum);

int targetSum(std::vector<int> set, int n, int target);

int main()
{
    memset(dp, -1, sizeof(dp));
    int n, target;
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

    std::cout << "\nEnter target value: ";
    std::cin >> target;

    int counter = targetSum(arr,n,target);
    std::cout << "\n\n#Expressions you can build for target "<< target << " = " << counter;


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
        You have to divide your set into 2 parts: One with + sign & other with - sign. Evaluate the expression to get final answer.

        Expression is nothing but adding all the positive & negative sign numbers --> Add(all + sign numbers)  -  Add(all - sign numbers)
        --> This is nothing but Count #Subset partitions with given difference (here difference = target)



*/

int targetSum(std::vector<int> set, int n, int target)
{
    int sum=0;

    for(int i=0; i<n; i++)
        sum += set[i];

    int counter = countSubsetSum2(set,n,(sum+target)/2);

    return counter;
}
