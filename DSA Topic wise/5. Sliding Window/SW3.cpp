
// Longest Substring Without Repeating Characters

/*

Given a string s, find the length of the longest substring without repeating characters.
    --> Substring must have ALL unique characters

Example 1:
Input: s = "abcabcbb"
Output: 3

Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1

Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.

Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

*/



// Method-1 --> HashMap
// This problem is very similar to longest substring with "k-unique chars", instead of k, here we have to keep
// all unique chars in substring.
// We do not have a given parameter to compare. So we will directly use window size to compare with.
// HashMap-size is being compared with current window size. We get 2 possibilities here:
    // 1. map size == current window --> perform calculation & increment j
    // 2. map size < current window --> repetitions found in current window. Remove ith index element from map


int lengthOfLongestSubstring(string s) {

    unordered_map<char, int> mp;

    int n = s.size(), maxLen = 0;
    int i=0, j=0;

    while(j < n)
    {
        mp[s[j]]++;

        if(mp.size() == j-i+1)
        {
            // calculate
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else if(mp.size() < j-i+1)
        {
            while(mp.size() < j-i+1)
            {
                mp[s[i]]--;

                if(mp[s[i]] == 0)
                    mp.erase(s[i]);

                i++;
            }

            j++;
        }
    }

    return maxLen;
}


// Method-2 --> unordered_set

int lengthOfLongestSubstring(string s)
{
    unordered_set<char> us;

    int n = s.size(), maxLen = 0;
    int i=0, j=0;

    while(j < n)
    {
        auto p = us.insert(s[j]);

        if(p.second)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            while(!us.insert(s[j]).second)
            {
                us.erase(s[i]);
                i++;
            }
            j++;
        }

    }

    return maxLen;
}
