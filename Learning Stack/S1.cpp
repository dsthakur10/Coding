/*

Next GREATER to RIGHT

Given a circular integer array nums (i.e., the next element of nums[nums.length - 1] is nums[0]),
return the next greater number for every element in nums.

The next greater number of a number x is the first greater number to its traversing-order next in the array,
which means you could search circularly to find its next greater number. If it doesn't exist, return -1 for this number.

*/


vector<int> nextGreaterElements(vector<int>& nums)
{
    int n = nums.size();
    vector<int> result(n,-1);
    stack<int> st;

    st.push(0);
    for(int x=1; x<2*n; x++)
    {
        int i = x%n;
        while(!st.empty() && nums[st.top()] < nums[i])
        {
            result[st.top()] = nums[i];
            st.pop();
        }

        st.push(i);
    }

    return result;

}



vector<long long> nextLargerElementRight(vector<long long> arr, int n)
{
    vector<long long> result;
    stack<long long> st;

    for(int i=n-1; i>=0; i--)
    {
        if(st.empty())
            result.push_back(-1);

        else if(arr[i] < st.top())
            result.push_back(st.top());

        else if(arr[i] >= st.top())
        {
            while(!st.empty() && st.top() <= arr[i])
                st.pop();

            if(st.empty())
                result.push_back(-1);

            else
                result.push_back(st.top());
        }


        st.push(arr[i]);
    }

    reverse(result.begin(), result.end());
    return result;

}
