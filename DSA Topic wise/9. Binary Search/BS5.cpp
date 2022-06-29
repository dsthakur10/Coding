// Split Array Largest Sum

/*

Given an array nums which consists of non-negative integers and an integer m, you can split the array into
'm' non-empty continuous subarrays.

Write an algorithm to minimize the largest sum among these m subarrays.

Example 1:
Input: nums = [7,2,5,10,8], m = 2
Output: 18
Explanation:
There are four ways to split nums into two subarrays. The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.

Example 2:
Input: nums = [1,2,3,4,5], m = 2
Output: 9

Example 3:
Input: nums = [1,4,4], m = 3
Output: 4

*/


// Method-1 Binary Search

// Same as Allocate Minimum #pages

/*
    // nums[] = pages[]
    // numbers = books
    // #subarrays = #students
    // Distribute numbers/books in consecutive manner
    // DONOT overload a subarray/student
    // minimum(maximum sum of subarray)= minimum(maximum pages for a student)
*/

int splitArray(vector<int>& nums, int m) {

    int low = INT_MIN, high = accumulate(nums.begin(), nums.end(), 0);
    for(int x: nums)
        low = max(x, low);

    if(m == 1)
        return high;

    int result = -1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(validPartition(nums, m, mid))
        {
            result = mid;
            high = mid-1;
        }

        else
            low = mid+1;
    }

    return result;
}


bool validPartition(vector<int>& nums, int m, int maxSum)
{
    int subarrays = 1, sum = 0;

    for(int i=0; i<nums.size(); i++)
    {
        sum += nums[i];

        if(sum > maxSum)
        {
            subarrays++;
            sum = nums[i];
        }

        if(subarrays>m)
            return false;
    }

    return true;
}


