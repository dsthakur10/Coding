/*

Next GREATER to LEFT


*/


#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

vector<int> nextLargerElementLeft(int n, int a[])
{
    stack<int> st;
    vector<int> result;

    for(int i=0; i<n; i++)
    {
        if(st.empty())
            result.push_back(-1);

        else if(a[i] < st.top())
            result.push_back(st.top());

        else if(a[i] >= st.top())
        {
            while(!st.empty() && a[i] >= st.top())
                st.pop();

            if(st.empty())
                result.push_back(-1);

            else
                result.push_back(st.top());
        }


        st.push(a[i]);
    }

    return result;
}



int main()
{
    //int arr[] = {9,4,15,6,2,10};
    int arr[] = {1,5,0,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    vector<int> result = nextLargerElementLeft(n, arr);

    cout << "\nResult given: ";

    for(int i=0; i<result.size(); i++)
        cout << result[i] << " ";

    return 0;
}
