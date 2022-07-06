/*

Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations
in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

NOTE: The solution set must not contain duplicate combinations.

Numbers in the array may not be distinct

*/


// Method-1 --> Space = O(1) --> Using array indices

vector<vector<int>> result;

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

    vector<int> output;
    sort(candidates.begin(), candidates.end());
    getCombinationSum2(candidates, output, 0, 0, target);

    return result;

}


void getCombinationSum2(vector<int>& input, vector<int>& output,
                        int index, int sum, int target)
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
        if(i > index && input[i] == input[i-1])
            continue;

        output.push_back(input[i]);
        getCombinationSum2(input, output, i+1, sum + input[i], target);
        output.pop_back();
    }
}



// Method-2 --> Using local HashSet to keep track of repeated elements

vector<vector<int>> result;

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {

    vector<int> output;
    sort(candidates.begin(), candidates.end());
    getCombinationSum2(candidates, output, 0, 0, target);

    return result;

}


void getCombinationSum2(vector<int>& input, vector<int>& output,
                        int index, int sum, int target)
{
    if(sum == target)
    {
        result.push_back(output);
        return;
    }

    if(sum > target)
        return;

    unordered_set<int> us;

    for(int i=index; i<input.size(); i++)
    {
        if(us.find(input[i]) != us.end())
            continue;

        us.insert(input[i]);

        output.push_back(input[i]);
        getCombinationSum2(input, output, i+1, sum + input[i], target);
        output.pop_back();
    }
}
