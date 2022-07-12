/*


*/


vector<int> largestDivisibleSubset(vector<int>& nums) {

    int maxSubset = 0, maxIndex;
    int n = nums.size();
    int dp[n], path[n];

    sort(nums.begin(), nums.end());

    for(int i=0; i<n; i++)
    {
        dp[i] = 1;
        path[i] = i;
        for(int j=0; j<i; j++)
        {
            if(nums[i] % nums[j] == 0)
            {
                if(dp[i] < 1 + dp[j])
                {
                    dp[i] = 1 + dp[j];
                    path[i] = j;
                }
            }
        }

        if(maxSubset < dp[i])
        {
            maxSubset = dp[i];
            maxIndex = i;
        }
        // maxSubset = max(maxSubset, dp[i]);
    }

    vector<int> subset(maxSubset);

    int index = maxIndex, counter = maxSubset-1;
    while(path[index] != index)
    {
        subset[counter--] = nums[index];
        index = path[index];
    }

    subset[counter] = nums[index];

    return subset;
}
