
/*

Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
x
A circular array means the end of the array connects to the beginning of the array. Formally, the next element of
nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].

A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i],
nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.

*/



// Method-1 --> Kadanes + prefix & Suffix sum for interval subarray

/*


*/


int maxSubarraySumCircular(vector<int>& nums) {

    int n = nums.size();
    int prefix[n], suffix[n];

    suffix[n-1] = nums[n-1];
    int sum1 = nums[n-1];
    for(int i=n-2; i>=0; i--)
    {
        sum1 += nums[i];
        suffix[i] = max(sum1, suffix[i+1]);
    }

    int maxSum = INT_MIN;
    int sum2 = 0;
    for(int i=0; i<n-2; i++)
    {
        sum2 += nums[i];
        maxSum = max(maxSum, sum2 + suffix[i+2]);
    }

    maxSum = max(maxSum, kadanes(nums));

    return maxSum;
}

int kadanes(vector<int>& nums)
{
    int n = nums.size();
    int sum = 0, maxSum = nums[0];

    sum = (nums[0] < 0) ? 0 : nums[0];
    for(int i=1; i<n; i++)
    {
        sum += nums[i];
        maxSum = max(maxSum, sum);

        if(sum < 0)
            sum = 0;
    }

    return maxSum;
}



// Method-2 --> Concatenation of array + monotonic queue

int maxSubarraySumCircular(vector<int>& nums) {

    int n = nums.size();
    int sum = 0, maxSum;
    vector<int> prefix = prefixSum(nums);
    deque<int> dq;

    int j=1;
    maxSum = nums[0];
    dq.push_back(0);

    // want largest P[j] - P[i]  &&  1 <= j-i <= N
    // For each j, want smallest P[i]  &&  j-N <= i

    // Use INC monotonic queue to push indices for prefix Sums from smallest to largest
    while(j < 2*n)
    {
        if(dq.front() < j-n)
            dq.pop_front();

        maxSum = max(maxSum, prefix[j] - prefix[dq.front()]);

        while(!dq.empty() && prefix[j] <= prefix[dq.back()])
            dq.pop_back();

        dq.push_back(j);
        j++;
    }

    return maxSum;
}

vector<int> prefixSum(vector<int>& nums)
{
    int n = nums.size();
    vector<int> prefix(2*n);

    prefix[0] = nums[0];
    for(int i=1; i<2*n; i++)
        prefix[i] = prefix[i-1] + nums[i%n];

    return prefix;
}
