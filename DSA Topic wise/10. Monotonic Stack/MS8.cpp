// Shortest Unsorted Continuous Subarray

/*
Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in
ascending order, then the whole array will be sorted in ascending order.

Return the shortest such subarray and output its length.

Example 1:
Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.

Example 2:
Input: nums = [1,2,3,4]
Output: 0
Example 3:

Input: nums = [1]
Output: 0

*/


// Method-1 --> sorting





// Method-2 --> stack


// Incorrect method
int findUnsortedSubarray(vector<int>& nums) {
    int n = nums.size();
    stack<int> st;

    int start = -1, end = -1;
    for(int i=0; i<n; i++)
    {
        while(!st.empty() && nums[st.top()] > nums[i])
        {
            if(start == -1)
                start = st.top();

            end = i;
            st.pop();
        }

        st.push(i);
    }

    cout << start << " " << end;
    if(start == -1)
        return 0;

    return end - start + 1;
}


