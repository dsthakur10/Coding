/*

Next SMALLER to LEFT


Given an array a of integers of length n, find the nearest smaller number for every element such that the smaller element
is on left side.If no small element present on the left print -1.

*/


vector<int> nextSmallerElementLeft(int n, int a[])
{
    stack<int> st;
    vector<int> result;

    for(int i=0; i<n; i++)
    {
        if(st.empty())
            result.push_back(-1);

        else if(a[i] > st.top())
            result.push_back(st.top());

        else if(a[i] <= st.top())
        {
            while(!st.empty() && a[i] <= st.top())
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


