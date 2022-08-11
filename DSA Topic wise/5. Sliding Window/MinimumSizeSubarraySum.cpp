// Minimum Size Subarray Sum

/*

Given an array of positive integers nums and a positive integer target, return the minimal length of a
contiguous subarray [numsl, numsl+1, ..., numsr-1, numsr] of which the sum is greater than or equal to target.
If there is no such subarray, return 0 instead.

Example 1:
Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2

Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:
Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:
Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

NOTE : Numbers are all POSITIVE
*/


// Method-1 --> Brute force --> O(n^3)

int minSubArrayLen(int target, vector<int>& nums) {

    int n = nums.size();
    int length = INT_MAX;

    for (int i = 0; i < n; i++)         // start of each subarray
    {
        for (int j = i; j < n; j++)         // end of each subarray
        {
            int sum = 0;
            for (int k = i; k <= j; k++)        // calculate sum of subarray (i,j)
                sum += nums[k];

            if (sum >= target)
            {
                length = min(length, (j - i + 1));
                break;

            //Found the smallest subarray with sum>=s starting with index i
            //hence move to next index
            }
        }
    }

    return (length == INT_MAX) ? 0 : length ;
}



// Method-2 --> Prefix-Sum (Better brute force) --> Time - O(n^2) | Space - O(n)

int minSubArrayLen(int target, vector<int>& nums) {

    int n = nums.size();
    int length = INT_MAX;
    vector<int> prefixSum(n);

    prefixSum[0] = nums[0];
    for(int k=1; k<n; k++)
        prefixSum[k] = prefixSum[k-1] + nums[k];

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (prefixSum[j] - prefixSum[i] + nums[i] >= target)
            {
                length = min(length, (j - i + 1));
                break;

            //Found the smallest subarray with sum>=s starting with index i
            //hence move to next index
            }
        }
    }

    return (length == INT_MAX) ? 0 : length ;
}



// Method-3 --> Prefix-Sum + Binary Search --> Time - O(nlogn) | Space - O(n)

// Instead of finding the lowest sum <= target starting from index i linearly, we can use binary search.

// lower_bound(first, last, val) returns LOWEST index having element <= val.
// If all elements < val --> return last iterator
// If all elements > val --> return first iterator
// Range of search --> [first, last) {NOT including last}

// We will be searching "target + prefixSum[i-1]" & not just target in the prefixSum array
// Because we start our search from index i & so we want to have subarray sum starting from index i, but prefixSum[]
// includes the sum from previous indices as well. So to get target from this index i, we will add all the elements
// from previous indices as new VALUE to search in our prefixSum[]

int minSubArrayLen(int target, vector<int>& nums) {

    int n = nums.size();
    int length = INT_MAX;
    vector<int> prefixSum(n+1);

    prefixSum[0] = 0;
    for(int k=1; k<=n; k++)
        prefixSum[k] = prefixSum[k-1] + nums[k-1];

    for (int i = 1; i <= n; i++)
    {
        int val = target + prefixSum[i-1];

        auto lower = lower_bound(prefixSum.begin(), prefixSum.end(), val);

        if(lower != prefixSum.end())
            length = min(length, (int)(lower - prefixSum.begin() - i + 1));
    }

    return (length == INT_MAX) ? 0 : length ;
}




// Method-4 --> Better brute force --> Time - O(n^2)

int minSubArrayLen(int target, vector<int>& nums) {

    int minLen = INT_MAX;

    for (int i = 0; i < nums.size() && minLen > 1; i++)
    {
        int sum = 0;
        for (int j = i; j < nums.size(); j++)
        {
            sum += nums[j];
            if (sum >= target)
            {
                minLen = min(minLen, j - i + 1);
                break;  // we can't find a shorter subarray that starts at i
            }
        }
    }

    return minLen == INT_MAX ? 0 : minLen;
}




// Method-5 --> Sliding window  / TWO-pointer

int minSubArrayLen(int target, vector<int>& nums) {

    int sum = 0, length = INT_MAX;
    int n = nums.size(), i=0, j=0;

    while(j < n)
    {
        sum += nums[j];

        if(sum < target)
            j++;

        else
        {
            while(sum >= target)
            {
                length = min(length, j-i+1);
                sum -= nums[i];
                i++;
            }

            j++;
        }
    }

    return length == INT_MAX ? 0 : length;
}
