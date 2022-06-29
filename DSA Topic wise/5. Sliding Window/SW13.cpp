
// Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

/*

Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that
the absolute difference between any two elements of this subarray is less than or equal to limit.

Example 1:
Input: nums = [8,2,4,7], limit = 4
Output: 2

Explanation: All subarrays are:
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4.
Therefore, the size of the longest subarray is 2.

Example 2:
Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4

Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.

Example 3:
Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3

*/


// Method-1 --> Sliding window with MultiSet

// Store elements in multiSet(to allow duplicates as well).
// At every step, check if largest element - smallest element <= limit. Continue inserting elements if so
// If difference > limit, keep removing elements from beginning until difference becomes <= limit & slide window
// Store the size of set as maxLen

int longestSubarray(vector<int>& nums, int limit)
{
    multiset<int> ms;
    int maxLen = 0;
    int i=0, j=0;

    while(j < nums.size())
    {
        ms.insert(nums[j]);

        if(*ms.rbegin() - *ms.begin() <= limit)
            j++;

        else
        {
            while(*ms.rbegin() - *ms.begin() > limit)
            {
                ms.erase(ms.find(nums[i]));     // ms.erase(nums[i]) will delete all the copies of nums[i]
                i++;
            }
            j++;
        }

        // maxLen = max((int)ms.size(), maxLen );
        maxLen = max(maxLen, j-i);
    }

    return maxLen;
}



// Method-2 --> Sliding window with 2 heaps {MaxHeap & MinHeap}








// Method-3 --> Sliding window with 2 Monotonic Queue (deque)

/*

Create 2 monotonic queues --> To store elements in INCREASING order & DECREASING order

    1. Maintain max/min element at the front of DEC/INC queue.
    2. Store only those elements in queue which might be useful in future
        --> Store only candidates for potential maximum/minimum in future in DEC/INC queue
        --> DEC queue --> while back of queue has element < current element (nums[j]) --> POP it
        --> INC queue --> while back of queue has element > current element (nums[j]) --> POP it
    3. Push current element in both queues
    4. Check if front of DEC queue - front of INC queue <= limit --> update maxLen
    5. while (front of DEC queue - front of INC queue > limit)
        (a). Check if front of queue = i --> pop it (For both queues)
        (b). Decrement window (i++)

If front of deque = nums[i] --> it is the one, we need to dequeue it, since we are gonna move the left pointer.
NOTE: nums[i] will never be larger/smaller than front of DEC/INC deque, and if nums[i] is smaller/larger than
the front, we good, keep moving left pointer until satisfying the limit.

*/

int longestSubarray(vector<int>& nums, int limit) {

    deque<int> dqMin, dqMax;
    int maxLen = 0;
    int i=0, j=0;

    while(j < nums.size())
    {
        while(!dqMax.empty() && nums[j] > dqMax.back())
            dqMax.pop_back();

        while(!dqMin.empty() && nums[j] < dqMin.back())
            dqMin.pop_back();

        dqMax.push_back(nums[j]);
        dqMin.push_back(nums[j]);

        if(dqMax.front() - dqMin.front() <= limit)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            while(dqMax.front() - dqMin.front() > limit)
            {
                if(nums[i] == dqMax.front())
                    dqMax.pop_front();

                if(nums[i] == dqMin.front())
                    dqMin.pop_front();

                i++;
            }

            j++;
        }
        //maxLen = max(maxLen, j-i);
    }
    return maxLen;
}
