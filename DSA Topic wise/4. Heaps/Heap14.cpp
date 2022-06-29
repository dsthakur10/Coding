/*

FREQUENCY SORT

Given an array of integers nums, sort the array in decreasing order based on the frequency of the values.

Return the sorted array.

    - Relative order of array is not maintained
    - No tie-breaker

Input: [1,1,1,3,2,2,4]
Output: [1,1,1,2,2,3,4] / [1,1,1,2,2,4,3]

*/


#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
typedef std::pair<int,int> pi;


std::vector<int> frequencySort(std::vector<int>& nums);


int main()
{
    //std::vector<int> vec = {3,2,3,1,2,4,5,5,6};
    std::vector<int> vec;
    int n,k;

    std::cout<< "Enter size of array: ";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0;i<n;i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }


    std::cout << "\nArray:\n";
    for(int i=0;i<n;i++)
        std::cout << vec[i] << " ";

    vec = frequencySort(vec);

    std::cout << "\nFrequency sort: ";

    for(int i=0;i<vec.size();i++)
        std::cout << vec[i] << " ";

    return 0;

}



std::vector<int> frequencySort(std::vector<int>& nums)
{
    std::unordered_map<int,int> mp;
    std::priority_queue<pi> pq;
    std::vector<int> vec;

    for(int i=0; i<nums.size(); i++)
        mp[nums[i]]++;

    for(auto it = mp.begin(); it != mp.end(); it++)             // sorting based on frequency--> maximum frequency first
        pq.push(std::make_pair(it->second, it->first));

    while(!pq.empty())
    {
        int counter = pq.top().first;
        while(counter > 0)
        {
            vec.push_back(pq.top().second);
            counter--;
        }

        pq.pop();
    }

    return vec;
}

