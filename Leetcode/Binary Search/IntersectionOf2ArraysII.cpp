// Duplicates allowed

/*
    1. If array is given sorted, use 2 pointer approach
    2. If given one array1's size <<<<<< array2's size , use HashMap

*/


// Method-1 --> 2 pointer (requires sorted arrays) --> O(nlogn + mlogm)  |  O(1) space

vector<int> findIntersection(vector<int>& a, vector<int>& b)
{
    // vector a is smaller than b
    vector<int> result;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int m = a.size(), n = b.size();

    int i=0, j=0;

    while(i < m && j < n)
    {
        if(a[i] == b[j])
        {
            result.push_back(a[i]);
            i++;
            j++;
        }

        else if(a[i] < b[j])
        {
            i++;
        }

        else
        {
            j++;
        }
    }

    return result;
}



vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {

    if(nums1.size() <= nums2.size())
        return findIntersection(nums1, nums2);

    else
        return findIntersection(nums2, nums1);

}



// Method-2 --> HashMap --> O(n+m) time  |  O(min(n,m)) space

vector<int> findIntersection2(vector<int>& a, vector<int>& b)
{
    // vector a is smaller than b
    vector<int> result;
    unordered_map<int, int> mp;

    int m = a.size(), n = b.size();

    for(int i=0; i<m; i++)
        mp[a[i]]++;

    for(int j=0; j<n; j++)
    {
        if(mp.find(b[j]) != mp.end() && mp[b[j]] != 0)
        {
            result.push_back(b[j]);
            mp[b[j]]--;
        }
    }

    return result;
}
