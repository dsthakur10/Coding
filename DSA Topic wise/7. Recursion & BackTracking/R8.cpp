
// Subsets

/*

Given an integer array nums of UNIQUE ELEMENTS, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:

Input: nums = [0]
Output: [[],[0]]


*/


vector<vector<int>> result;


// Method-1  Recursion

void addSubset(vector<int> input, vector<int> output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

/*
    vector<int> op1 = output;
    vector<int> op2 = output;
    op2.push_back(input[0]);

    input.erase(input.begin());

    addSubset(input, op1);
    addSubset(input, op2);
*/

    int x = input[0];
    input.erase(input.begin());

    addSubset(input, output);
    output.push_back(x);
    addSubset(input, output);
}


vector<vector<int>> subsets(vector<int>& nums) {

    vector<int> output;

    addSubset(nums, output);

    return result;
}




// Method-2 Cascading method

vector<vector<int>> subsets2(vector<int>& nums)
{
    vector<vector<int>> result;
    vector<int> temp;

    result.push_back({});

    for(int i=0; i<nums.size(); i++)
    {
        int n = result.size();
        for(int j=0; j<n; j++)
        {
            temp = result[j];
            temp.push_back(nums[i]);
            result.push_back(temp);
            temp.clear();
        }
    }

    return result;
}


