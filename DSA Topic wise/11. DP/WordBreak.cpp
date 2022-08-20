/*

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated
sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:
Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 2:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

*/


// TOP-DOWN

int dp[301];

bool wordBreak(string s, vector<string>& wordDict) {

    memset(dp, -1, sizeof(dp));
    unordered_set<string> set(wordDict.begin(), wordDict.end());
    int n = s.size();

    return solve(set, s, 0);
}


int solve(unordered_set<string>& set, string s, int start)
{
    if(start >= s.size())
        return 1;

    if(start == s.size()-1 && set.find(s) != set.end())
        return dp[start] = 1;

    if(dp[start] != -1)
        return dp[start];

    int temp;

    for(int k = start+1; k<=s.size(); k++)
    {
        string left = s.substr(start, k-start);

        if(set.find(left) != set.end())
            temp = solve(set, s, k);

        else
            temp = 0;

        if(temp)
            return dp[start] = 1;
    }

    return dp[start] = 0;
}



// BOTTOM-UP

bool wordBreak(string s, vector<string>& wordDict) {

    unordered_set<string> set(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n+1, false);

    dp[n] = true;
    bool temp;
    for(int i=n-1; i>=0; i--)
    {
        for(int j = i+1; j <= s.size(); j++)
        {
            string left = s.substr(i, j-i);

            if(set.find(left) != set.end())
                temp = dp[j];

            else
                temp = false;

            if(temp)
            {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[0];
}
