//


//Function to calculate the span of stock[] price for all n days.
vector <int> calculateSpan(int price[], int n)
{
    vector<int> result(n);
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        while(!st.empty() && price[i] >= price[st.top()])
            st.pop();

        if(st.empty())
            result[i] = i+1;

        else
            result[i] = i - st.top();

        st.push(i);
    }


    return result;
}



// Online Stock Span
class StockSpanner
{
    public:
    int counter, result;
    stack<int> st;
    vector<int> my;

    StockSpanner() {
        counter = 0;
    }

    int next(int price) {

        while(!st.empty() && price >= my[st.top()])
            st.pop();

        if(st.empty())
            result = counter+1;

        else
            result = counter - st.top();

        my.push_back(price);
        st.push(counter++);

        return result;
    }
};
