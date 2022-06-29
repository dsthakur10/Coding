
vector<vector<int>> result;


// TLE

vector<vector<int>> combine(int n, int k)
{
    vector<int> output;
    vector<int> input;

    for(int i=1; i<=n; i++)
        input.push_back(i);

    getCombinations(input, output, k);
    return result;
}


void getCombinations(vector<int> input, vector<int> output, int k)
{
    if(output.size() == k)
    {
        result.push_back(output);
        return;
    }

    for(int i=0; i<input.size(); i++)
    {
        int x = input[i];
        vector<int> op = output;
        vector<int> ip(input.begin()+i+1, input.end());

        op.push_back(x);

        getCombinations(ip, op, k);

        //input.insert(input.begin()+i, x);
    }
}



// TLE

vector<vector<int>> combine2(int n, int k)
{
    vector<int> output;
    vector<int> input;

    for(int i=1; i<=n; i++)
        input.push_back(i);

    getCombinations(input, output, k, 0);
    return result;
}


void getCombinations2(vector<int> input, vector<int> output, int k, int start)
{
    if(output.size() == k)
    {
        result.push_back(output);
        return;
    }

    for(int i=start; i<input.size(); i++)
    {
        int x = input[i];
        vector<int> op = output;
        op.push_back(x);

        getCombinations(input, op, k, i+1);
    }
}



// Method-3 --> Pass by Value --> Passing without input array

vector<vector<int>> combine3(int n, int k) {

    vector<int> output;
    getCombinations(output, k, 1, n);
    return result;
}


void getCombinations3(vector<int> output, int k, int start, int n)
{
    if(output.size() == k)
    {
        result.push_back(output);
        return;
    }

    for(int i=start; i<=n; i++)
    {
        vector<int> op = output;
        op.push_back(i);

        getCombinations(op, k, i+1, n);
    }
}


// Method-4 --> Pass by reference --> Passing without input array

vector<vector<int>> combine4(int n, int k) {

    vector<int> output;
    getCombinations(output, k, 1, n);
    return result;
}

void getCombinations4(vector<int>& output, int k, int start, int n)
{
    if(output.size() == k)
    {
        result.push_back(output);
        return;
    }

    for(int i=start; i<=n; i++)
    {
        output.push_back(i);

        getCombinations(output, k, i+1, n);

        output.pop_back();
    }
}
