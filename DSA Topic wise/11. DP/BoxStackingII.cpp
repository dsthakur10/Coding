

// boxes[i][0] --> length
// boxes[i][1] --> width
// boxes[i][2] --> height


static bool comp(const vector<int>& a, const vector<int>& b)
{
    return a[0]*a[1] < b[0]*b[1];
}


int maxHeight(int height[],int width[],int length[],int n)
{
    vector<vector<int>> boxes;

    int x, y;
    for(int i=0; i<n; i++)
    {
        x = min(width[i], length[i]);
        y = max(width[i], length[i]);
        boxes.push_back( {x, y, height[i]} );

        x = min(width[i], height[i]);
        y = max(width[i], height[i]);
        boxes.push_back( {x, y, length[i]} );

        x = min(height[i], length[i]);
        y = max(height[i], length[i]);
        boxes.push_back( {x, y, width[i]} );
    }

    sort(boxes.begin(), boxes.end(), comp);

    return LIS(boxes, boxes.size());
}


int LIS(vector<vector<int>>& boxes, int N)
{
    int maxHeight = 0;
    int dp[N];

    for(int i=0; i<N; i++)
    {
        dp[i] = boxes[i][2];        // height;
        for(int j=0; j<i; j++)
        {
            if(boxes[j][0] < boxes[i][0] && boxes[j][1] < boxes[i][1])
                dp[i] = max(dp[i], boxes[i][2] + dp[j]);
        }

        maxHeight = max(maxHeight, dp[i]);
    }

    return maxHeight;
}
