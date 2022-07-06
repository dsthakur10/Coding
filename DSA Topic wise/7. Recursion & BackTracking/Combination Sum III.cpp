/*

Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice,
and the combinations may be returned in any order.

*/



// Using k numbers (EXACTLY), generate sum of n
vector<vector<int>> result;

vector<vector<int>> combinationSum3(int k, int n) {

    vector<int> output;
    getCombinationSum3(output, k , n, 1);

    return result;
}

void getCombinationSum3(vector<int>& output, int k, int n, int index)
{
    if(n == 0 && k == 0)
    {
        result.push_back(output);
        return;
    }

    if(n < 0 || k < 0)
        return;

    for(int i=index; i<=9; i++)
    {
        if(i > n)                   // to avoid unnecessary looping
            continue;

        output.push_back(i);
        getCombinationSum3(output, k-1 , n-i, i+1);
        output.pop_back();
    }
}
