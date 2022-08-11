

// Method-1 --> O(n^3) time --> Brute force

int maxPoints(vector<vector<int>>& points) {

    int n = points.size();
    int maxPoints = 0;

    if(n == 1 || n == 2)
        return n;

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            float slope;
            int count = 2;
            float y = points[i][1] - points[j][1];
            float x = points[i][0] - points[j][0];

            if(x == 0)
                slope = INT_MAX;
            else
                slope =  y/x;

            for(int k=0; k<n; k++)
            {
                float newSlope;

                if( k == i || k == j)
                    continue;

                float b = points[i][1] - points[k][1];
                float a = points[i][0] - points[k][0];

                if(a == 0)
                    newSlope = INT_MAX;
                else
                    newSlope =  b/a;

                if(newSlope == slope)
                    count++;
            }

            maxPoints = max(maxPoints, count);
        }
    }

    return maxPoints;
}




// Method-2 --> O(n^2) time | O(n) space

unordered_map<float, int> mp;

int maxPoints(vector<vector<int>>& points) {

    int n = points.size();
    int maxPoints = 0;

    if(n == 1 || n == 2)
        return n;

    for(int i=0; i<n-1; i++)
    {
        mp.clear();
        float slope;
        for(int j=i+1; j<n; j++)
        {
            float y = points[i][1] - points[j][1];
            float x = points[i][0] - points[j][0];

            if(x == 0)
                slope = INT_MAX;
            else
                slope = y/x;

            if(mp.find(slope) == mp.end())
                mp[slope] = 2;

            else
                mp[slope]++;
        }

        for(auto it : mp)
            maxPoints = max(maxPoints, it.second);
    }

    return maxPoints;
}
