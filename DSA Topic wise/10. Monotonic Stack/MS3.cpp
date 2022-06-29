// Maximal Rectangle

/*
Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's
and return its area.

Example 1:
Input: matrix= [["1","0","1","0","0"],
                ["1","0","1","1","1"],
                ["1","1","1","1","1"],
                ["1","0","0","1","0"]]
Output: 6
Explanation: The maximal rectangle is shown in the above picture.

Example 2:
Input: matrix = [["0"]]
Output: 0

Example 3:
Input: matrix = [["1"]]
Output: 1

*/


vector<int> NSL, NSR;

int maximalRectangle(vector<vector<char>>& matrix) {

    int m = matrix.size(), n = matrix[0].size();
    vector<int> heights(n, 0);
    int area = 0;

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(matrix[i][j] == '1')
                heights[j]++;
            else
                heights[j] = 0;
        }

        area = max(area, largestRectangleArea(heights));
    }

    return area;
}


int largestRectangleArea(vector<int>& heights) {

    nextSmallestToLeft(heights);
    nextSmallestToRight(heights);

    int area = 0;
    for(int i=0; i<heights.size(); i++)
    {
        area = max(area, heights[i] * (NSR[i] - NSL[i] - 1));
    }

    return area;
}


void nextSmallestToLeft(vector<int>& heights)
{
    int n = heights.size();
    NSL = vector<int>(n, -1);
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        while(!st.empty() && heights[st.top()] >= heights[i])
            st.pop();

        if(!st.empty())
            NSL[i] = st.top();

        st.push(i);
    }
}


void nextSmallestToRight(vector<int>& heights)
{
    int n = heights.size();
    NSR = vector<int>(n, n);
    stack<int> st;

    for(int i=n-1; i>=0; i--)
    {
        while(!st.empty() && heights[st.top()] >= heights[i])
            st.pop();

        if(!st.empty())
            NSR[i] = st.top();

        st.push(i);
    }
}
