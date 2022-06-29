
bool validateStackSequences(vector<int>& pushed, vector<int>& popped)
{
    stack<int> st;
    int i=0,j=0;

    while(i<pushed.size())
    {
        while(i<pushed.size() && pushed[i] != popped[j])
        {
            st.push(pushed[i]);
            i++;
            //cout<<"\n"<<st.top()<<" will be added";
        }

        st.push(pushed[i++]);
        //cout<<"\n"<<st.top()<<" will be added";

        while(!st.empty() && popped[j] == st.top())
        {
            //cout<<"\n"<<st.top()<<" will be deleted";
            st.pop();
            j++;
        }

        //cout<<endl<<"i = "<<i<<"\tj = "<<j<<endl;
    }

    if(st.empty())
        return true;


    return false;
}
