/*

Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

Example 1:
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input: s = "aa", p = "*"
Output: true
Explanation: '*' matches any sequence.

Example 3:
Input: s = "cb", p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

Constraints:

0 <= s.length, p.length <= 2000
s contains only lowercase English letters.
p contains only lowercase English letters, '?' or '*'

*/


int dp[2001][2001];
bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    memset(dp, -1, sizeof(dp));
    return wildcard(s, p, m, n);
}

int wildcard(string s, string p, int m, int n)
{
    //if(dp[m][n] != -1)
   //     return dp[m][n];

    if(m == 0 && n == 0)
        return 1;

    if(n == 0)          // pattern exhausted
        return 0;

    if(dp[m][n] != -1)
        return dp[m][n];

    if(m == 0)
    {
        int i = 0;

        while(i < n && p[i] == '*')
        {
            dp[m][i+1] = 1;
            i++;
        }

        while(i < n)
            dp[m][i+1] = 0;

        return dp[m][n];
    }

    if(p[n-1] == '?' || s[m-1] == p[n-1])
        dp[m][n] = wildcard(s, p, m-1, n-1);

    else if(p[n-1] == '*')
        dp[m][n] = wildcard(s, p, m-1, n) || wildcard(s, p, m, n-1);

    else
        dp[m][n] = 0;

    return dp[m][n];
}


// BOTTOM-UP

bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    bool dp[m+1][n+1];

    dp[0][0] = true;

    for(int i=1; i<m+1; i++)
        dp[i][0] = false;

    int j = 1;
    while(j < n+1 && p[j-1] == '*')
    {
        dp[0][j] = true;
        j++;
    }

    while(j < n+1)
    {
        dp[0][j] = false;
        j++;
    }

    for(int i=1; i<m+1; i++)
    {
        for(int j=1; j<n+1; j++)
        {
            if(p[j-1] == '?' || p[j-1] == s[i-1])
                dp[i][j] = dp[i-1][j-1];

            else if(p[j-1] == '*')
                dp[i][j] = dp[i-1][j] || dp[i][j-1];

            else
                dp[i][j] = false;
        }
    }

    return dp[m][n];
}
