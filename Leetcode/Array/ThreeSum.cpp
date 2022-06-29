#include <bits/stdc++.h>
using namespace std;

struct hashFunction
{
    size_t operator()(const pair<int,int> &x) const
    {
        return x.first ^ x.second;
    }
};


vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> result;
    vector<int> single;
    int n = nums.size();
    unordered_set<pair<int,int>, hashFunction> st;
    //unordered_map<int,int> mp;

    sort(nums.begin(), nums.end());
    for(int k=0; k<n-2; k++)
    {
        int target = 0 - nums[k];

        int i = k+1;
        int j = n-1;

        while(i < j)
        {
            if(nums[i] + nums[j] < target)
                i++;

            else if(nums[i] + nums[j] > target)
                j--;

            else
            {
                pair<int,int> pi = make_pair(nums[i], nums[j]);

                if(st.find(pi) == st.end())
                //if(mp.find(nums[i])==mp.end() || mp[nums[i]] != nums[j])
                {

                    single.push_back(nums[i]);
                    single.push_back(nums[j]);
                    single.push_back(nums[k]);

                    result.push_back(single);

                    st.insert(pi);
                    //mp[nums[i]] = nums[j];

                    single.clear();

                }

                i++;
                j--;

            }
        }
    }

    return result;
}



vector<vector<int>> threeSum2(vector<int>& nums)
{

    vector<vector<int>> result;
    vector<int> single;
    int n = nums.size();

    sort(nums.begin(), nums.end());
    for(int k=0; k<n-2; k++)
    {
        int target = 0 - nums[k];

        int i = k+1;
        int j = n-1;

        while(i < j)
        {
            if(nums[i] + nums[j] < target)
                i++;

            else if(nums[i] + nums[j] > target)
                j--;

            else
            {
                single.push_back(nums[i]);
                single.push_back(nums[j]);
                single.push_back(nums[k]);

                result.push_back(single);
                single.clear();

                i++;
                j--;

                while(i < j && nums[i] == nums[i-1])     // processing duplicates of num[i]
                    i++;

                while(i < j && nums[j] == nums[j+1])     // processing duplicates of nums[j]
                    j--;
            }
        }

        while(k < n-3 && nums[k] == nums[k+1])
            k++;
    }

    return result;
}



int main()
{
    vector<int> vec = {-1,0,1,2,-1,-4};

    vector<vector<int>> result = threeSum(vec);

    for(int i=0; i<result.size(); i++)
    {
        for(int j=0; j<result[i].size(); j++)
            std::cout << result[i][j] << " ";

        cout << endl;
    }

    return 0;
}
