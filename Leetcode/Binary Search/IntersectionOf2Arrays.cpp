// Duplicates NOT allowed


vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {

    if(nums1.size() <= nums2.size())
        return findIntersection(nums1, nums2);

    else
        return findIntersection(nums2, nums1);

}




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
            if(result.empty() || result.back() != a[i])
            {
                result.push_back(a[i]);
            }

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




vector<int> findIntersection2(vector<int>& a, vector<int>& b)
{
    // vector a is smaller than b

    vector<int> result;
    unordered_set<int> se;

    int m = a.size(), n = b.size();

    for(int i=0; i<m; i++)
        se.insert(a[i]);

    // unordered_set<int> se(a.begin(), a.end());


    for(int j=0; j<n; j++)
    {
        if(se.find(b[j]) != se.end())
        {
            result.push_back(b[j]);
            se.erase(b[j]);
        }
    }

    return result;
}

