
// Delete a middle element from stack (recursively)

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

void deleteMiddle(stack<int, vector<int>>& st, int middleIndex);

int main()
{
    //vector<int> vec = {2,3,7,6,4,5,9};
    //vector<int> vec = {100, 70, 60, 20, 1};
    //vector<int> vec = {1, 5, 7, 9, 24};
    //vector<int> vec = {1};
    vector<int> vec = {100, 99};
    //vector<int> vec = {20, 40, 10, 77, 33, 88, 66, 99};
    //vector<int> vec = {2,2,2,3,2,2};

    stack<int, vector<int>> st(vec);
    stack<int, vector<int>> mystack = st;

    cout << "\nOld Stack = ";
    while(!mystack.empty())
    {
        cout << mystack.top() << " ";
        mystack.pop();
    }

    //int middle = st.size() - (st.size()/2);
    int middle = (st.size()/2) + 1;
    deleteMiddle(st, middle);

    cout << "\nUpdated Stack = ";
    while(!st.empty())
    {
        cout << st.top() << " ";
        st.pop();
    }

    return 0;
}



void deleteMiddle(stack<int, vector<int>>& st, int middleIndex)
{
    if(st.size() == 0)                          // base condition
        return;

    if(middleIndex == 1)
    {
        st.pop();
        return;
    }

    int x = st.top();
    st.pop();

    deleteMiddle(st, middleIndex-1);            // hypothesis

    st.push(x);                                 // induction
}

