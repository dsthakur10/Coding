
// Max Consecutive Ones III

/*
Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array 4
if you can flip at most k 0's.

Example 1:
Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6

Example 2:
Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
Output: 10

*/


int longestOnes(vector<int>& nums, int k) {

    int n = nums.size(), zeros=0, maxLen=0;
    int i=0, j=0;

    while(j < n)
    {
        if(nums[j] == 0)
            zeros++;

        if(zeros <= k)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            while(zeros > k)
            {
                if(nums[i] == 0)
                    zeros--;

                i++;
            }
            j++;
        }
    }

    return maxLen;
}
