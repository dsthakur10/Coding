/*

Given a string s, find the length of the longest substring without repeating characters

Input: s = "abcabcbb"
Output: 3

Input: s = "bbbbb"
Output: 1

Input: s = "pwwkew"
Output: 3

*/


int lengthOfLongestSubstring(string s)
{
    unordered_set<char> myset;

    int i=0, j=0, n=s.size(), sum = 0, count = 0;

    while(j < n)
    {
        auto p = myset.insert(s[j]);

        if(p.second)
        {
            sum++;
            count = max(count, sum);
            j++;
        }

        else
        {
            while(myset.insert(s[j]).second == false)
            {
                myset.erase(s[i]);
                i++;
                sum--;
            }

            sum++;
            j++;
        }
    }

    return count;
}




int lengthOfLongestSubstring2(string s)
{
    unordered_map<char, int> mp;            // <value, frequency>

    int i=0, j=0, length=0, sum = 0, n = s.size();

    while(j < n)
    {
        mp[s[j]]++;
        sum++;

        if(mp.size() == j-i+1)
        {
            length = max(length, sum);
            j++;
        }

//         else if(mp.size() > j-i+1)
//         {
//             j++;
//         }

        else if(mp.size() < j-i+1)               // map has
        {
            while(mp.size() < j-i+1)
            {
                mp[s[i]]--;
                sum--;

                if(mp[s[i]] == 0)
                    mp.erase(s[i]);

                i++;
            }

            j++;
        }
    }

    return length;
}
