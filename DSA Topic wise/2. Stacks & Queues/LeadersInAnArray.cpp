
vector<int> leaders(int a[], int n)
{
    vector<int> result;
    stack<int> st;

    for(int i=n-1; i>=0; i--)
    {
        while(!st.empty() && a[i] >= st.top())
            st.pop();

        if(st.empty())
            result.push_back(a[i]);

        st.push(a[i]);
    }

    reverse(result.begin(), result.end());

    return result;
}
