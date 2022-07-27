/*

Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array.
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b

Example 1:
Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]

Example 2:
Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]

*/


// 2 pointers

/*

We want to find a range in given array such that range size = k && it contains numbers as close as possible to x

*/

vector<int> findClosestElements(vector<int>& nums, int k, int x)
{
    int n = nums.size();
    vector<int> result;

    int low = 0, high = n-1;

    // high - low + 1 ==> select just k #elements in range

    while(high - low + 1 > k)
    {
        // we will absolutely ignore nums[low]

        if(abs(nums[low] - x) > abs(nums[high] - x))
            low++;

        // in case of tie breaker, prefer low over high because of indexing

        else
            high--;
    }

    for(int i=low; i<=high; i++)
        result.push_back(nums[i]);

    return result;
}
