// Next Greater Element II

/*

Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
return the next greater number for every element in nums.

The next greater number of a number x is the first greater number to its traversing-order next in the array,
which means you could search circularly to find its next greater number.
If it doesn't exist, return -1 for this number.

Example 1:
Input: nums = [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; The number 2 can't find next greater number.
The second 1's next greater number needs to search circularly, which is also 2.

Example 2:
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]

*/


vector<int> nextGreaterElements(vector<int>& nums) {

    int n = nums.size();
    vector<int> result(n, INT_MIN);
    stack<int> st;

    // traverse from end & store numbers in stack in MONOTONICALLY increasing order
    for(int i=n-1; i>=0; i--)
    {
        while(!st.empty() && nums[i] >= st.top())   // = deals with duplicate elements
            st.pop();

        if(!st.empty())
            result[i] = st.top();

        st.push(nums[i]);
    }


    for(int i=n-1; i>=0; i--)
    {
        while(!st.empty() && nums[i] >= st.top())
            st.pop();

        if(st.empty())
            break;

        //if(result[i] == -1)
        if(result[i] == INT_MIN)
            result[i] = st.top();
    }

    for(int i=0; i<result.size(); i++)
    {
        if(result[i] == INT_MIN)
            result[i] = -1;
    }
    return result;
}



// Method-2 --> Using Modulo

vector<int> nextGreaterElements(vector<int>& nums) {

    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;

    // traverse from end & store numbers in stack in MONOTONICALLY increasing order
    int N = 2*n-1;
    for(int i=N-1; i>=0; i--)
    {
        while(!st.empty() && nums[i%n] >= st.top())
            st.pop();

        if(!st.empty())
            result[i%n] = st.top();

        st.push(nums[i%n]);
    }

    return result;
}
