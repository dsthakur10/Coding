// Score of Parenthesis

/*
Given a balanced parentheses string s, return the score of the string.

The score of a balanced parentheses string is based on the following rule:

"()" has score 1.
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.


Example 1:
Input: s = "()"
Output: 1

Example 2:
Input: s = "(())"
Output: 2

Example 3:
Input: s = "()()"
Output: 2

Constraints:

2 <= s.length <= 50
s consists of only '(' and ')'.
s is a balanced parentheses string.

*/


// Method-1 --> Stack

// Idea is simple --> Push '(' as soon as you encounter it.
// If you encounter ')', you have 2 options :
//      (a) stack top = '(' --> pop & push 1
//      (b) stack top = number --> until top = number, pop & add it to temporary variable
//          (1) If stack is empty --> push temp (No need to double the temp, as no () found outside)
//          (2) If stack top = '(' --> pop it & push 2*temp
//      while stack is empty --> pop & add numbers to score --> Return score


int scoreOfParentheses(string s)
{
    int score = 0;
    stack<string> st;

    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == '(')         // s[i] = '('
            st.push("(");

        else                    // we have s[i] = ')'
        {
            if(st.top() == "(")
            {
                st.pop();
                st.push("1");
            }

            else                // we have stack top = number
            {
                int temp = 0;
                string str;
                while(!st.empty() && st.top() != "(")
                {
                    str = st.top();
                    st.pop();
                    temp += stoi(str);
                }

                if(st.empty())      // No '(' to check on --> No need to double the current score
                {
                    st.push(to_string(temp));
                }

                else                // '(' present --> Need to double the score
                {
                    st.pop();
                    st.push(to_string(2*temp));
                }
            }
        }
    }

    string str;
    while(!st.empty())
    {
        str = st.top();
        st.pop();
        score += stoi(str);
    }

    return score;
}


// Method-2 --> Stack

/*

Every position in the string has a depth - some number of matching parentheses surrounding it.
For example, the dot in (()(.())) has depth 2, because of these parentheses: (__(.__))

Our goal is to maintain the score at the current depth we are on.
    --> When we see an opening bracket, we increase our depth, and our score at the new depth is 0.
    --> When we see a closing bracket, we add twice the score of the previous deeper part - except when
        counting (), which has a score of 1.

For example, when counting (()(())), our stack will look like this:

[0, 0] after parsing (
[0, 0, 0] after (
[0, 1] after )
[0, 1, 0] after (
[0, 1, 0, 0] after (
[0, 1, 1] after )
[0, 3] after )
[6] after )

*/


int scoreOfParentheses(string s)
{
    stack<int> st;

    st.push(0);

    for(int i=0; i<s.size(); i++)
    {
        if(s[i] == '(')
            st.push(0);

        else
        {
            int x = st.top();
            st.pop();

            int y = st.top();
            st.pop();

            st.push(y + max(2*x, 1));
        }
    }

    return st.top();
}
