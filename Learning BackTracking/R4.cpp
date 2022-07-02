
// Reverse the stack (recursively)

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void reverseStack(stack<int, vector<int>>& st);
void helper(stack<int, vector<int>>& st, int x);

int main()
{
    //vector<int> vec = {2,3,7,6,4,5,9};
    //vector<int> vec = {100, 70, 60, 20, 1};
    //vector<int> vec = {1, 5, 7, 9, 24};
    //vector<int> vec = {};
    //vector<int> vec = {100, 99};
    //vector<int> vec = {20, 40, 10, 77, 33, 88, 66, 99};
    //vector<int> vec = {2,2,2,3,2,2};
    vector<int> vec = {1,2,3,4,5};

    stack<int, vector<int>> st(vec);
    stack<int, vector<int>> mystack = st;

    cout << "\nOld Stack = ";
    while(!mystack.empty())
    {
        cout << mystack.top() << " ";
        mystack.pop();
    }

    reverseStack(st);

    cout << "\nReversed Stack = ";
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}



void reverseStack(stack<int, vector<int>>& st)
{
    if(st.empty())              // base condition
        return;

    int x = st.top();
    st.pop();

    reverseStack(st);           // hypothesis

    helper(st, x);              // induction
}



void helper(stack<int, vector<int>>& st, int x)
{
    if(st.empty())              // base condition
        st.push(x);

    else{
        int y = st.top();
        st.pop();

        helper(st, x);          // hypothesis

        st.push(y);             // induction
    }
}
