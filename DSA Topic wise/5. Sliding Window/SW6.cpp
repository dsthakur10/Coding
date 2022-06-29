
// Longest Repeating Character Replacement

/*

You are given a string s and an integer k. You can choose any character of the string and change it to any
other uppercase English character. You can perform this operation "at most k times".

Return the length of the longest substring containing the same letter you can get after performing the
above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.

*/


/*

We can make at most k changes to the string (any character can be replaced with any other character).
So, let's say there were no constraints like "k".

--> Given a string, convert it to a string with all same characters with minimal changes:

    "length of the entire string - #times maximum occurring character in the string"

--> Given this, we can apply the "at most k changes" constraint and maintain a sliding window such that:

    "(length of substring - #times maximum occurring character in the substring)" <= k

*/


// Maintain "curMax" character which is most frequently occurring character in current window.
// As & when you slide window, update this curMax


int characterReplacement(string s, int k)
{
    unordered_map<char, int> mp;
    int maxLen = 0;
    char curMax = 'A';
    int i=0, j=1;

    mp[s[0]]++;
    curMax = s[0];
    while(j < s.size())
    {
        mp[s[j]]++;

        // update current Max
        if(mp[s[j]] > mp[curMax])
            curMax = s[j];

        if(j-i+1 - mp[curMax] <= k)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            while(j-i+1 - mp[curMax] > k)
            {
                mp[s[i]]--;

                // find new curMax
                if(curMax == s[i])
                    curMax = findCurrentMax(mp, s[i]);

                i++;
            }

            j++;
        }
    }

    return maxLen;
}


char findCurrentMax(unordered_map<char, int>& mp, char ch)
{
    char curMax = ch;

    for(auto it = mp.begin(); it != mp.end(); it++)
    {
        if(it->second > mp[curMax])
            curMax = it->first;
    }

    return curMax;
}



// Without an extra while loop to find curMax --> no need
// When the sliding window shrinks, the counts array won't get larger.
// So basically curMax never be updated in this loop

int characterReplacement(string s, int k) {

    unordered_map<char, int> mp;
    int sum = 0, maxLen = 0;
    char curMax = 'A';
    int i=0, j=1;

    mp[s[0]]++;
    curMax = s[0];
    while(j < s.size())
    {
        mp[s[j]]++;

        if(mp[s[j]] > mp[curMax])
            curMax = s[j];

        if(j-i+1 - mp[curMax] <= k)
        {
            maxLen = max(maxLen, j-i+1);
            j++;
        }

        else
        {
            if(j-i+1 - mp[curMax] > k)
            {
                mp[s[i]]--;

                // if(curMax == s[i])
                //     curMax = findCurrentMax(mp, s[i]);
                // // find new curMax

                i++;
            }

            j++;
        }
    }

    return maxLen;
}
