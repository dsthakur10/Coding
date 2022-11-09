class CustomStack {
public:

    int limit;
    stack<int> st;
    stack<int> reference;

    CustomStack(int maxSize) {
        limit = maxSize;
    }

    void push(int x) {

        if(st.size() < limit)
            st.push(x);
    }

    int pop() {

        if(st.empty())
            return -1;

        int x = st.top();
        st.pop();
        return x;
    }

    // O(n) time
    void increment(int k, int val) {

        while(st.size() > k)
        {
            reference.push(st.top());
            st.pop();
        }

        while(!st.empty())
        {
            reference.push(st.top() + val);
            st.pop();
        }

        while(!reference.empty())
        {
            st.push(reference.top());
            reference.pop();
        }
    }
};

