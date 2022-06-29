
// Maximum rectangle of all 1's in a binary matrix


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



int maximalRectangle(vector<vector<char>>& matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> heights(m, vector<int>(n,0));
    int maximum = INT_MIN;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(i != 0)
                heights[i][j] = heights[i-1][j];

            if(matrix[i][j] == '1')
                heights[i][j]++;

            else
                heights[i][j] = 0;
        }

        maximum = max(maximum, largestRectangleArea(heights[i]));

        for(int j=0; j<n; j++)
            cout << heights[i][j]<< " ";

        cout << "\n";
    }

    return maximum;
}

