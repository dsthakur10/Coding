
// Method-1 --> 1 traversal of string --> HashMap

char nonrepeatingCharacter(string S)
{
    unordered_map<char, pair<int, int>> mp;
    char unique;

    for(int i=0; i<S.size(); i++)
    {
        int count = 1;
        if(mp.find(S[i]) != mp.end())
            count = mp[S[i]].first + 1;

        mp[S[i]] = {count, i};
    }

    int i = INT_MAX;
    for(auto it : mp)
    {
        int count = it.second.first;
        int index = it.second.second;

        if(count == 1 && i > index)
            i = index;
    }

    if(i == INT_MAX)
        return '$';

    return S[i];
}


// Method-2 --> character array of size 256

char nonrepeatingCharacter(string S)
{
    vector<pair<int, int>> characterArray(256, {0,0});

    for(int i=0; i<S.size(); i++)
    {
        int count = characterArray[S[i]].first + 1;
        characterArray[S[i]] = {count, i};
    }

    int x = INT_MAX;
    for(int i=0; i<256; i++)
    {
        int count = characterArray[S[i]].first;
        int index = characterArray[S[i]].second;

        if(count == 1 && x > index)
            x = index;
    }

    if(x == INT_MAX)
        return '$';

    return S[x];
}
