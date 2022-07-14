/*

Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation:
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation:
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

*/


/*

Task is to convert word1 --> word2. Given 3 operations: replace, delete, insert

IF: A[m-1] == B[n-1]
    --> DO NOTHING --> shrink both word1 & word2
ELSE:
    --> You have 3 different ways:
        1. Replace word1[m-1] by word2[n-1] --> shrink both word1 & word2
        2. Delete character from word1 --> shrink word1
        3. Copy character from word2 --> shrink word2

    select the minimum of all 3
    dp[m][n] = 1 + min(replace, delete, copy)
*/

// TOP-DOWN

int minDistance(string word1, string word2) {

    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp (m+1, vector<int> (n+1, -1));

    return edit(word1, word2, m, n, dp);
}


int edit(string word1, string word2, int m, int n, vector<vector<int>>& dp)
{
    if(dp[m][n] != -1)
        return dp[m][n];

    if(m == 0)
        return dp[m][n] = n;

    if(n == 0)
        return dp[m][n] = m;

    // no need to edit. Just skip to next character
    if(word1[m-1] == word2[n-1])
        dp[m][n] = edit(word1, word2, m-1, n-1, dp);

    else
    {
        int x = 1 + edit(word1, word2, m-1, n-1, dp);   // replace
        int y = 1 + edit(word1, word2, m-1, n, dp);     // delete
        int z = 1 + edit(word1, word2, m, n-1, dp);     // insert

        dp[m][n] = min(x, min(y,z));
    }

    return dp[m][n];
}



// BOTTOM - UP
int minDistance(string word1, string word2) {

    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp (m+1, vector<int> (n+1, -1));

    for(int i=0; i<m+1; i++)
    {
        for(int j=0; j<n+1; j++)
        {
            if(i == 0)
                dp[i][j] = j;

            else if(j == 0)
                dp[i][j] = i;

            else if(word1[i-1] == word2[j-1])
                dp[i][j] = dp[i-1][j-1];

            else
            {
                int x = 1 + dp[i-1][j-1];   // replace
                int y = 1 + dp[i-1][j];     // delete
                int z = 1 + dp[i][j-1];     // insert

                dp[i][j] = min(x, min(y,z));
            }

        }
    }
    return dp[m][n];
}
