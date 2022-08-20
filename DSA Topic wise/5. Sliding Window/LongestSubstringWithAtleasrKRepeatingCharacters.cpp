int longestSubstring(string s, int k) {

    int n = s.size();
    int maxUnique = 0, maxLen = 0;
    unordered_map<char, int> mp;
    unordered_set<char> set;

    for(char ch: s)
        set.insert(ch);

    maxUnique = (int)set.size();

    // curUnique signify #unique characters you must keep in given window(substring) for possible candidate answer
    // now check if window contains #curUnique chars for atleast k times

    for(int curUnique=1; curUnique<=maxUnique; curUnique++)
    {
        int i=0, j=0;
        int unique = 0, atleastK = 0, len = 0;
        mp.clear();

        // find the maximum length of any window with #unique characters = curUnique
        // atleastK --> keeps count of unique chars that have reached value >= k
        // unique --> keeps track of unique characters in current window
        while(j < n)
        {
            if(mp.find(s[j]) == mp.end())
                unique++;

            mp[s[j]]++;

            if(mp[s[j]] == k)
                atleastK++;

            if(unique <= curUnique)
                j++;

            else
            {
                while(unique > curUnique)
                {
                    if(mp[s[i]] == k)
                        atleastK--;

                    mp[s[i]]--;

                    if(mp[s[i]] == 0)
                    {
                        unique--;
                        mp.erase(s[i]);
                    }

                    i++;
                }
                j++;
            }

            if(unique == curUnique && atleastK == curUnique)
                len = max(len, j-i);
        }

        maxLen = max(maxLen, len);
    }

    return maxLen;
}
