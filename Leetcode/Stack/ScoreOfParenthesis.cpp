/*

Given a balanced parentheses string s, return the score of the string.

The score of a balanced parentheses string is based on the following rule:

"()" has score 1.
AB has score A + B, where A and B are balanced parentheses strings.
(A) has score 2 * A, where A is a balanced parentheses string.


*/



int scoreOfParentheses(string s)
{
    stack<string> st;
    string check;

    for(int i=0; i<s.size(); i++)
    {
        check += s[i];

        if(check == "(")
            st.push("(");

        else
        {
            if(st.top() == "(")
            {
                st.pop();
                st.push("1");
            }

            else
            {
                int temp = 0;
                string str;
                while(!st.empty() && st.top() != "(")
                {
                    str += st.top();
                    temp += stoi(str);

                    st.pop();
                    str.clear();
                }

                if(!st.empty())
                {
                    st.pop();
                    temp *= 2;
                    st.push(to_string(temp));
                }
            }
        }

        check.clear();
    }

    int score = 0;
    while(!st.empty())
    {
        score += stoi(st.top());
        st.pop();
    }

    return score;
}



int scoreOfParentheses2(string s) {

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


// Method-3 --> count cores (maintain balance variable to keep track of depth of '()')

int scoreOfParentheses3(string s)
{
    char prev = '(';
    int balance = 0;
    int result = 0;

    for(const char& ch : s)
    {
        if(ch == '(')
            balance++;

        else
        {
            balance--;
            if(prev == '(')
                result += pow(2, balance);
        }

        prev = ch;
    }

    return result;

}
