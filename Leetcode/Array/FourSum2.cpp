#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// TIME LIMIT EXCEEDED - O(N^3)
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
    unordered_map<int, int> mp;
    int counter=0;

    for(int x : nums4)          // <element, frequency> of array4
        mp[x]++;

    for(int i : nums1)
    {
        for(int j : nums2)
        {
            for(int k : nums3)
            {
                int target = 0 - i - j - k;

                if(mp.find(target) != mp.end())
                {
                    counter += mp[target];
                }
            }
        }
    }

    return counter;
}


// O(N^2)
int fourSumCount2(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
{
    unordered_map<int, int> mp;
    int counter=0;

    for(int k : nums3)          // <sum, frequency> of array3 & array4
    {
        for(int l : nums4)
        {
            int sum = k + l;
            mp[sum]++;
        }
    }

    for(int i : nums1)
    {
        for(int j : nums2)
        {
            int target = 0 - i - j;

            if(mp.find(target) != mp.end())
            {
                counter += mp[target];
            }
        }
    }

    return counter;
}
