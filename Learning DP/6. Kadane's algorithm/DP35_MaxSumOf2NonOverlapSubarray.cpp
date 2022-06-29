/*

Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.

The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.

Example 1:

Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
Output: 20
Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.

Example 2:

Input: nums = [3,8,1,3,2,1,8,9,0], firstLen = 3, secondLen = 2
Output: 29
Explanation: One choice of subarrays is [3,8,1] with length 3, and [8,9] with length 2.

Example 3:

Input: nums = [2,1,5,6,0,9,5,0,3,8], firstLen = 4, secondLen = 3
Output: 31
Explanation: One choice of subarrays is [5,6,0,9] with length 4, and [3,8] with length 3.

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;


int maxSumSliding(vector<int>& nums, int len, int &start);
int maxSumSlidingiWithoutIndex(vector<int> nums, int len, int notStart, int notEnd);


void leftSum(vector<int>& nums, int lLen, int leftDp[]);
void rightSum(vector<int>& nums, int rLen, int rightDp[]);

int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen);             // will not work
int maxSumTwoNoOverlap2(vector<int>& nums, int firstLen, int secondLen);



int main()
{

    std::vector<int> arr;
    int n,x,len1, len2;

    std::cout << "Enter size: \n";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    std::cout << "Enter sizes of 2 subarrays: \n";
    std::cin >> len1 >> len2;

    int maxSum = maxSumTwoNoOverlap2(arr, len1, len2);

    std::cout << "\n\nMaxSum Subarray = " << maxSum;

    return 0;

}



int maxSumSliding(vector<int>& nums, int len, int &start)
{
    int temp = 0, maxSum = 0;

    for(int i=0; i<len; i++)
        temp += nums[i];

    maxSum = std::max(temp, maxSum);
    start = 0;

    for(int i=len; i<nums.size(); i++)
    {
        temp = temp + nums[i] - nums[i-len];

        if(maxSum < temp)
        {
            maxSum = temp;
            start = i-len+1;
        }
    }

    return maxSum;
}



int maxSumSlidingiWithoutIndex(vector<int> nums, int len, int notStart, int notEnd)
{
    vector<int> arr = nums;

    for(int i=notStart; i<notEnd; i++)
        arr[i] = INT_MIN;

    long long temp = 0, maxSum = 0;

    for(int i=0; i<len; i++)
        temp += arr[i];

    maxSum = std::max<long long>(temp, maxSum);

    for(int i=len; i<arr.size(); i++)
    {
        temp = temp + arr[i] - arr[i-len];

        if(maxSum < temp)
        {
            maxSum = temp;
        }
    }

    return (int)maxSum;
}



// This method will not work because here we are finding maxSum for firstLen subarray & then removing those indices from consideration for maxSum for secondLen subarray
// This might cause wrong output because we are not being dynamic in finding maxSum as a whole.
// maxSum for firstLen subarray maybe maximum but because of it you might not be able to achieve full potential of secondLen subarray.


int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen)
{
    int maxSum, temp, sum1, sum2, sum3, sum4, start;

    start = 0;
    sum1 = maxSumSliding(nums, firstLen, start);
    sum2 = maxSumSlidingiWithoutIndex(nums, secondLen, start, start+firstLen);

    maxSum = sum1 + sum2;

    start = 0;

    sum3 = maxSumSliding(nums, secondLen, start);
    sum4 = maxSumSlidingiWithoutIndex(nums, firstLen, start, start+secondLen);

    std::cout << "\nSUM1 ( " << firstLen << " ) " << sum1;
    std::cout << "\nSUM2 ( " << secondLen << " ) " << sum2;
    std::cout << "\nSUM3 ( " << secondLen << " ) " << sum3;
    std::cout << "\nSUM4 ( " << firstLen << " ) " << sum4;


    maxSum = max(maxSum, sum3+sum4);

    return maxSum;

}



void leftSum(vector<int>& nums, int lLen, int leftDp[])
{
    // start traversing from left side

    int n = nums.size();
    int sum = 0;

    for(int i=0; i<lLen; i++)
    {
        sum += nums[i];
        leftDp[i] = 0;
    }

    leftDp[lLen-1] = sum;

    for(int i=lLen; i<n; i++)
    {
        sum = sum + nums[i] - nums[i-lLen];

        leftDp[i] = max(leftDp[i-1], sum);
    }
}



void rightSum(vector<int>& nums, int rLen, int rightDp[])
{
    // start traversing from right side

    int n = nums.size();
    int sum = 0;

    for(int i=n-1; i>=n-rLen; i--)
    {
        sum += nums[i];
        rightDp[i] = 0;
    }

    rightDp[n-rLen] = sum;

    for(int i=n-rLen-1; i>=0; i--)
    {
        sum = sum + nums[i] - nums[i+rLen];

        rightDp[i] = max(rightDp[i+1], sum);
    }

}



int maxSumTwoNoOverlap2(vector<int>& nums, int firstLen, int secondLen)
{
    int n = nums.size();
    int leftDp[n], rightDp[n];
    int sum = 0, maxSum = 0;

    leftSum(nums, firstLen, leftDp);
    rightSum(nums, secondLen, rightDp);

    std::cout << "\n\nLeft summation for array with size = "<< firstLen << " : ";
    for(int i=0; i<n; i++)
        std::cout << leftDp[i] <<" ";


    std::cout << "\n\nRight summation for array with size = "<< secondLen << " : ";
    for(int i=0; i<n; i++)
        std::cout << rightDp[i] <<" ";


    for(int i=firstLen-1; i<n-secondLen; i++)
    {
        sum = leftDp[i] + rightDp[i+1];
        maxSum = max(maxSum, sum);
    }

    std::cout << "\nMaxSum2 = " << maxSum ;

    leftSum(nums, secondLen, leftDp);
    rightSum(nums, firstLen, rightDp);


    std::cout << "\n\nLeft summation for array with size = "<< secondLen << " : ";
    for(int i=0; i<n; i++)
        std::cout << leftDp[i] <<" ";


    std::cout << "\n\nRight summation for array with size = "<< firstLen << " : ";
    for(int i=0; i<n; i++)
        std::cout << rightDp[i] <<" ";

    for(int i=secondLen-1; i<n-firstLen; i++)
    {
        sum = leftDp[i] + rightDp[i+1];
        maxSum = max(maxSum, sum);
    }

    std::cout << "\nMaxSum2 = " << maxSum ;

    return maxSum;
}
