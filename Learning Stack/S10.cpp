// Longest valid parenthesis

/*

Given a string containing just the characters '(' and ')',
find the length of the longest valid (well-formed) parentheses substring.

*/



// Method-1 --> Brute force --> O(n^3) time | O(n) space

/*
    Consider every substring of EVEN length & check if it is a valid string
    To check a validity of a parenthesis string is too easy.

    Generating every substring will take O(n^2) time. Each substring will take O(n) time to check its validity --> O(n^3) time.
*/


bool isValid(string s)
{
    stack<char> st;

    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == '(')
            st.push(s[i]);

        else
        {
            if(st.empty())
                return false;
            else if(st.top() == '(')
                st.pop();
        }
    }

    return st.empty();
}



int longestValidParentheses(string s)
{
    int n = s.size();
    int maxLen = 0;
    for(int i=0; i<=n-2; i++)
    {
        for(int j=i+1; j<=n-1; j=j+2)
        {
            if(isValid(s.substr(i,j-i+1)))
                maxLen = max(maxLen, j-i+1);
        }
    }

    return maxLen;
}



// Method-2 --> Dynamic programming

int longestValidParentheses2(string s)
{
    int n = s.size();
    int maxLen = 0;
    vector<int> dp(n,0);

    for(int i=1; i<n; i++)
    {
        if(s[i] == ')')
        {
            if(s[i-1] == '(')
                dp[i] = ((i-2 >= 0) ? dp[i-2] : 0 ) + 2;

            else if((i - dp[i-1] - 1 >= 0) && s[i - dp[i-1] - 1] == '(')
                dp[i] = dp[i-1] + ( (i - dp[i-1] - 2 >= 0) ? dp[i - dp[i-1] - 2] : 0) + 2;

            maxLen = max(maxLen, dp[i]);
        }
    }

    return maxLen;
}



// Method-3 --> Stack --> O(n) time | O(n) space

int longestValidParentheses3(string s)
{
    int maxLen = 0;
    stack<int> st;

    st.push(-1);
    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == '(')
            st.push(i);

        else if(s[i] == ')')
        {
            if(st.empty() || st.top() == -1)
                st.push(i);

            else if(s[st.top()] == '(')
                st.pop();

            else
                st.push(i);
        }
    }

    if(st.empty())
        return s.size();

    int x = s.size()-1;
    while(!st.empty())
    {
        maxLen = max(x - st.top(), maxLen);
        x = st.top() - 1;
        st.pop();
    }

    return maxLen;
}
