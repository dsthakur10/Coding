/*

Given a string, a partitioning of the string is a palindrome partitioning if every substring of the partition is a palindrome.

For example, “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”.

Determine the fewest cuts needed for a palindrome partitioning of a given string.

Eg:
minimum of 3 cuts are needed for “ababbbabbababa”. The three cuts are “a | babbbab | b | ababa”.

If a string is a palindrome, then minimum 0 cuts are needed. If a string of length n containing all different characters, then minimum n-1 cuts are needed.


Input : str = “geek”
Output : 2
We need to make minimum 2 cuts, i.e., “g | ee | k”

Input : str = “aaaa”
Output : 0
The string is already a palindrome.

Input : str = “abcde”
Output : 4

Input : str = “abbac”
Output : 1

*/


#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<climits>

static int dp[101][101];

int palindromePartition(std::string str, int i, int j);                     // Top_Down memoization
int palindromePartition2(std::string str, int n);                           // Bottom-Up
int palindromePartition3(std::string str, int i, int j);                    // optimized version

int main()
{
    memset(dp, -1, sizeof(dp));

    std::string str;

    std::cout << "\nEnter string: ";
    std::cin >> str;

    int cost = palindromePartition(str, 0, str.size()-1);
    std::cout << "\n\nTOP-DOWN: Minimum #partitions = " << cost << "\n";


    cost = palindromePartition2(str, str.size());
    std::cout << "\n\nBOTTOM-UP: Minimum #partitions = " << cost;

    return 0;

}



int palindromePartition(std::string str, int i, int j)
{
    if(i >= j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    std::string sub = str.substr(i,j-i+1);
    std::string rev = std::string(sub.rbegin(),sub.rend());

    //std::cout << "\n"<< rev ;

    if(sub.compare(rev) == 0)
        dp[i][j] = 0;

    else
    {
        int minimum = INT_MAX;
        int temp;

        for(int k=i; k<j; k++)
        {
            temp = 1 + palindromePartition(str, i, k) + palindromePartition(str, k+1, j);
            minimum = std::min(minimum, temp);
        }

        dp[i][j] = minimum;
        //std::cout << " dp[i][j] = " << dp[i][j];

    }

    return dp[i][j];
}



int palindromePartition2(std::string str, int n)
{
    int dp[n+1][n+1];

    for(int i=1; i<=n; i++)
        dp[i][i] = 0;

    for(int l=2; l<=n; l++)
    {
        for(int i=1; i<=n-l+1 ; i++)
        {
            int j = i+l-1;

            std::string sub = str.substr(i-1,j-i+1);
            std::string rev = std::string(sub.rbegin(),sub.rend());

            if(sub.compare(rev) == 0)
            {
                dp[i][j] = 0;
                continue;
            }

            int minimum = INT_MAX;

            for(int k=i; k<j; k++)
            {
                int temp = dp[i][k] + dp[k+1][j] + 1;

                minimum = std::min(minimum, temp);
            }

            dp[i][j] = minimum;
        }
    }


    for(int i=0; i<n+1; i++)
    {
        std::cout << "\n";
        for(int j=0; j<n+1; j++)
            std::cout << dp[i][j] <<" ";
    }

    return dp[1][n];
}




int palindromePartition3(std::string str, int i, int j)
{
    if(i >= j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    std::string sub = str.substr(i,j-i+1);
    std::string rev = std::string(sub.rbegin(),sub.rend());

    //std::cout << "\n"<< rev ;

    if(sub.compare(rev) == 0)
        dp[i][j] = 0;

    else
    {
        int minimum = INT_MAX;
        int temp;

        for(int k=i; k<j; k++)
        {
            temp = 1 + palindromePartition(str, i, k) + palindromePartition(str, k+1, j);
            minimum = std::min(minimum, temp);
        }

        dp[i][j] = minimum;
        //std::cout << " dp[i][j] = " << dp[i][j];

    }

    return dp[i][j];
}




// LATEST

// TOP-DOWN --> TLE

int dp[2001][2001];

int minCut(string s) {
    memset(dp, -1, sizeof(dp));
    int n = s.size();

    return palindromePartition(s, 0, n-1);
}


int palindromePartition(string s, int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    if(i>j)
        return 0;

    if(i == j)
        return dp[i][j] = 0;

    if(isPalindrome(s, i, j))
        return dp[i][j] = 0;

    dp[i][j] = INT_MAX;
    for(int k = i; k < j; k++)
    {
        int temp = 1 +
            palindromePartition(s, i, k) + palindromePartition(s, k+1, j);

        dp[i][j] = min(dp[i][j], temp);
    }

    return dp[i][j];
}


bool isPalindrome(string& s, int i, int j)
{
    while(i <= j)
    {
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }

    return true;
}


// TOP-DOWN 2 --> TLE

int dp[2001][2001];

int minCut(string s) {
    memset(dp, -1, sizeof(dp));
    int n = s.size();

    return palindromePartition(s, 0, n-1);
}


int palindromePartition(string& s, int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    if(i>j)
        return 0;

    if(i == j)
        return dp[i][j] = 0;

    if(isPalindrome(s, i, j))
        return dp[i][j] = 0;

    dp[i][j] = INT_MAX;
    for(int k = i; k < j; k++)
    {
        int x = (dp[i][k] == -1) ? palindromePartition(s, i, k) : dp[i][k];
        int y = (dp[k+1][j] == -1) ? palindromePartition(s, k+1, j) : dp[k+1][j];
        int temp = 1 + x + y;

        dp[i][j] = min(dp[i][j], temp);
    }

    return dp[i][j];
}


bool isPalindrome(string& s, int i, int j)
{
    while(i <= j)
    {
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }

    return true;
}


// TOP-DOWN-3 --> Works correctly --> ONLY recurse to 2nd half if the first half is palindrome

int dp[2001][2001];

int minCut(string s) {
    memset(dp, -1, sizeof(dp));
    int n = s.size();

    return palindromePartition(s, 0, n-1);
}


int palindromePartition(string& s, int i, int j)
{
    if(dp[i][j] != -1)
        return dp[i][j];

    if(i>j)
        return 0;

    if(i == j)
        return dp[i][j] = 0;

    if(isPalindrome(s, i, j))
        return dp[i][j] = 0;

    dp[i][j] = INT_MAX;
    for(int k = i; k < j; k++)
    {
        if(isPalindrome(s, i, k))
        {
            int temp = 1 + palindromePartition(s, k+1, j);
            dp[i][j] = min(dp[i][j], temp);
        }
    }

    return dp[i][j];
}

bool isPalindrome(string& s, int i, int j)
{
    while(i <= j)
    {
        if(s[i] != s[j])
            return false;
        i++;
        j--;
    }

    return true;
}




// Method-3 --> FRONT-PARTITION method --> TOP-DOWN

int dp[2001];

bool isPalindrome( string& s, int i, int j )
{
    while( i<j ){
        if( s[i] != s[j] )
            return false;
        i++, j--;
    }
    return true;
}


int solve(string& s, int index, int n)
{
    if(dp[index] != -1)
        return dp[index];

    if(index >= n-1)
        return 0;

    // check if the whole string starting from index till the end is palindrome --> Return 0 cuts if YES
    if(isPalindrome(s, index, n-1))
        return dp[index] = 0;

    int ans = INT_MAX;
    for(int i=index; i<n-1; i++)        // last cur is made (index...n-2) | (n-1...n-1)
    {
        if(isPalindrome(s, index, i))               // recurse only if the left half of string is palindrome
        {
            ans = min(ans, 1 + solve(s, i+1, n));
        }
    }

    return dp[index] = ans;
}

int minCut(string s) {

    memset(dp, -1, sizeof(dp));
    int n = s.size();
    return solve(s, 0, n);
}



// Method-3 --> FRONT-PARTITION method --> BOTTOM-UP

bool isPalindrome( string& s, int i, int j )
{
    //cout<< s.substr( i, j-i+1 ) <<"\n";
    while( i<j ){
        if( s[i] != s[j] )
            return false;
        i++, j--;
    }
    return true;
}


int minCut(string s) {

    int n = s.size();
    int dp[n];

    dp[n-1] = 0;
    for(int i=n-2; i>=0; i--)
    {
        if(isPalindrome(s, i, n-1))
        {
            dp[i] = 0;
            continue;
        }

        int ans = INT_MAX;
        for(int j=i; j<n-1; j++)
        {
            if(isPalindrome(s, i, j))
                ans = min(ans, 1 + dp[j+1]);
        }

        dp[i] = ans;
    }

    return dp[0];
}
