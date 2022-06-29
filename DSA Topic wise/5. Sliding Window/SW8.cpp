
// Subarrays with K Different Integers

/*

Given an integer array nums and an integer k, return the number of good subarrays of nums.

A good array is an array where the number of different integers in that array is exactly k.

For example, [1,2,3,1,2] has 3 different integers: 1, 2, and 3.
A subarray is a contiguous part of an array.


Example 1:
Input: nums = [1,2,1,2,3], k = 2
Output: 7
Explanation: Subarrays formed with exactly 2 different integers:
[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]

Example 2:
Input: nums = [1,2,1,3,4], k = 3
Output: 3
Explanation: Subarrays formed with exactly 3 different integers: [1,2,1,3], [2,1,3], [1,3,4].

*/


// With sliding window, we cannot directly calculate #subarrays having exact k unique integers.
// For this, you have to calculate:
//      #subarrays having atmost k unique integers - #subarrays having atmost (k-1) unique integers


int subarraysWithKDistinct(vector<int>& nums, int k) {

    return subarrayWithAtmostKDistinct(nums, k) - subarrayWithAtmostKDistinct(nums, k-1);
}


int subarrayWithAtmostKDistinct(vector<int>& nums, int k)
{
    unordered_map<int, int> mp;
    int number = 0;
    int i=0, j=0;

    while(j < nums.size())
    {
        mp[nums[j]]++;

        if(mp.size() > k)
        {
            while(mp.size() > k)
            {
                mp[nums[i]]--;

                if(mp[nums[i]] == 0)
                    mp.erase(nums[i]);
                i++;
            }
        }

        number += j-i+1;
        j++;
    }

    return number;
}
