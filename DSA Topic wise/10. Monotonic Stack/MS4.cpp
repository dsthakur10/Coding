// Remove Duplicate Letters

/*
Given a string s, remove duplicate letters so that every letter appears once and only once.
You must make sure your result is the smallest in lexicographical order among all possible results.

Example 1:
Input: s = "bcabc"
Output: "abc"

Example 2:
Input: s = "cbacdcbc"
Output: "acdb"

*/



string removeDuplicateLetters(string s)
{
    int n = s.size();
    vector<int> last(26, -1);
    vector<int> mark(26, 0);
    stack<int> st;
    string str;

    for(int i=0; i<n; i++)
        last[s[i] - 'a'] = i;

    for(int i=0; i<n; i++)
    {
        int x = s[i] - 'a';

        if(!mark[x])
        {
            while(!st.empty()  &&  s[i] < s[st.top()]  &&  i < last[s[st.top()] - 'a'])
            {
                mark[s[st.top()] - 'a'] = 0;
                st.pop();
            }

            st.push(i);
        }

        mark[x] = 1;
    }

    while(!st.empty())
    {
      str += s[st.top()];
      st.pop();
    }

    reverse(str.begin(), str.end());
    return str;
}
