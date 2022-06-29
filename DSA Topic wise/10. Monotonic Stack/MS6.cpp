// Remove K Digits

/*

Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer
after removing k digits from num.

Example 1:
Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:
Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:
Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.


Constraints:
    1. 1 <= k <= num.length <= 105
    2. num consists of only digits.
    3. num does not have any leading zeros except for the zero itself.

*/


// Since we want smallest number possible after removing k-digits, we will use greedy approach here.
// Greedy approach --> Pop the greater element than upcoming from the current locality & DEC k
// Keep a track of smaller numbers in ascending order in stack.
// After all the numbers are visited, if (#digits to remove != k) --> need to remove top elements from stack
//      WHY ? --> Since we are already keeping track of numbers in INC order, numbers at top >= numbers below
// In the end you may encounter 0's in beginning & you need to remove them before returning final answer.
// Make sure to keep atleast one 0 in the string if string contains all 0's


string removeKdigits(string num, int k)
{
    stack<int> st;
    string str;

    for(int i=0; i<num.size(); i++)
    {
        // not equals to because top is still equal to current & might be required
        // 1112 with k=1

        while(!st.empty() && k > 0 && st.top() > num[i])
        {
            st.pop();
            k--;
        }

        st.push(num[i]);
    }

    // handles the case when some portion of string is in all ascending order and k > 0
    // --> You have to pop from stack as stack top > bottom elements --> Greedy is still satisfied here.

    while(k > 0)
    {
        st.pop();
        k--;
    }

    while(!st.empty())
    {
        str += st.top();
        st.pop();
    }

    if(str.empty())
        return "0";

    reverse(str.begin(), str.end());

    while(str.size() > 1 && str[0] == '0')      // removing 0's from beginning until string size becomes 1
        str.erase(str.begin());

    return str;
}
