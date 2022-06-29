/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    1. Open brackets must be closed by the same type of brackets.
    2. Open brackets must be closed in the correct order.

*/


#include<iostream>
#include<stack>
#include<queue>
#include <string>

bool isValid(std::string s);


int main()
{
    std::string str;
    std::cout<<"Enter the string of parentheses :\n";
    std::cin >> str;

    std::cout <<"\nString str = "<< str << "\n";

    bool flag = isValid(str);

    if(flag)
        std::cout << "\nVALID.\n";
    else
        std::cout << "\nINVALID. TRY AGAIN.\n";

    return 0;
}


bool isValid(std::string s)
{
    std::stack<char> st;

    for(std::string::iterator it = s.begin(); it != s.end(); ++it)
    {
        if(*it == '{' || *it == '(' || *it == '[' )                         // push only opening brackets in stack
            st.push(*it);

        else
        {
            if(st.empty())                          // case when stack is empty (perfectly balanced parenthesis until now) but we are getting closing bracket in string next
                return false;

            switch(*it)
            {
            case '}':
                if(st.top() != '{')                 // the closing bracket must match opening bracket in stack to avoid imbalance
                    return false;
                else
                    st.pop();                       // popping that opening bracket
                break;

            case ')':
                if(st.top() != '(')
                    return false;
                else
                    st.pop();
                break;

            case ']':
                if(st.top() != '[')
                    return false;
                else
                    st.pop();
                break;

            default:
                std::cout <<"\nString contains other characters than parenthesis.\n";
                return false;
            }
        }
    }

    if(!st.empty())                 // case when #opening brackets > #closing brackets
        return false;

    return true;
}
