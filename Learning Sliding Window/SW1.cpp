// MAXIMUM SUM SUBARRAY of size = k

// Given an array of integers and a number k, find the maximum sum of a subarray of size k.

#include<climits>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>

int maxSumSubarray(std::vector<int> nums, int k);
int maxSumSubarray2(std::vector<int> nums, int k);


int main()
{
    int n,k;
    std::vector<int> nums;

    std::cout << "Enter size of vector: ";
    std::cin >> n;

    std::cout << "Enter the array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        nums.push_back(k);
    }

    std::cout << "\nEnter the size of subarray: ";
    std::cin >> k;

    int sum = maxSumSubarray(nums,k);

    std::cout << "\n\nMax sum subarray = " << sum;

    return 0;
}


int maxSumSubarray(std::vector<int> nums, int k)
{
    int sum = 0, n = nums.size(), maxSum;

    if(k > n)
    {
        std::cout << "\n\nINVALID";
        return INT_MIN;
    }

    for(int i=0; i<k; i++)                          // compute the sum of 1st window
        sum += nums[i];

    maxSum = sum;
    for(int i=0; i<n-k; i++)                        // find the max of all windows
    {
        sum = sum + nums[k+i] - nums[i];

        maxSum = std::max(sum,maxSum);
    }

    return maxSum;
}



int maxSumSubarray2(std::vector<int> nums, int k)
{
    int sum = 0, n = nums.size(), maxSum = INT_MIN, i,j;

    if(k > n)
    {
        std::cout << "\n\nINVALID";
        return INT_MIN;
    }

    i = 0;                              // i is the starting of window
    j = 0;                              // j is the ending of window

    while(j < n)                        // until j reaches the end of the array
    {
        sum += nums[j];

        if(j-i+1 < k)                   // sum until size of window = k
            j++;

        else
        {
            maxSum = std::max(sum,maxSum);

            sum -= nums[i];             // removing the 1st element of window
            i++;
            j++;
        }
    }

    return maxSum;
}
