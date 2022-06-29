// Sort a stack (recursively

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void sortStack(stack<int, vector<int>>& st);
void insertStack(stack<int, vector<int>>& st, int x);


int main()
{
    //vector<int> vec = {2,3,7,6,4,5,9};
    //vector<int> vec = {100, 70, 60, 20, 1};
    //vector<int> vec = {1, 5, 7, 9, 24};
    //vector<int> vec = {1};
    //vector<int> vec = {};
    vector<int> vec = {20, 40, 10, 77, 33, 88, 66};
    //vector<int> vec = {2,2,2,3,2,2};

    stack<int, vector<int>> st(vec);

    cout << "Sorted Stack = ";

    sortStack(st);

    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}



void sortStack(stack<int, vector<int>>& st)
{
    if(st.size() == 0 || st.size() == 1)             // base condition
        return;

    int x = st.top();
    st.pop();

    sortStack(st);           // hypothesis

    insertStack(st, x);      // induction
}



void insertStack(stack<int, vector<int>>& st, int x)
{
    if(st.size() == 0 || st.top() <= x)             // base condition
        st.push(x);

    else                                   // induction
    {
        int y = st.top();
        st.pop();

        insertStack(st, x);          // hypothesis

        st.push(y);
    }
}
