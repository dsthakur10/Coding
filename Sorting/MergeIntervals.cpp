
vector<vector<int>> merge(vector<vector<int>>& intervals)
{
    int n = intervals.size();
    vector<vector<int>> merged;

    sort(intervals.begin(), intervals.end());

    for(auto interval : intervals)
    {
        if(merged.empty() || merged.back()[1] < interval[0])
            merged.push_back(interval);

        else
            merged.back()[1] = max(merged.back()[1], interval[1]);
    }

    return merged;
}
