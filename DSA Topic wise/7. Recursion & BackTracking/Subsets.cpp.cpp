// Subsets

/*

Given an integer array nums of unique elements, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

*/


// Method-1 --> CASCADING

vector<vector<int>> subsets(vector<int>& nums) {

    vector<vector<int>> result;
    vector<int> subset;

    result.push_back({});
    for(int i=0; i<nums.size(); i++)
    {
        int n = result.size();
        for(int j=0; j<n; j++)
        {
            subset = result[j];
            subset.push_back(nums[i]);
            result.push_back(subset);
        }
    }

    return result;
}


// Method-2 Backtracking (pass by value) | NOT OPTIMIZED

vector<vector<int>> result;

vector<vector<int>> subsets(vector<int>& nums) {

    getSubsets(nums, {});

    return result;
}

void getSubsets(vector<int> input, vector<int> output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    int x = input[0];
    input.erase(input.begin());

    getSubsets(input, output);
    output.push_back(x);
    getSubsets(input, output);
}



// Method-3 --> Backtracking (pass by reference) | optimized

vector<vector<int>> result;

vector<vector<int>> subsets(vector<int>& nums) {

    vector<int> output;
    getSubsets(nums, output);

    return result;
}

void getSubsets(vector<int>& input, vector<int>& output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    int x = input[0];
    input.erase(input.begin());

    getSubsets(input, output);
    output.push_back(x);
    getSubsets(input, output);

    // backtrack
    output.pop_back();
    input.insert(input.begin(), x);
}



// Method-4 --> Backtracking (pass by reference) | best Space optimized
// No deleting of elements from INPUT vector

// Logic is to keep index from where to print next subset --> Increment this index at every call


vector<vector<int>> result;

vector<vector<int>> subsets(vector<int>& nums)
{
    vector<int> output;
    addSubsets(nums, 0, output);

    return result;
}


void addSubsets(vector<int>& nums, int k, vector<int>& output)
{
    result.push_back(output);

    for (int j = k; j < nums.size(); j++)
    {
        output.push_back(nums[j]);
        addSubsets(nums, j + 1, output);
        output.pop_back();
    }
}
