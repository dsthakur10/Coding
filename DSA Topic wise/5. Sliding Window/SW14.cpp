// Get Equal Substrings Within Budget

/*
You are given two strings s and t of the same length and an integer maxCost.

You want to change s --> t. Changing the ith character of s to ith character of t costs |s[i] - t[i]|
(i.e., the absolute difference between the ASCII values of the characters).

Return the maximum length of a substring of s that can be changed to be the same as the corresponding substring
of t with a cost less than or equal to maxCost. If there is no substring from s that can be changed to its
corresponding substring from t, return 0.

Example 1:
Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3
Explanation: "abc" of s can change to "bcd". That costs 3, so the maximum length is 3.

Example 2:
Input: s = "abcd", t = "cdef", maxCost = 3
Output: 1
Explanation: Each character in s costs 2 to change to character in t,  so the maximum length is 1.

Example 3:
Input: s = "abcd", t = "acde", maxCost = 0
Output: 1
Explanation: You cannot make any change, so the maximum length is 1.

*/


// Method-1 --> Reduce problem to --> "Maximum sum subarray with sum <= k"

// Since we need to find the maximum substring that can be replaced we can actually breakdown this problem
// to an array of integers that represent the replacement cost of s[i] --> t[i] and then find the maximum length
// of continuous integers in that array whose sum <= maxCost

int equalSubstring(string s, string t, int maxCost) {

    int n = s.size();
    int sum = 0, maxLen = 0;
    int i=0, j=0;

    while(j < n)
    {
        sum += abs(s[j] - t[j]);    // cost = s[i] - t[i] --> We have to get maximum subarray with sum <= maxCost

        if(sum <= maxCost)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            while(sum > maxCost)
            {
                sum -= abs(s[i] - t[i]);
                i++;
            }
            j++;
        }
    }

    return maxLen;
}
