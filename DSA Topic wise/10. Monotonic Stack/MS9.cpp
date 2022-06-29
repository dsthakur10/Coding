// Sum of Subarray Minimums

/*

Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr.
Since the answer may be large, return the answer modulo 10^9 + 7.


Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation:
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.

Example 2:
Input: arr = [11,81,94,43,3]
Output: 444

*/



// Method-1 --> Sorting

// Find 1st index where copy[i] < nums[i] --> starting of unsorted array
// Find last index where copy[i] > nums[i] --> ending of unsorted array

int findUnsortedSubarray(vector<int>& nums)
{
    int n = nums.size();
    int start = 0, end = -1;

    vector<int> copy = nums;
    sort(copy.begin(), copy.end());

    int minn = nums[0], maxx = nums[n-1];
    for(int i=0; i<n; i++)
    {
        if(copy[i] < nums[i])
        {
            start = i;
            break;
        }
    }

    for(int i=n-1; i>=0; i--)
    {
        if(copy[i] > nums[i])
        {
            end = i;
            break;
        }
    }

    return end - start + 1;
}



// Method-2 --> Stack

int findUnsortedSubarray(vector<int>& nums)
{
    int n = nums.size();
    stack<int> st;
    int start = n-1, end = 0;

    for(int i=0; i<n; i++)
    {
        while(!st.empty() && nums[st.top()] > nums[i])
        {
            start = min(st.top(), start);
            st.pop();
        }

        st.push(i);
    }


    // Empty stack for new operation
    while(!st.empty())
        st.pop();


    for(int i=n-1; i>=0; i--)
    {
        while(!st.empty() && nums[st.top()] < nums[i])
        {
            end = max(st.top(), end);
            st.pop();
        }

        st.push(i);
    }

    if(start == n-1)
        return 0;

    return end - start + 1;
}



// Method-3 --> 2-pointers

// Find 1st & last inversion in array
// Our task is to find smallest & largest index NOT IN correct place
// Smallest index NOT in place --> 1st number which is in unsorted order
// Largest index NOT in place --> Last number which is in unsorted order
// Traverse from end --> begin to get 1st index not in place
// Traverse from begin --> end to get last index not in place

int findUnsortedSubarray(vector<int>& nums)
{
    int n = nums.size();
    int start = 0, end = -1;                    // if array is sorted --> (-1) - 0 + 1 = 0
    int minn = nums[n-1], maxx = nums[0];

    // find smallest index having inversion
    for(int i=n-2; i>=0; i--)
    {
        if(nums[i] > minn)
            start = i;

        else
            minn = nums[i];
    }

    // find largest index having inversion
    for(int i=1; i<=n-1; i++)
    {
        if(nums[i] < maxx)
            end = i;

        else
            maxx = nums[i];
    }

    return end - start + 1;
}
