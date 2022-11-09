/*

You are given an array of strings words. Each element of words consists of two lowercase English letters.

Create the longest possible palindrome by selecting some elements from words and concatenating them in any order.
Each element can be selected at most once.

Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome,
return 0.

A palindrome is a string that reads the same forward and backward.

Example 1:

Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.

Example 2:
Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.

Example 3:
Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".

*/


int longestPalindrome(vector<string>& words) {

    unordered_map<string, int> mp;
    int result = 0;
    bool flag = true;

    for(string str : words)
        mp[str]++;

    for(string str : words)
    {
        string rev = str;
        reverse(rev.begin(), rev.end());

        if(str[0] == str[1] && mp.find(str) != mp.end())
        {
            // case-1: multiple identical strings with repeated char
            if(mp[str] >= 2)
            {
                mp[str] -= 2;
                if(mp[str] == 0)
                    mp.erase(str);

                result += 4;
            }

            // case-2: string with repeated char
            else if(flag)
            {
                mp.erase(str);

                result += 2;
                flag = false;
            }
        }

        // case-3: match found
        else if(mp.find(str) != mp.end() && mp.find(rev) != mp.end())
        {
            mp[str]--;
            if(mp[str] == 0)
                mp.erase(str);

            mp[rev]--;
            if(mp[rev] == 0)
                mp.erase(rev);

            result += 4;
        }

        // case-4: No match found
        else if(mp.find(str) != mp.end())
        {
            mp[str]--;
            if(mp[str] == 0)
                mp.erase(str);
        }
    }

    return result;
}
