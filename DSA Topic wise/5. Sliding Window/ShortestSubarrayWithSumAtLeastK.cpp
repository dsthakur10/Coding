// Shortest Subarray with Sum at Least K

/*
Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums
with a sum of at least k. If there is no such subarray, return -1.

Example 1:
Input: nums = [1], k = 1
Output: 1

Example 2:
Input: nums = [1,2], k = 4
Output: -1

Example 3:
Input: nums = [2,-1,2], k = 3
Output: 3

NOTE: Array may contain negative numbers
*/


// This problem is hard because of the inclusion of negative elements in array, otherwise we could have done it
// in normal way like every other sliding window problem


// Logic --> Modified sliding window with deque




int shortestSubarray(vector<int>& nums, int k)
{
    int n = nums.size();
    vector<long> prefixSum(n+1,0);
    deque<int> dq;
    int minLen = INT_MAX, j=0;

    if(n == 1)
    {
        if(nums[0] >= k)
            return 1;
        else
            return -1;
    }

    for(int i=0; i<n; i++)
        prefixSum[i+1] = prefixSum[i] + nums[i];

    while(j < n+1)
    {
        while(!dq.empty() && prefixSum[j] <= prefixSum[dq.back()])
            dq.pop_back();

        dq.push_back(j);

        if(prefixSum[j] - prefixSum[dq.front()] < k)
        {
            j++;
        }

        else
        {
            while(!dq.empty() &&
                  prefixSum[j] - prefixSum[dq.front()] >= k)
            {
                minLen = min(minLen, j - dq.front());
                dq.pop_front();
            }
            j++;
        }
    }

    return minLen == INT_MAX ? -1 : minLen;
}
