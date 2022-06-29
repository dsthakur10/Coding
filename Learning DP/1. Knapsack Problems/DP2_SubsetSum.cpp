


#include<iostream>
#include<vector>
#include<cstring>

static int dp[100][1000];


int isSubsetSum(std::vector<int> set, int n, int sum);
bool isSubsetSum2(std::vector<int> set, int n, int sum);


int main()
{
    memset(dp, -1, sizeof(dp));
    int n, sum;
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

    std::cout << "\nEnter sum value: ";
    std::cin >> sum;


    int flag = isSubsetSum(arr,n,sum);
    std::cout << "\n\nTOP-DOWN --> Subset sum possible = " << flag;

    bool flag2 = isSubsetSum2(arr,n,sum);
    std::cout << "\n\nBOTTOM-UP --> Subset sum possible = " << std::boolalpha << flag2;

    return 0;

}



// TOP - DOWN

int isSubsetSum(std::vector<int> set, int n, int sum)
{
    // sum == 0 && n == 0 will still yield TRUE

    if(sum == 0)                                        // Empty subset would do that
        return 1;

    if(n == 0)                                          // sum!=0 but n==0 --> no numbers left to choose --> sum cannot be formed
        return 0;

    if(dp[n][sum] != -1)
        return dp[n][sum];

                                    // if set[i-1] <= sum value --> Either SELECT or DROP this ith element
                                            // SELECT --> subtract its value from sum
                                            // DROP --> Ignore it. Pick the next element
                                    // return TRUE if any of the above 2 choices yields TRUE

    if(set[n-1] <= sum)
        dp[n][sum] = isSubsetSum(set,n-1,sum) || isSubsetSum(set,n-1,sum-set[n-1]);

    else
        dp[n][sum] = isSubsetSum(set,n-1,sum);

    return dp[n][sum];

}


// BOTTOM - UP

bool isSubsetSum2(std::vector<int> set, int n, int sum)
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
