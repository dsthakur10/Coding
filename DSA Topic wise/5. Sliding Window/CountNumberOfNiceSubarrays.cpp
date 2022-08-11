
//  Count Number of Nice Subarrays

/*

Given an array of integers nums and an integer k. A continuous subarray is called nice if there are
'K' ODD NUMBERS on it.

Return the number of nice sub-arrays.

Example 1:
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:
Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There is no odd numbers in the array.

Example 3:
Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

*/



// Method-1
//      #subarrays having atmost k odd numbers - #subarrays having atmost (k-1) odd numbers


int numberOfSubarrays(vector<int>& nums, int k) {

    return numberOfSubarraysWithAtmostK(nums, k) - numberOfSubarraysWithAtmostK(nums, k-1);

}


int numberOfSubarraysWithAtmostK(vector<int>& nums, int k)
{
    int n = nums.size();
    unordered_map<int, int> mp;
    int odd=0, number=0;
    int i=0, j=0;

    while(j < n)
    {
        if(nums[j] % 2 == 1)
            odd++;

        if(odd <= k)
            j++;

        else
        {
            while(odd > k)
            {
                if(nums[i] % 2 == 1)
                    odd--;

                i++;
            }
            j++;
        }

        number += j-i;
    }

    return number;
}



// Method-2
// Make given array as binary array. Perform the following conversion :
    // odd number --> 1
    // even number --> 0
// Problem reduces to "number of binary subarrays with sum = k"


int numberOfSubarrays2(vector<int>& nums, int k) {

    for(int i=0; i<nums.size(); i++)
    {
        if(nums[i] % 2 == 0)
            nums[i] = 0;

        else
            nums[i] = 1;
    }

    return subarraysWithAtmostSumK(nums, k) - subarraysWithAtmostSumK(nums, k-1);

}


int subarraysWithAtmostSumK(vector<int>& nums, int goal)
{
    if(goal < 0)
        return 0;

    int n = nums.size();
    int sum = 0, countOfArrays = 0;
    int  i=0, j=0;

    while(j < n)
    {
        sum += nums[j];

        if(sum <= goal)
        {
            countOfArrays += j-i+1;
            j++;
        }

        else
        {
            while(sum > goal)
            {
                sum -= nums[i];
                i++;
            }

            countOfArrays += j-i+1;
            j++;
        }
    }

    return countOfArrays;
}

