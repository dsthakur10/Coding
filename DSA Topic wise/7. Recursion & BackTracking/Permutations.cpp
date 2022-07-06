// Permutations

/*

Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order.

*/


// Method-1 --> Space = O(n) --> Pass by value


vector<vector<int>> result;

vector<vector<int>> permute(vector<int>& nums)
{
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



// Method-2 --> Space = O(n) --> Pass by reference

vector<vector<int>> result;

vector<vector<int>> permute(vector<int>& nums) {

    vector<int> output;
    getPermutations(nums, output);

    return result;
}

void getPermutations(vector<int>& input, vector<int>& output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];

        output.push_back(x);
        input.erase(input.begin() + i);

        getPermutations(input, output);

        output.pop_back();
        input.insert(input.begin() + i, x);
    }
}



// Method-3 --> Inplace | space = O(1) --> Pass by reference

vector<vector<int>> result;

vector<vector<int>> permute(vector<int>& nums) {

    getPermutations(nums, 0);

    return result;
}

void getPermutations(vector<int>& input, int k)
{
    if(k == input.size()-1)
    {
        result.push_back(input);
        return;
    }

    for(int i=k; i<input.size(); i++)
    {
        swap(input[k], input[i]);
        getPermutations(input, k+1);
        swap(input[k], input[i]);
    }
}
