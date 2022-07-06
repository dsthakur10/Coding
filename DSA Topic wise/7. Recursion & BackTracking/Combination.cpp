// Combinations


// Method-1 --> Pass by reference

vector<vector<int>> result;

vector<vector<int>> combine(int n, int k) {

    vector<int> output;
    getCombinations(output, 1, n, k);

    return result;
}

void getCombinations(vector<int>& output, int count, int n, int k)
{
    if(output.size() == k)
    {
        result.push_back(output);
        return;
    }

    for(int i=count; i<=n; i++)
    {
        output.push_back(i);
        getCombinations(output, i+1, n, k);
        output.pop_back();
    }

}
