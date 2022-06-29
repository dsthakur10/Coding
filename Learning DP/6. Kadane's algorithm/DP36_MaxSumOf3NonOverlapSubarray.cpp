/*

Given an integer array nums and an integer k, find 3 non-overlapping subarrays of length k with maximum sum and return them.

Return the result as a list of indices representing the starting position of each interval (0-indexed). IF THERE ARE MULTIPLE ANSWERS, RETURN THE LEXICOGRAPHICALLY SMALLEST ONE.

Example 1:

Input: nums = [1,2,1,2,6,7,5,1], k = 2
Output: [0,3,5]

Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.


Example 2:

Input: nums = [1,2,1,2,1,2,1,2,1], k = 2
Output: [0,2,4]


Example 3:

Input: nums = [5,2,1,4,3,4,2,1,3,6,3,3,6], k = 3
Output: [,,]

*/


#include<iostream>
#include<string>
#include<cstring>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;


void leftSum(vector<int>& nums, int k);
void rightSum(vector<int>& nums, int k);

vector<int> maxSumThreeNoOverlap(vector<int>& nums, int k);             // will not work



int main()
{

    std::vector<int> arr;
    int n,x,len;

    std::cout << "Enter size: \n";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    std::cout << "Enter sizes of subarrays: \n";
    std::cin >> len;

    vector<int> maxSum = maxSumThreeNoOverlap(arr, len);

    std::cout << "\n\nMaxSum Subarray indices = ";
    for(int i=0; i<maxSum.size(); i++)
        cout << maxSum[i] <<" ";

    return 0;

}



void leftSum(vector<int>& nums, int k, int leftDp[])
{
    // start traversing from left side

    int n = nums.size();
    int sum = 0;

    for(int i=0; i<k; i++)
    {
        sum += nums[i];
        leftDp[i] = 0;
    }

    leftDp[k-1] = sum;

    for(int i=k; i<n; i++)
    {
        sum = sum + nums[i] - nums[i-k];

        leftDp[i] = max(leftDp[i-1], sum);
    }
}



void rightSum(vector<int>& nums, int k, int rightDp[])
{
    // start traversing from right side

    int n = nums.size();
    int sum = 0;

    for(int i=n-1; i>=n-k; i--)
    {
        sum += nums[i];
        rightDp[i] = 0;
    }

    rightDp[n-k] = sum;

    for(int i=n-k-1; i>=0; i--)
    {
        sum = sum + nums[i] - nums[i+k];

        rightDp[i] = max(rightDp[i+1], sum);
    }

}



vector<int> maxSumThreeNoOverlap(vector<int>& nums, int k)
{

    vector<int> index(3,-1);
    int n = nums.size();
    int leftDp[n], rightDp[n];
    int sum = 0, maxSum = 0;

    leftSum(nums, k, leftDp);
    rightSum(nums, k, rightDp);

    std::cout << "\n\nLeft summation for array with size = "<< k << " : ";
    for(int i=0; i<n; i++)
        std::cout << leftDp[i] <<" ";


    std::cout << "\n\nRight summation for array with size = "<< k << " : ";
    for(int i=0; i<n; i++)
        std::cout << rightDp[i] <<" ";


    for(int i=k; i<2*k; i++)
        sum += nums[i];

    int temp = 0;
    int lSum = 0, rSum = 0;

    for(int i=k ; i<=(n-2*k); i++)
    {
        temp = leftDp[i-1] + sum + rightDp[i+k];            // You can also use prefix Sum to calculate sum in any range
        // temp = leftDp[i-1] + rightDp[i+k] + prefixSum[i+k-1] - prefixSum[i-1];

        if(maxSum < temp)
        {
            index[1] = i;

            lSum = leftDp[i-1];
            rSum = rightDp[i+k];
            maxSum = temp;
        }

        sum = sum + nums[i+k] - nums[i];
    }

    // this will work absolutely fine.

/*
    for(int i=k-1; i<index[1]; i++)
    {
        if(leftDp[i] == lSum)
        {
            index[0] = i-k+1;
            break;
        }
    }

*/

    // won't work here, because rightDp[i] starts from reverse & so you cannot exactly say where is the starting point of our 3rd sub-Array
    // Because, rightDp[i] is still equal to sum but you cannot exactly guess where the starting index is since it can be anywhere from this point

    // You actually need to calculate the sum (first time this sum has occurred) & then compare it with rSum. If found equal, return starting point

/*
    for(int i=index[1]+k; i<=n-k; i++)
    {
        if(rightDp[i] == rSum)
        {
            index[2] = i;
            break;
        }
    }
*/

    int prefixSum[n];
    for(int i=0; i<n; i++)
    {
        if(i==0)
            prefixSum[i] = nums[i];
        else
            prefixSum[i] = prefixSum[i-1] + nums[i];
    }


    for(int i=index[1]+k; i<=n-k; i++)
    {
        if(prefixSum[i+k-1] - prefixSum[i-1] == rSum)
        {
            index[2] = i;
            break;
        }
    }

    for(int i=0; i<=index[1]-k; i++)
    {
        if((prefixSum[i+k-1] - ((i-1<0) ? 0 : prefixSum[i-1])) == lSum)
        {
            index[0] = i;
            break;
        }
    }

    cout << "\n\n MAXSUM = " << maxSum;
    return index;

}
