/*

Given an integer array arr, partition the array into (contiguous) subarrays of length at most k.
After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.
Test cases are generated so that the answer fits in a 32-bit integer.

Example 1:
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]

Example 2:
Input: arr = [1,4,1,5,7,3,6,1,9,9,3], k = 4
Output: 83

Example 3:
Input: arr = [1], k = 1
Output: 1

*/


// Method-1 --> FRONT-PARTITION method --> Time = O(k*n^2) --> #subproblems = n | time/subproblem = O(k*n)

/*

Try out every partition possible starting from beginning.
Now, dp[i] --> maximum sum obtained starting from ith index till the end of array.
Our task is to find dp[0]

Now, we will draw a partition keeping in mind that maximum subarray size allowed is k. We won't move beyond index+k

Helper function is used to find maximum element in given subarray.

*/

int dp[501];
int maxSumAfterPartitioning(vector<int>& arr, int k) {

    int n = arr.size();
    memset(dp, -1, sizeof(dp));
    return solve(arr, k, 0);
}


int solve(vector<int>& arr, int k, int index)
{
    int n = arr.size();

    if(index > n-1)         // reached end of array
        return 0;

    if(dp[index] != -1)
        return dp[index];

    // partition starts from "index + 1" & goes until "k + index"
    for(int i=index; i<n && i<k+index; i++)
    {
        int maxNumber = findMaximum(arr, index, i);         // finds maximum in given range of subarray
        int sum = maxNumber*(i-index+1);

        dp[index] = max(dp[index], sum + solve(arr,k,i+1));     // trying out every possible partition
    }

    cout << "index = " << index << " sum = " << dp[index] << "\n";
    return dp[index];
}


int findMaximum(vector<int>& arr, int start, int end)
{
    int maximum = 0;

    for(int i=start; i<=end; i++)
        maximum = max(maximum, arr[i]);

    return maximum;
}



// Method-2 --> O(k*n) | #subproblems = n | time/subproblem = O(k)
// We don't need a helper function to find maximum in current subarray

int dp[501];
int maxSumAfterPartitioning(vector<int>& arr, int k) {

    int n = arr.size();
    memset(dp, -1, sizeof(dp));
    return solve(arr, k, 0);
}


int solve(vector<int>& arr, int k, int index)
{
    int n = arr.size();

    if(index > n-1)         // reached end of array
        return 0;

    if(dp[index] != -1)
        return dp[index];

    // partition starts from "index + 1" & goes until "k + index"

    int maxNumber = 0;
    for(int i=index; i<n && i<k+index; i++)
    {
        maxNumber = max(maxNumber, arr[i]);             // finds maximum in given range of subarray
        int sum = maxNumber*(i-index+1);

        dp[index] = max(dp[index], sum + solve(arr,k,i+1));     // trying out every possible partition
    }

    cout << "index = " << index << " sum = " << dp[index] << "\n";
    return dp[index];
}



// BOTTOM-UP

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    int dp[n+1];

    dp[n] = 0;
    for(int i=n-1; i>=0; i--)
    {
        int ans = 0;
        int maxNumber = 0;
        for(int j=i; j<i+k && j<n; j++)
        {
            maxNumber = max(maxNumber, arr[j]);
            int sum = maxNumber*(j-i+1);

            ans = max(ans, sum + dp[j+1]);
        }

        dp[i] = ans;
    }

    return dp[0];
}
