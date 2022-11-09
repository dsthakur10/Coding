
/*

A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words
beginWord -> s1 -> s2 -> ... -> sk such that:

    --> Every adjacent pair of words differs by a single letter.
    --> Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
        sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the
shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.


Example 1:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog",
which is 5 words long.

Example 2:
Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.


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

vector<string> findNeighbors(unordered_set<string>& us, string word)
{
    vector<string> lookalike;

    for(int i=0; i<word.size(); i++)
    {
        char old = word[i];
        for(char ch = 'a'; ch <= 'z'; ch++)
        {
            if(ch != old)
            {
                word[i] = ch;
                if(us.find(word) != us.end())
                {
                    lookalike.push_back(word);
                    us.erase(word);
                    // delete the word from HashSet to avoid unnecessary check & since every word has to appear
                    // only once in the BFS search.
                }
            }
        }
        word[i] = old;
    }

    return lookalike;
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    unordered_map<string, vector<string>> mp;
    unordered_set<string> us(wordList.begin(), wordList.end());
    queue<string> q;
    int level = 0;

    if(us.find(endWord) == us.end())
        return 0;

    q.push(beginWord);
    while(!q.empty())
    {
        level++;
        int n = q.size();

        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;

            if(cur == endWord)
                return level;

            // No need for this since any word will appear only once as we have deleted that word from HashSet
            // once it appeared to be neighbor of some node.

//                 if(mp.find(cur) != mp.end())
//                     continue;

            mp[cur] = findNeighbors(us, cur);

            for(string str : mp[cur])
                q.push(str);
        }
    }

    return 0;
}



// Method-4 --> Without using HashMap --> Only HashSet is enough --> Directly insert neighbors of current node in
// queue without storing them in HashMap.


void findNeighbors(queue<string>& q, unordered_set<string>& us, string word)
{
    for(int i=0; i<word.size(); i++)
    {
        char old = word[i];
        for(char ch = 'a'; ch <= 'z'; ch++)
        {
            if(ch != old)
            {
                word[i] = ch;
                if(us.find(word) != us.end())
                {
                    q.push(word);
                    us.erase(word);                 // once the word appears in the map, it won't be repeated.
                }
            }
        }
        word[i] = old;
    }
}

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {

    unordered_set<string> us(wordList.begin(), wordList.end());
    queue<string> q;
    int level = 0;

    if(us.find(endWord) == us.end())
        return 0;

    q.push(beginWord);
    while(!q.empty())
    {
        level++;
        int n = q.size();

        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;

            if(cur == endWord)
                return level;

            findNeighbors(q, us, cur);
        }
    }

    return 0;
}
