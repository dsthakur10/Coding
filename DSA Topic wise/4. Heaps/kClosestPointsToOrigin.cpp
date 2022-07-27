/*



*/


// Method-1 --> Max-heap

typedef pair<int, pair<int, int>> ppi;

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

    vector<vector<int>> result;
    priority_queue<ppi> pq;

    for(int i=0; i<points.size(); i++)
    {
        int distance = (points[i][0]*points[i][0]) + (points[i][1]*points[i][1]);

        pq.push({distance, {points[i][0], points[i][1]}});

        if(pq.size() > k)
            pq.pop();
    }

    while(!pq.empty())
    {
        int u = pq.top().second.first;
        int v = pq.top().second.second;

        result.push_back({u,v});
        pq.pop();
    }

    return result;
}



// Method-2 --> Quick-Select

// Implementation of Quick-Select using nth_element() of STL

static bool compare(vector<int>& a, vector<int>& b)
{
    return a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1];
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {

    nth_element(points.begin(), points.begin() + k, points.end(), compare);

    vector<vector<int>> result(points.begin(), points.begin() + k);

    return result;
}
