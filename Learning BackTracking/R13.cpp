// Generate well-formed parentheses

/*

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))", "(()())", "(())()", "()(())", "()()()"]

Example 2:
Input: n = 1
Output: ["()"]

*/


vector<string> result;

// Method-1 --> Using Stack to validate the parentheses string.

vector<string> generateParenthesis(int n)
{
    string output;
    stack<char> st;

    validParenthesis(output, st, 2*n);

    return result;
}


void validParenthesis(string output, stack<char> st, int k)
{
    if(k == 0)
    {
        result.push_back(output);

        cout << output << " ";
        return;
    }

    if(st.empty())
    {
        st.push('(');
        output += '(';
        validParenthesis(output, st, k-1);
    }

    else if(st.top() == '(')
    {
        // ((
        st.push('(');
        output += '(';
        if(st.size() <= k)  // makes '((((' & further invalid in length = 6
        {
            validParenthesis(output, st, k-1);
        }

        // undo work
        st.pop();
        output.pop_back();

        // ()
        st.pop();
        output += ')';
        validParenthesis(output, st, k-1);
    }

}



// Method-2 --> Keeping track of open & closing brackets

vector<string> generateParenthesis2(int n)
{
    string output;

    validParenthesis(output, n, n);

    return result;
}

void validParenthesis2(string output, int open, int close){

//      if(close < open || close < 0 || open < 0)
//          return;

    if(open == 0 && close == 0)
    {
        result.push_back(output);
        cout << output << " ";
        return;
    }

    int newopen = open-1;
    int newclose = close-1;

    if(newopen >= 0)
        validParenthesis(output + '(', newopen, close);

    if(open <= newclose && newclose >= 0)
        validParenthesis(output + ')', open, newclose);

}
