
// Permutations

/*

Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

Example 1:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

*/


vector<vector<int>> result;


// Method-1 --> Filling the output array from size 0 to input.size()

vector<vector<int>> permute(vector<int>& nums) {

    vector<int> output;

    getPermutations(nums, output);

    return result;

}


void getPermutations(vector<int> input, vector<int> output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];
        vector<int> op = output;
        op.push_back(x);

        input.erase(input.begin() + i);
        getPermutations(input, op);
        input.insert(input.begin() + i, x);
    }
}



// Method-2 --> Solving inplace just by swapping numbers in every recursive call
// No need to create & pass separate array in every call --> space optimized

vector<vector<int>> permute2(vector<int>& nums) {

    getPermutations(nums, 0);

    return result;

}


void getPermutations2(vector<int>& input, int start)
{
    if(start == input.size()-1)
    {
        result.push_back(input);
        return;
    }

    for(int i=start; i<input.size(); i++)
    {
        swap(input[start], input[i]);

        getPermutations(input, start+1);

        swap(input[start], input[i]);
    }
}
