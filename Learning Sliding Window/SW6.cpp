/*

Given a string you need to return the size of the longest possible substring that has exactly K unique characters.
If there is no possible substring then print -1.

eg.
Input:
S = "aabacbebebe", K = 3
Output: 7   --> "cbebebe"

Input:
S = "aaaa", K = 2
Output: -1

*/


int longestKSubstr(string s, int k)
{
    unordered_map<char, int> mp;            // <value, frequency>

    int i=0, j=0, length=-1, sum = 0, unique = 0, n = s.size();

    while(j < n)
    {
        mp[s[j]]++;
        sum++;

        if(mp[s[j]] == 1)
            unique++;

        if(unique == k)
        {
            length = max(length, sum);
            j++;
        }

        else if(unique < k)
            j++;

        else
        {
            while(unique > k)
            {
                mp[s[i]]--;
                sum--;

                if(mp[s[i]] == 0)
                    unique--;

                i++;
            }

            j++;
        }
    }

    return length;
}



// Logic is same. Just the space complexity is optimized. Always O(K)--> Map size never go beyond K+1


int longestKSubstr2(string s, int k)
{
    unordered_map<char, int> mp;            // <value, frequency>

    int i=0, j=0, length=-1, sum = 0, n = s.size();

    while(j < n)
    {
        mp[s[j]]++;
        sum++;

        if(mp.size() == k)
        {
            length = max(length, sum);
            j++;
        }

        else if(mp.size() < k)
        {
            j++;
        }

        else
        {
            while(mp.size() > k)
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
