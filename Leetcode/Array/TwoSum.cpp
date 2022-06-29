vector<int> twoSum(vector<int>& nums, int target)
{
    int n = nums.size();
    unordered_multimap<int,int> mp;

    for(int i=0; i<n; i++)
        mp.insert(make_pair(nums[i], i));

    sort(nums.begin(), nums.end());

    int i=0, j=n-1;

    while(i<j)
    {
        if(nums[i] + nums[j] < target)
            i++;

        else if(nums[i] + nums[j] > target)
            j--;

        else
            break;
    }

    if(nums[i] == nums[j])
    {
        auto range = mp.equal_range(nums[i]);
        auto it = range.first;

        int x = it->second;
        it++;
        int y = it->second;

        return {x,y};
    }

    else
    {
        return {mp.find(nums[i])->second, mp.find(nums[j])->second};
    }

}


vector<int> twoSum(vector<int>& nums, int target)
{
    unordered_map<int,int> mp;

    int n = nums.size();

    for(int i=0; i<n; i++)
    {
        int toFind = target - nums[i];

        if(mp.find(toFind) != mp.end())
            return {i, mp[toFind]};

        else
            mp[nums[i]] = i;
    }

    return {};
}
