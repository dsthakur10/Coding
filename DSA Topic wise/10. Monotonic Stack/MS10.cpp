
// Minimum Cost Tree From Leaf Values

/*

Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children --> FULL BINARY TREE
The values of array correspond to the "values of each leaf" in an in-order traversal of the tree.
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. 4
It is guaranteed this sum fits into a 32-bit integer.

A node is a leaf if and only if it has zero children.
Example 1:
Input: arr = [6,2,4]
Output: 32
Explanation: There are two possible trees shown.
The first has a non-leaf node sum 36, and the second has non-leaf node sum 32.

Example 2:
Input: arr = [4,11]
Output: 44

Constraints:
2 <= arr.length <= 40

*/


// Method-1 --> Greedy approach --> O(n^2) time | O(1) space

/*
In the final tree, value of non-leaf nodes are from maximum leaf values from left and right subtrees.
If in the final tree, the maximum value from the array is at deepest level of the tree,
its value will be used multiple times for multiple parent nodes, which is obviously not ideal.

So the finding here is we should place the smallest value from array at deepest level.
Smallest value here means the product of pair arr[i] and arr[i + 1] where the product is smallest.

What happens to the pair after that? The smaller of the pair will never be used again and we can simply discard it.

Find the index i so that arr[i] * arr[i + 1] is the smallest (arr[i] * arr[i + 1] is added to the result)
and discard the less of the pair. Keep doing so until array size is 1.

// NOTE: Selecting values must be in the inorder of arr given & not just randomly 2 elements whose product is minimum

*/


int mctFromLeafValues(vector<int>& arr)
{
    int n = arr.size();
    int result = 0;

    // arr size dynamically changes as we remove element from vector in each iteration
    while(arr.size() != 1)
    {
        int x, y, n=arr.size();
        long minimum = LONG_MAX;

        // Selecting optimal value of new product --> selecting optimal nodes
        for(int i=0; i<n-1; i++)
        {
            long temp = (long)arr[i]*arr[i+1];

            if(minimum > temp)
            {
                x = i;
                y = i+1;
                minimum = temp;
            }
        }

        // removing the smaller of 2 nodes as it won't be of any use in future
        // We pass maximum value of the pair higher up the order.

        int minToRemove = min(arr[x],arr[y]) == arr[x] ? x : y;
        arr.erase(arr.begin() + minToRemove);

        result += minimum;          // add the product in each step
    }

    return result;
}



// Method-2 --> Stack --> O(n) time | O(n) space

/*
Different Greedy approach --> select the minimum element from present array & find the min( arr[i-1], arr[i+1] )
Add this product to result --> result += minimum * min(arr[i-1], arr[i+1])

Find the smallest value in the array, use it and its smaller neighbor to build a non-leaf node, then we can
safely delete it from the array since it has a smaller value than its neighbor so it will never be used again.

In greedy approach, everytime we delete current minimum, we need to start all over again & find next smallest.
Thus repeated work is being done.

Observation --> Each iteration involves actually removing a "local minimum" value
    --> arr[i-1], arr[i], arr[i+1] --> arr[i-1] >= arr[i] <= arr[i+1]
    1. Remove ith element as it is current minimum & since its neighbors are greater than it, it will never be used
    2. product = arr[i] * min( arr[i-1], arr[i+1] )

Monotonic DEC stack can be used for this --> Pop the top element as soon as you find top <= current
    --> top is arr[i], element below top is arr[i-1], current is arr[i+1]

After repeating this until all the elements are traversed, we have used all the local minima

Stack still contains elements which are just internal nodes or leaf without local minima, stored in DECREASING order
Top 2 elements of stack can be multiplied & top will be removed as it is naturally smaller than its below element
Perform this until stack size = 1

*/

int mctFromLeafValues(vector<int>& arr)
{
    int n = arr.size(), result = 0;
    stack<int> st;

    // 1st pass will cover all the local minima
    for(int i=0; i<n; i++)
    {
        while(!st.empty() && st.top() <= arr[i])
        {
            int mid = st.top();
            st.pop();

            if(st.empty())                              // boundary condition --> What if arr[i] is just 2nd element
                result += mid * arr[i];

            else
                result += mid * min(st.top(), arr[i]);
        }

        st.push(arr[i]);
    }

    // 2nd pass will cover what is left from 1st pass (WITHOUT local minima)
    while(st.size() > 1)
    {
        int x = st.top();
        st.pop();
        int y = st.top();

        result += x*y;
    }

    return result;
}
