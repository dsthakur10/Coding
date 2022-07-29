
/*



*/


// TLE

unordered_map<string, vector<string>> mp;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    queue<string> q;

    q.push(beginWord);
    int level = 0;
    while(!q.empty())
    {
        int n = q.size();
        level++;
        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;
            cout << "\ncurrunt = " << cur;

            if(cur == endWord)
                return level;

            if(mp.find(cur) != mp.end())
                continue;

            findNeighbor(cur, wordList);

            for(string str : mp[cur])
            {
                //cout << str << "\n";
                if(mp.find(str) == mp.end())
                    q.push(str);
            }
        }
    }

    return 0;
}

void findNeighbor(string str, vector<string>& wordList)
{
    for(int i=0 ; i<wordList.size(); i++)
    {
        if(wordList[i] == str)
            continue;

        int n = str.size();
        int count = 0;

        for(int j=0; j<n; j++)
        {
            if(wordList[i][j] != str[j])
                count++;
        }

        if(count == 1)
            mp[str].push_back(wordList[i]);
    }
}



// Method-2 --> Using HashSet to keep track of visited nodes to avoid unnecessary calculations

unordered_map<string, vector<string>> mp;

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    unordered_set<string> us(wordList.begin(), wordList.end());
    queue<string> q;

    if(us.find(endWord) == us.end())
        return 0;

    q.push(beginWord);
    int level = 0;
    while(!q.empty())
    {
        int n = q.size();
        level++;
        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;
            us.erase(cur);

            cout << "\ncurrunt = " << cur;

            if(cur == endWord)
                return level;

            if(mp.find(cur) != mp.end())
                continue;

            findNeighbor(cur, us);

            for(string str : mp[cur])
            {
                //cout << str << "\n";
                if(mp.find(str) == mp.end())
                    q.push(str);
            }
        }
    }

    return 0;
}

void findNeighbor(string str, unordered_set<string>& us)
{
    for(auto it = us.begin() ; it != us.end(); it++)
    {
        string sit = *it;
        if(sit == str)
            continue;

        int n = str.size();
        int count = 0;

        for(int j=0; j<n; j++)
        {
            if(sit[j] != str[j])
                count++;
        }

        if(count == 1)
            mp[str].push_back(sit);
    }
}



// Method-3 --> replacing each character of each word in queue --> O(260)


int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    unordered_set<string> us(wordList.begin(), wordList.end());
    queue<string> q;

    if(us.find(endWord) == us.end())
        return 0;

    q.push(beginWord);
    int level = 0;
    while(!q.empty())
    {
        int n = q.size();
        level++;
        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;
            us.erase(cur);

            if(cur == endWord)
                return level;

            for(int i=0; i<cur.size(); i++)
            {
                char x = cur[i];
                for(char ch = 'a'; ch <= 'z'; ch++)
                {
                    cur[i] = ch;

                    if(us.find(cur) != us.end())
                        q.push(cur);
                }
                cur[i] = x;
            }
        }
    }

    return 0;
}
