
// Print LIS
// Use hashing to trace back from dp[n] = maxLen till dp[n] = 1
// Use path[n] to store prev index of LIS ending at index-i
// path[i] --> prev Index in LIS ending at index-i


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

static int dp[101];
static int path[101];
int maxx = 0;
int maxIndex = 0;

int LIS(std::vector<int> arr, int n);
vector<int> printLCS(vector<int> arr, int n);

int main()
{
    memset(dp, -1, sizeof(dp));
    std::vector<int> arr;
    int n,x;

    std::cout << "Enter size: \n";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    LIS(arr,n-1);

    cout << "\n";
    for(int i=0; i<n; i++)
        std::cout << dp[i] << " ";

    cout << "\n\n";
    for(int i=0; i<n; i++)
        std::cout << path[i] << " ";

    vector<int> lis = printLCS(arr, n);

    for(int i=0; i<lis.size(); i++)
        std::cout << lis[i] << " ";

}


vector<int> printLCS(vector<int> arr, int n)
{
    int index = maxIndex;
    vector<int> lis(maxx);

    int counter = maxx-1;
    while(index != path[index])
    {
        lis[counter] = arr[index];
        index = path[index];
        counter--;
    }

    lis[counter] = arr[index];

    return lis;
}

int LIS(std::vector<int> arr, int n)
{
    if(dp[n] != -1)
        return dp[n];

    path[n] = n;
    if(n == 0)
    {
        dp[n] = 1;
        return dp[n];
    }

    dp[n] = 1;

    for(int k=n-1; k>=0; k--)
    {
        int temp = (dp[k] != -1) ? dp[k] : LIS(arr , k);

        if(arr[k] < arr[n])
        {
            if(dp[n] < 1 + temp)
            {
                dp[n] = 1 + temp;
                path[n] = k;
            }
        }
    }

    if(maxx < dp[n])
    {
        maxx = dp[n];
        maxIndex = n;
    }

    return dp[n];
}

