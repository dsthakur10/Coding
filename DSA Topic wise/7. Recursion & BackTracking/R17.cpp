
// Unique Permutations

/*

Given a collection of integers nums, that might contain duplicates, return all possible UNIQUE permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output:
[[1,1,2], [1,2,1], [2,1,1]]

*/

#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

vector<vector<int>> result;

void getPermutations(vector<int> input, vector<int> output, set<vector<int>>& myset);
vector<vector<int>> permuteUnique(vector<int>& nums);

void getPermutations2(vector<int>& nums, set<vector<int>>& myset, int start);
vector<vector<int>> permuteUnique2(vector<int>& nums);

vector<vector<int>> permuteUnique3(vector<int>& nums);
void getPermutations3(vector<int> nums, int start);

vector<vector<int>> permuteUnique4(vector<int>& nums);
void getPermutations4(vector<int>& nums, int start);


int main()
{
    vector<int> nums = {1,1,2,2};
    //vector<int> nums = {1,2,1};
    //vector<int> nums = {2,1,1};

    vector<vector<int>> myvec = permuteUnique3(nums);

    for(int i=0; i<myvec.size(); i++)
    {
        for(int j=0; j<myvec[i].size(); j++)
            cout << myvec[i][j] << " ";

        cout << "\n";
    }
}



void getPermutations(vector<int> input, vector<int> output, set<vector<int>>& myset)
{
    if(input.empty())
    {
        myset.insert(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];

        vector<int> op = output;
        op.push_back(x);

        input.erase(input.begin() + i);
        getPermutations(input, op, myset);
        input.insert(input.begin() + i, x);
    }
}



vector<vector<int>> permuteUnique(vector<int>& nums)
{
    set<vector<int>> myset;
    vector<int> output;
    getPermutations(nums, output, myset);

    vector<vector<int>> result(myset.begin(), myset.end());     // alternative of iterating through every element in set & copying

    return result;
}



void getPermutations2(vector<int>& nums, set<vector<int>>& myset, int start)
{
    if(start == nums.size()-1)
    {
        myset.insert(nums);
        return;
    }

    for(int i=start; i<nums.size(); i++)
    {
        swap(nums[start], nums[i]);
        getPermutations2(nums, myset, start+1);
        swap(nums[start], nums[i]);
    }
}


vector<vector<int>> permuteUnique2(vector<int>& nums)
{
    set<vector<int>> myset;
    getPermutations2(nums, myset, 0);

    vector<vector<int>> result(myset.begin(), myset.end());

    return result;
}



// Method-3 -->

vector<vector<int>> permuteUnique3(vector<int>& nums) {

    sort(nums.begin(), nums.end());
    getPermutations3(nums, 0);
    return result;
}


void getPermutations3(vector<int> nums, int start)
{
    if(start == nums.size()-1)
    {
        result.push_back(nums);
        return;
    }

    for(int i=start; i<nums.size(); i++)
    {
        if(start != i && nums[start] == nums[i])
            continue;

        swap(nums[start], nums[i]);
        getPermutations3(nums, start+1);
        //swap(nums[start], nums[i]);
    }
}




vector<vector<int>> permuteUnique4(vector<int>& nums)
{

    getPermutations4(nums, 0);

    return result;

}



void getPermutations4(vector<int>& nums, int start)
{
    if (start == nums.size()-1)
    {
        result.push_back(nums);
        return;
    }

    unordered_set<int> st;
    for (int i = start; i < nums.size(); i++)
    {
        if (st.count(nums[i]) == 1)
            continue;

        st.insert(nums[i]);
        swap(nums[i], nums[start]);
        getPermutations(nums, start + 1);
        swap(nums[i], nums[start]);
    }
}
