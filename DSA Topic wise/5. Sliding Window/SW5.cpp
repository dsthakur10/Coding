
//   "bbaaacbd" 3 --> fails here
int longestSubstring(string s, int k) {

    unordered_map<char, int> mp;
    unordered_set<char> curWindow;
    int maxLen = 0;
    int counter=0;

    int i=0, j=0;

    while(j < s.size())
    {
        curWindow.insert(s[j]);
        mp[s[j]]++;

        if(mp[s[j]] == k)
            counter++;

        if(curWindow.size() == counter)
            maxLen = max(j-i+1, maxLen);

        j++;
    }

    while(i < s.size())
    {
        mp[s[i]]--;

        if(mp[s[i]] == 0)
            curWindow.erase(s[i]);

        if(mp[s[i]] < k)
            counter--;

        if(curWindow.size() == counter)
            maxLen = max(j-1-i, maxLen);

        i++;
    }

    return maxLen;
}

