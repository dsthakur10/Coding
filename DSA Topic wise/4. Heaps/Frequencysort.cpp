/*

Given an array of integers nums, sort the array in increasing order based on the frequency of the values.
If multiple values have the same frequency, sort them in decreasing order.

Return the sorted array

*/

typedef pair<int, int> pi;

// apply reverse operations in min-heap

struct compare{
    bool operator()(pi a, pi b)
    {
        if(a.first > b.first)
            return true;

        else if(a.first == b.first)
            return a.second < b.second;

        else
            return false;
    }
};


vector<int> frequencySort(vector<int>& nums) {

    vector<int> result;
    unordered_map<int, int> mp;
    priority_queue<pi, vector<pi>, compare> pq;

    for(int i=0; i<nums.size(); i++)
        mp[nums[i]]++;

    for(auto it = mp.begin(); it != mp.end(); it++)
        pq.push({it->second, it->first});

    while(!pq.empty())
    {
        int x = pq.top().second;        // element
        int count = pq.top().first;     // freq

        while(count > 0)
        {
            result.push_back(x);
            count--;
        }

        pq.pop();
    }

    return result;
}



// Method-2 --> Custom sort

vector<int> frequencySort(vector<int>& nums) {

    unordered_map<int, int> mp;
    for(int i=0; i<nums.size(); i++)
        mp[nums[i]]++;

    sort(nums.begin(), nums.end(), [&](int a, int b) {
        return mp[a] == mp[b] ? a > b : mp[a] < mp[b];
    });

    return nums;
}
