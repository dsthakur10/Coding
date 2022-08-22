vector<string> result;

vector<string> generateParenthesis(int n) {

    int open = 1, close = 0;
    string input = "(";

    parentheses(input, open, close, n);

    return result;
}

void parentheses(string& input, int open, int close, int n)
{
    if(open == n && close == n)
    {
        result.push_back(input);
        return;
    }


    if(close > open)
        return;

    if(open > n || close > n)
        return;

    input.push_back('(');
    parentheses(input, open+1, close, n);
    input.pop_back();

    input.push_back(')');
    parentheses(input, open, close+1, n);
    input.pop_back();
}
