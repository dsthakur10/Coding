/*
Given an array of DISTINCT integers candidates and a target integer target, return a list of all unique combinations
of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times.
Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations
for the given input.

*/



// Logic is to store every element as many number of times as possible in the array until either sum = target OR
// sum > target. We use a for loop to ensure that every element get a chance to appear in array with every other element

// Method-1 --> Pass by Value

vector<vector<int>> result;

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

    vector<int> output;
    getCombinationSum(candidates, output, 0, 0, target);

    return result;

}

void getCombinationSum(vector<int>& input, vector<int> output, int index, int sum, int target)
{
    if(sum == target)
    {
        result.push_back(output);
        return;
    }

    if(sum > target)
        return;

    for(int i=index; i<input.size(); i++)
    {
        vector<int> op = output;
        op.push_back(input[i]);
        getCombinationSum(input, op, i, sum + input[i], target);    // same index i for repeating elements
    }
}



// Method-2 --> Pass by Reference

vector<vector<int>> result;

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {

    vector<int> output;
    getCombinationSum(candidates, output, 0, 0, target);

    return result;

}

void getCombinationSum(vector<int>& input, vector<int>& output, int index, int sum, int target)
{
    if(sum == target)
    {
        result.push_back(output);
        return;
    }

    if(sum > target)
        return;

    for(int i=index; i<input.size(); i++)
    {
        output.push_back(input[i]);
        getCombinationSum(input, output, i, sum + input[i], target);
        output.pop_back();
    }
}
