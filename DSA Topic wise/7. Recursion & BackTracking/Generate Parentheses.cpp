
// Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.



// Method-1 --> Pass by Value

vector<string> result;

vector<string> generateParenthesis(int n) {

    string output = "(";
    getValidParentheses(output, n, 1, 0);
    return result;
}

void getValidParentheses(string output, int n, int open, int close)
{
    if(open == n && close == n)
    {
        result.push_back(output);
        return;
    }

    if(open < n)
    {
        getValidParentheses(output + '(', n, open+1, close);
    }

    if(close < open)
    {
        getValidParentheses(output + ')', n, open, close+1);
    }
}



// Method-2 --> Pass by Reference

vector<string> result;

vector<string> generateParenthesis(int n) {

    string output = "(";
    getValidParentheses(output, n, 1, 0);
    return result;
}

void getValidParentheses(string& output, int n, int open, int close)
{
    if(open == n && close == n)
    {
        result.push_back(output);
        return;
    }

    if(open < n)
    {
        output.push_back('(');
        getValidParentheses(output, n, open+1, close);
        output.pop_back();
    }

    if(close < open)
    {
        output.push_back(')');
        getValidParentheses(output, n, open, close+1);
        output.pop_back();
    }
}
