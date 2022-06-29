
// Use NSL-index & NSR-index to get the boundary limits for any given building-i
// area = max {heights[i] * (NSRIndex[i] - NSLIndex[i] - 1)}

// Use 2 pseudo indices (-1 for NSL & n for NSR) --> If no NSL/NSR exists, use pseudo indices to make our calculation correct.

// eg {1,2,3,4,5} / {5,4,3,2,1}


int largestRectangleArea(vector<int>& heights)
{
    vector<int> smallerLeft = nextSmallerElementLeft(heights);
    vector<int> smallerRight = nextSmallerElementRight(heights);

    int maxx = INT_MIN;
    int n = heights.size();

    for(int i=0; i<n; i++)
    {
        maxx = max(maxx, heights[i] * (smallerRight[i] - smallerLeft[i] - 1));
    }

    return maxx;
}


vector<int> nextSmallerElementLeft(vector<int> heights)
{
    stack<int> st;
    vector<int> result;

    int n = heights.size();
    for(int i=0; i<n; i++)
    {
        if(st.empty())
            result.push_back(-1);

        else if(heights[i] > heights[st.top()])
            result.push_back(st.top());

        else if(heights[i] <= heights[st.top()])
        {
            while(!st.empty() && heights[i] <= heights[st.top()])
                st.pop();

            if(st.empty())
                result.push_back(-1);

            else
                result.push_back(st.top());
        }


        st.push(i);
    }

    return result;
}


vector<int> nextSmallerElementRight(vector<int> heights)
{
    stack<int> st;
    vector<int> result;

    int n = heights.size();
    for(int i=n-1; i>=0; i--)
    {
        if(st.empty())
            result.push_back(n);

        else if(heights[st.top()] < heights[i])
            result.push_back(st.top());

        else
        {
            while(!st.empty() && heights[st.top()] >= heights[i])
                st.pop();

            if(st.empty())
                result.push_back(n);

            else
                result.push_back(st.top());
        }

        st.push(i);
    }

    reverse(result.begin(), result.end());

    return result;
}

