
typedef pair<int, int> pi;


// Method-1 --> Using PAIRS to store the count of #continuous days for which stock price <= given day-i
// Stack contents --> <price[i], count[i]>

vector <int> calculateSpan(int price[], int n)
{
    vector<int> result;
    stack<pi> st;

    for(int i=0; i<n; i++)
    {
        int days = 1;
        if(st.empty())
            result.push_back(1);

        else if(st.top().first > price[i])
        {
            result.push_back(1);
        }

        else if(st.top().first <= price[i])
        {
            while(!st.empty() && st.top().first <= price[i])
            {
                days += st.top().second;
                st.pop();
            }

            result.push_back(days);
        }

        st.push(make_pair(price[i], days));
    }

    return result;
}



// Method-2 --> Take help of result[st.top()] to calculate count of #continuous days for given day-i.
// Reason for choosing index over price itself is to get previous counts from result array.
// Stack contents --> Index-i

vector <int> calculateSpan2(int price[], int n)
{
    vector<int> result;
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        int count=1;
        if(st.empty())
            result.push_back(1);

        else if(price[st.top()] > price[i])
            result.push_back(1);

        else
        {
            while(!st.empty() && price[st.top()] <= price[i])
            {
                count += result[st.top()];
                st.pop();
            }

            result.push_back(count);

        }

        st.push(i);
    }

    return result;
}



// Method-3 --> Nearest GREATER to LEFT --> store index of NGL --> span[i] = i - index[i] {index[i] = index of NGL for day-i}
vector <int> calculateSpan(int price[], int n)
{
    vector<int> result(n, 1);
    vector<int> index;
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        if(st.empty())
            index.push_back(-1);

        else if(price[st.top()] > price[i])
            index.push_back(st.top());

        else
        {
            while(!st.empty() && price[st.top()] <= price[i])
                st.pop();

            if(st.empty())
                index.push_back(-1);

            else
                index.push_back(st.top());
        }

        st.push(i);
        result[i] = i-index[i];
    }

    //for(int i=0; i<n; i++)
      //  result[i] = i-index[i];

    return result;
}



// Method-4 --> Use a temp variable rather than storing indices for every element
vector <int> calculateSpan(int price[], int n)
{
    vector<int> result(n, 1);
    int index;
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        if(st.empty())
            index = -1;

        else if(price[st.top()] > price[i])
            index = st.top();


        else
        {
            while(!st.empty() && price[st.top()] <= price[i])
                st.pop();

            if(st.empty())
                index = -1;

            else
                index = st.top();
        }

        st.push(i);
        result[i] = i-index;
    }

    return result;
}
