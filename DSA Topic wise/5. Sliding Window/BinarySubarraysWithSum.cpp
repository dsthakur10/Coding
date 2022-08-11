
// Binary Subarrays With Sum

/*

Given a binary array nums and an integer goal, return the number of non-empty subarrays with a sum goal.

A subarray is a contiguous part of the array.

nums[i] is either 0 or 1.
0 <= goal <= nums.length

Example 1:
Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Example 2:
Input: nums = [0,0,0,0,0], goal = 0
Output: 15

*/



// WRONG --> Does not count sum in the middle

int numSubarraysWithSum(vector<int>& nums, int goal) {

    int n = nums.size();
    int sum = 0, countOfArrays = 0;
    int  i=0, j=0;

    while(j < n)
    {
        sum += nums[j];

        if(sum == goal)
        {
            countOfArrays++;
            j++;
        }

        else if(sum < goal)
            j++;

        else
        {
            while(sum > goal)
            {
                sum -= nums[i];
                i++;
            }

            j++;
        }
    }

    while(i < n && sum == goal)
    {
        sum -= nums[i];
        countOfArrays++;
        i++;
    }

    return countOfArrays;
}



// Method-1 --> #subarrays having sum <= k - #subarrays having sum <= (k-1)


int numSubarraysWithSum(vector<int>& nums, int goal) {

    return atmost(nums, goal) - atmost(nums, goal-1);

}

int atmost(vector<int>& nums, int goal)
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



// Method-2 --> Prefix Sum + HashMap --> Convert into 2-pointer problem

/*
Sum of window [i,j] = prefixSum[j] - prefixSum[i-1]
--> We have to find pairs (i,j) i < j such that : prefixSum[j] - prefixSum[i-1] = goal
--> This is nothing but 2Sum problem:
        prefixSum[i-1] = prefixSum[j] - goal
Use HashMap to store <prefixSum, frequency>
*/

int numSubarraysWithSum(vector<int>& nums, int goal)
{
    int n = nums.size();
    unordered_map<int, int> mp;     // <prefixSum, frequency>
    int countOfArrays = 0, prefixSum = 0;

    // mp[0] = 1;       --> for prefixSum = goal

    for(int k=0; k<n; k++)
    {
        prefixSum += nums[k];           // prefixSum
        int x = prefixSum - goal;       // find ith element in window [i,j]

        if(mp.find(x) != mp.end())              // if find prefixSum[i-1] --> add its frequency to final answer
            countOfArrays += mp[x];

        mp[prefixSum]++;                // Store current prefixSum for later use | Increment frequency of prefixSum

        // current element is equal to goal (it needs no interval to produce the sum, i.e. goal)
        if(prefixSum == goal)
            countOfArrays++;
    }

    return countOfArrays;
}
