
/*

Given an input string s and a pattern p, implement regular expression matching with support for '.' and '*' where:

'.' Matches any single character.​​​​
'*' Matches zero or more of the preceding element.
The matching should cover the entire input string (not partial).

Example 1:
Input: s = "aa", p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

Example 2:
Input: s = "aa", p = "a*"
Output: true
Explanation: '*' means zero or more of the preceding element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

Example 3:
Input: s = "ab", p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

*/



// LOGIC :

/*

4 cases to look for:
    1. s[m-1] == p[n-1]     --> match found | dp[m][n] = dp[m-1][n-1]

    2. p[n-1] == '.'        --> dp[m][n] = dp[m-1][n-1]

    3. p[n-1] == '*'
        --> need to check next upcoming character before deciding anything.

        a. p[n-2] == '.' --> dp[m][n] = dp[m-1][n] || dp[m][n-1] || dp[m][n-2]
            --> treat '.*' as multiple or 1 or 0 occurrences of '.'

        b. p[n-2] == s[m-1] --> dp[m][n] = dp[m-1][n] || dp[m][n-1] || dp[m][n-2]
            --> treat 'x*' as multiple or 1 or 0 occurrences of 'x'

        c. p[n-2] != s[m-1] --> dp[m][n] = dp[m][n-2]
            --> avoid it (consider as 0 occurrence)

    4. s[m-1] != p[n-1]     --> dp[m][n] = 0


Special care to be taken for base cases:

    1. Both string & pattern are empty --> dp[0][0] = 1

    2. Pattern is empty --> dp[i][0] = 0

    3. String is empty
        a. p[j-1] = '*' --> dp[0][j] = dp[0][j-2]       --> Ignore x*
        b. p[j-1] =  character --> dp[0][j] = 0

*/

// TOP-DOWN

int dp[31][31];
bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    memset(dp, -1, sizeof(dp));
    return wildcard(s, p, m, n);
}


int wildcard(string& s, string& p, int m, int n)
{
    if(dp[m][n] != -1)
       return dp[m][n];

    if(m == 0 && n == 0)
        return 1;

    if(n == 0)          // pattern exhausted
        return 0;

    if(m == 0)          // string exhausted
    {
        if(p[n-1] == '*')                       // avoid patterns like a* or .* (treat as 0 occurrence)
            dp[m][n] = wildcard(s, p, m, n-2);

        else                                    // letter or '.' encountered without * embedded
            dp[m][n] = 0;

        return dp[m][n];
    }

                                                    // match found --> check on next character
    if(p[n-1] == '.' || s[m-1] == p[n-1])
        dp[m][n] = wildcard(s, p, m-1, n-1);

                                                    // special case --> '*' is encountered --> see the (n-2)th letter
    else if(p[n-1] == '*')
    {
                                                            // (n-2)th letter is '.'
        // can be treated as multiple or 1 or 0 occurrences of character
        if(p[n-2] == '.')
            dp[m][n] = wildcard(s, p, m-1, n) || wildcard(s, p, m, n-1) || wildcard(s, p, m, n-2);


        else                                                // (n-2)th letter is character
        {
            // match found --> can be treated as multiple or 1 or 0 occurrences of character
            if(p[n-2] == s[m-1])
                dp[m][n] = wildcard(s, p, m-1, n) || wildcard(s, p, m, n-1) || wildcard(s, p, m, n-2);


            // match does NOT found --> Ignore it (treat as 0 occurence)
            else
                dp[m][n] = wildcard(s, p, m, n-2);
        }
    }

                                                    // match not found --> return FALSE
    else
        dp[m][n] = 0;

    return dp[m][n];
}


// BOTTOM-UP

bool isMatch(string s, string p) {

    int m = s.size(), n = p.size();
    bool dp[m+1][n+1];

    dp[0][0] = true;

    // pattern empty
    for(int i=1; i<m+1; i++)
        dp[i][0] = false;

    // string empty
    for(int j=1; j<n+1; j++)
    {
        if(p[j-1] == '*')
            dp[0][j] = dp[0][j-2];

        else
            dp[0][j] = false;
    }

    for(int i=1; i<m+1; i++)
    {
        for(int j=1; j<n+1; j++)
        {
            if(p[j-1] == '.' || s[i-1] == p[j-1])
                dp[i][j] = dp[i-1][j-1];

            else if(p[j-1] == '*')
            {
                if(p[j-2] == '.' || p[j-2] == s[i-1])
                    dp[i][j] = dp[i-1][j] || dp[i][j-1] || dp[i][j-2];

                else
                    dp[i][j] = dp[i][j-2];
            }

            else
                dp[i][j] = false;
        }
    }

    return dp[m][n];
}
