// Subsets II

/*

Given an integer array nums that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

*/



// Method-1 --> Additional space of set | NOT space optimized (pass by value)

vector<vector<int>> result;
set<vector<int>> myset;

vector<vector<int>> subsetsWithDup(vector<int>& nums) {

    vector<int> output;
    sort(nums.begin(), nums.end());
    addSubsets(nums, output);

    for(auto it = myset.begin(); it != myset.end(); it++)
        result.push_back(*it);

    return result;
}

void addSubsets(vector<int> input, vector<int> output)
{
    if(input.empty())
    {
        myset.insert(output);
        return;
    }

    int x = input[0];
    input.erase(input.begin());

    addSubsets(input, output);
    output.push_back(x);
    addSubsets(input, output);
}



// Method-2 --> Additional space of set | space optimized (pass by reference)

vector<vector<int>> result;
set<vector<int>> myset;

vector<vector<int>> subsetsWithDup(vector<int>& nums) {

    vector<int> output;
    sort(nums.begin(), nums.end());
    addSubsets(nums, output);

    for(auto it = myset.begin(); it != myset.end(); it++)
        result.push_back(*it);

    return result;
}

void addSubsets(vector<int>& input, vector<int>& output)
{
    if(input.empty())
    {
        myset.insert(output);
        return;
    }

    int x = input[0];
    input.erase(input.begin());

    addSubsets(input, output);
    output.push_back(x);
    addSubsets(input, output);

    input.insert(input.begin(), x);
    output.pop_back();
}



// Method-3 --> WITHOUT set | space optimized (pass by reference)

// The below shown method fails because we remove all the duplicate entries leaving only a single copy for
// each duplicate entry. This won't let us make subset with duplicate elements like : {1,2,2} or {2,2}

/*

    int x = input[0];
    int count = 0;
    while(!input.empty() && x == input[0])
    {
        count++;
        input.erase(input.begin());
    }

    addSubsets(input, output);
    output.push_back(x);
    addSubsets(input, output);

    while(count > 0)
    {
        input.insert(input.begin(), x);
        count--;
    }
    output.pop_back();

*/


vector<vector<int>> result;

vector<vector<int>> subsetsWithDup(vector<int>& nums) {

    vector<int> output;
    sort(nums.begin(), nums.end());
    addSubsets(nums, output, 0);

    return result;
}

void addSubsets(vector<int>& nums, vector<int>& output, int index)
{
    result.push_back(output);

    int i = index;
    int n = nums.size();
    while(i < n)
    {
        if(i != index && i > 0 && nums[i] == nums[i-1])
        {
            i++;
            continue;
        }

        output.push_back(nums[i]);
        addSubsets(nums, output, i+1);
        output.pop_back();
        i++;
    }
}



// Method-4 --> Iterative (CASCADING)
