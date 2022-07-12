// Longest Arithmetic Subsequence

/*

Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
A sequence seq is arithmetic if seq[i+1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).

Example 1:
Input: nums = [3,6,9,12]
Output: 4
Explanation: The whole array is an arithmetic sequence with steps of length = 3.

Example 2:
Input: nums = [9,4,7,2,10]
Output: 3
Explanation: The longest arithmetic subsequence is [4,7,10].

Example 3:
Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation: The longest arithmetic subsequence is [20,15,10,5].

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

int LIS(vector<int>& nums);

int main()
{
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

    int inc = LIS(arr);
    reverse(arr.begin(), arr.end());
    int dec = LIS(arr);

    cout << "\nINC = " << inc;
    cout << "\nDEC = " << dec;

    cout << "\n" << max(inc, dec);

}


int LIS(vector<int>& nums) {
    int maxLen = 0;
    int n = nums.size();
    int dp[n], diff[n];

    dp[0] = 1;
    diff[0] = 0;

    for(int i=1; i<n; i++)
    {
        dp[i] = 1;
        diff[i] = 0;

        for(int j=0; j<i; j++)
        {
            if(nums[j] < nums[i])
            {
                if((dp[i] < 1 + dp[j]) &&
                   (diff[j] == 0 || nums[i] - nums[j] == diff[j]))
                {
                    dp[i] = 1 + dp[j];
                    diff[i] = nums[i] - nums[j];
                }
            }
        }

        maxLen = max(maxLen, dp[i]);
    }

    cout << "\n Original array: ";
    for(int i=0; i<nums.size(); i++)
        cout << nums[i] << " ";

    cout << "\n Difference array : ";
    for(int i=0; i<n; i++)
        cout << diff[i] << " ";

    return maxLen;
}
