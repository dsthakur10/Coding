/*

Given two strings s and t of lengths m and n respectively

Task is to return the MINIMUM WINDOW SUBSTRING of 's' such that every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

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
Explanation: Both 'a's from t must be included in the window. Since the largest window of s only has one 'a', return empty string.

*/


// search all the letters of 't' in 's' --> return minimum such substring of s
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


