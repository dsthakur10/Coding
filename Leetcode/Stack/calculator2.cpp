#include<iostream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

int precedence(char c);
vector<string> infixToPostfix(string s);
int postfixEvaluation(vector<string> tokens);

int calculate(string s);
int calculate2(string s);

int main()
{
    string str;

    cout << "\nEnter the string: ";
    cin >> str;

    cout << "\n\nPostfix Evaluation = " << calculate2(str);

}


int precedence(char c)
{
    if(c == '^')
        return 3;

    else if(c == '/' || c=='*')
        return 2;

    else if(c == '+' || c == '-')
        return 1;

    else
        return -1;
}



vector<string> infixToPostfix(string s)
{
    stack<char> st;
    vector<string> tokens;
    string temp;
    int i=0;

    while(i < s.size())
    {
        if(s[i] != '/' && s[i] != '*' && s[i] != '+' && s[i] != '-')
        {
            while(i < s.size() && s[i] != '/' && s[i] != '*' && s[i] != '+' && s[i] != '-')
            {
                temp += s[i];
                i++;
            }

            tokens.push_back(temp);
            temp.clear();
        }

        else
        {
            if(st.empty() || precedence(st.top()) < precedence(s[i]))
                st.push(s[i]);

            else
            {
                while(!st.empty() && precedence(st.top()) >= precedence(s[i]))
                {
                    temp += st.top();
                    tokens.push_back(temp);
                    st.pop();
                    temp.clear();
                }

                st.push(s[i]);
            }

            i++;
        }
    }

    while(!st.empty())
    {
        temp += st.top();
        tokens.push_back(temp);
        st.pop();
        temp.clear();
    }

    return tokens;
}



int postfixEvaluation(vector<string> tokens)
{
    stack<int> st;

    for(int i=0; i<tokens.size(); i++)
    {
        if(tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "+" || tokens[i] == "-")
        {
            int op2 = st.top();
            st.pop();
            int op1 = st.top();
            st.pop();

            if(tokens[i] == "/")
                st.push(op1 / op2);

            else if(tokens[i] == "*")
                st.push(op1 * op2);

            else if(tokens[i] == "+")
                st.push(op1 + op2);

            else if(tokens[i] == "-")
                st.push(op1 - op2);
        }

        else
        {
            int x = stoi(tokens[i]);
            st.push(x);
        }
    }

    return st.top();
}


// Method-1 --> (1) INFIX to POSTFIX (2) POSTFIX evaluation

int calculate(string s)
{
    vector<string> tokens = infixToPostfix(s);

    cout << "\n\nConverted Postfix expression = ";
    for(int i=0; i<tokens.size(); i++)
        cout << tokens[i] << " ";

    int result = postfixEvaluation(tokens);

    return result;
}



int calculate2(string s)
{
    stack<int> digits;
    string temp;
    int var1,var2;
    char first, second='!';

    int i=0;
    while(i < s.size() && s[i] != '/' && s[i] != '*' && s[i] != '+' && s[i] != '-')
    {
        temp += s[i];
        i++;
    }

    if(i == s.size())
        return stoi(temp);

    digits.push(stoi(temp));
    temp.clear();

    first = s[i];
    i++;

    while(i < s.size())
    {
        while(i < s.size() && s[i] != '/' && s[i] != '*' && s[i] != '+' && s[i] != '-')
        {
            temp += s[i];
            i++;
        }

        if(!temp.empty())
            digits.push(stoi(temp));
        temp.clear();

        if(second != '!')
        {
            var2 = digits.top();
            digits.pop();
            var1 = digits.top();
            digits.pop();

            if(second == '*')
                digits.push(var1 * var2);

            else if(second == '/')
                digits.push(var1 / var2);

            second = '!';
        }


        second = s[i];
        i++;

        if(first == '*' || first == '/')
        {
            var2 = digits.top();
            digits.pop();
            var1 = digits.top();
            digits.pop();

            if(first == '*')
                digits.push(var1 * var2);

            else if(first == '/')
                digits.push(var1 / var2);

            first = second;
            second = '!';
        }

        else
        {
            if(second == '+' || second == '-')
            {
                var2 = digits.top();
                digits.pop();
                var1 = digits.top();
                digits.pop();

                if(first == '+')
                    digits.push(var1 + var2);

                else if(first == '-')
                    digits.push(var1 - var2);

                first = second;
                second = '!';
            }
        }
    }

    var2 = digits.top();
    digits.pop();
    var1 = digits.top();
    digits.pop();

    if(first == '*')
        return var1 * var2;

    else if(first == '/')
        return var1 / var2;

    else if(first == '+')
        return var1 + var2;

    else
        return var1 - var2;
}



