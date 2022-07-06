/*

Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]

*/


vector<vector<string>> result;

vector<vector<string>> partition(string s) {

    if(s.empty())
        return result;

    vector<string> output;
    getPalindromes(output, s, 0);

    return result;
}

void getPalindromes(vector<string>& output, string s, int index)
{
    int n = s.size();
    if(index == n)
    {
        result.push_back(output);
        return;
    }

    // check for every substring from [index, i]
    // If it is palindrome, check its neighbor --> [i+1, ....]

    for(int i=index; i<n; i++)
    {
        if(isPalindrome(s, index, i))
        {
            string str = s.substr(index, i-index+1);
            output.push_back(str);

            getPalindromes(output, s, i+1);

            output.pop_back();
        }
    }
}


bool isPalindrome(const string& s, int start, int end)
{
    while(start <= end)
    {
        if(s[start++] != s[end--])
            return false;
    }

    return true;
}

