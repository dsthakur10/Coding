/*

Next SMALLER to RIGHT


*/


#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;

vector<int> nextSmallerElementRight(int n, int a[])
{
    stack<int> st;
    vector<int> result;

    for(int i=n-1; i>=0; i--)
    {
        if(st.empty())
            result.push_back(-1);

        else if(st.top() < a[i])
            result.push_back(st.top());

        else
        {
            while(!st.empty() && st.top() >= a[i])
                st.pop();

            if(st.empty())
                result.push_back(-1);

            else
                result.push_back(st.top());
        }

        st.push(a[i]);
    }

    reverse(result.begin(), result.end());

    return result;
}


int main()
{
    int arr[] = {9,4,15,6,2,10};
    //int arr[] = {1,5,0,3,4,5};
    int n = sizeof(arr)/sizeof(arr[0]);

    vector<int> result = nextSmallerElementRight(n, arr);

    cout << "\nResult given: ";

    for(int i=0; i<result.size(); i++)
        cout << result[i] << " ";

    return 0;
}
