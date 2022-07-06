
// Permutations II

// Method-1 --> SET | Space = O(n) * 2 | Pass by value

vector<vector<int>> result;
set<vector<int>> myset;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<int> output;
    getPermutations(nums, output);

    for(auto it = myset.begin(); it != myset.end(); it++)
        result.push_back(*it);

    return result;
}

void getPermutations(vector<int> input, vector<int> output)
{
    if(input.empty())
    {
        myset.insert(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];
        input.erase(input.begin() + i);
        vector<int> op = output;
        op.push_back(x);

        getPermutations(input, op);

        input.insert(input.begin() + i, x);
    }
}



// Method-2 --> SET | Space = O(n) * 2 | Pass by reference

vector<vector<int>> result;
set<vector<int>> myset;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<int> output;
    getPermutations(nums, output);

    for(auto it = myset.begin(); it != myset.end(); it++)
        result.push_back(*it);

    return result;
}

void getPermutations(vector<int>& input, vector<int>& output)
{
    if(input.empty())
    {
        myset.insert(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];
        input.erase(input.begin() + i);
        output.push_back(x);

        getPermutations(input, output);

        input.insert(input.begin() + i, x);
        output.pop_back();
    }
}



// Method-3 --> SET | Inplace | Space = O(n) | Pass by reference


vector<vector<int>> result;
set<vector<int>> myset;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    vector<int> output;
    getPermutations(nums, 0);

    for(auto it = myset.begin(); it != myset.end(); it++)
        result.push_back(*it);

    return result;
}

void getPermutations(vector<int>& input, int k)
{
    if(k == input.size()-1)
    {
        myset.insert(input);
        return;
    }

    for(int i=k; i<input.size(); i++)
    {
        swap(input[i], input[k]);
        getPermutations(input, k+1);
        swap(input[i], input[k]);
    }
}



// Method-4 --> WITHOUT SET | Inplace | Space = O(1) | Pass by value

vector<vector<int>> result;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
    getPermutations(nums, 0);

    return result;
}

void getPermutations(vector<int> input, int k)
{
    if(k == input.size()-1)
    {
        result.push_back(input);
        return;
    }

    for(int i=k; i<input.size(); i++)
    {
        if(i == k || input[i] != input[k])
        {
            swap(input[i], input[k]);
            getPermutations(input, k+1);
        }
    }

}



// Method-5 --> WITHOUT SET | Inplace | Space = O(1) | Pass by reference
// Notice that, we will be required to restore the state of input vector before recursive call returns.

vector<vector<int>> result;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
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
        if(i == k || input[i] != input[k])
        {
            swap(input[i], input[k]);
            getPermutations(input, k+1);
        }
    }

    for(int i=input.size()-1; i>k; i--)
        swap(input[i], input[k]);
}



// Method-6 --> unordered_set to track repeated elements

vector<vector<int>> result;

vector<vector<int>> permuteUnique(vector<int>& nums)
{
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

    unordered_set<int> us;

    for(int i=k; i<input.size(); i++)
    {
        if(us.count(input[i]) == 0)
        {
            swap(input[i], input[k]);
            getPermutations(input, k+1);
            swap(input[i], input[k]);
        }

        us.insert(input[i]);
    }
}
