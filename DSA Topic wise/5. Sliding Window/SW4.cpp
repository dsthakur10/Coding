
// Minimum Window Substring

/*

Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that
every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

*/


// Method-1 --> HashMap

/*
    1. Use two pointers: start and end to represent a window.
    2. Move end to find a valid window.
    3. When a valid window is found, move start to find a smaller window.

To c heck if a window is valid, we use a map to store (char, count) for chars in t.
And use counter for the unique number of chars of t.
The key part is m[s[j]]--
--> We decrease count for each char in 's', if it belongs to 't'. If count = 0 --> decrement counter

When counter drops to 0 --> valid window is found (containing all characters from 't')
Now our task is to minimize the found window.

Keep removing unnecessary chars in the beginning until the substring becomes invalid candidate for our answer.

*/

// search all the letters of 't' in 's' --> return minimum such substring of s
string minWindow(string s, string t) {

    int m = s.size(), n = t.size();

    if(m < n)
        return "";

    unordered_map<char, int> mp;
    string str;
    int i=0, j=0, minLen = INT_MAX, start = -1;
    int counter, strLen = 0;

    for( char &x : t)
        mp[x]++;
    counter = mp.size();

    while(j < m)
    {
        if(mp.find(s[j]) != mp.end())
        {
            mp[s[j]]--;

            if(mp[s[j]] == 0)
                counter--;
        }

        strLen++;
        //str.push_back(s[j]);

        if(counter == 0)
        {
            while(i < m && counter == 0)
            {
                if(strLen < minLen)
                {
                    start = i;
                    minLen = strLen;
                }
                //minLen = min(minLen, strLen);

                if(mp.find(s[i]) != mp.end())
                {
                    mp[s[i]]++;

                    if(mp[s[i]] == 1)
                        counter++;
                }

                //str.erase(str.begin());
                strLen--;
                i++;
            }
        }

        j++;
    }

    if(start == -1)
        return "";
    cout << "minLen = " << minLen;

    str = s.substr(start, minLen);
    return str;
}



// Method-2 --> Vector instead of HashMap

string minWindow(string s, string t) {

    int m = s.size(), n = t.size();

    if(m < n)
        return "";

    vector<int> letters(128, 0);
    string str;

    int i=0, j=0, minLen = INT_MAX, start = -1;
    int counter, strLen = 0;

    for( char &x : t)
        letters[x]++;

    counter = n;

    while(j < m)
    {
        letters[s[j]]--;

        if(letters[s[j]] >= 0)
            counter--;

        strLen++;

        if(counter == 0)
        {
            while(i < m && counter == 0)
            {
                if(strLen < minLen)
                {
                    start = i;
                    minLen = strLen;
                }

                letters[s[i]]++;
                if(letters[s[i]] > 0)
                    counter++;

                strLen--;
                i++;
            }
        }

        j++;
    }

    if(start == -1)
        return "";
    cout << "minLen = " << minLen;

    str = s.substr(start, minLen);
    return str;
}
