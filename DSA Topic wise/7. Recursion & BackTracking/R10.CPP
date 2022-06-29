
void createPermutations(string output, vector<string>& result, int pos){

    if(output.size()-1 == pos)
    {
        result.push_back(output);
        return;
    }

    string op1 = output;
    string op2 = output;

    op1.insert(pos+1," ");

    createPermutations(op1, result, pos+2);
    createPermutations(op2, result, pos+1);

}


vector<string> permutation(string S)
{
    vector<string> result;

    createPermutations(S, result, 0);

    return result;
}




void createPermutations2(string input, string output, vector<string>& result){

    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    string op1 = output + " " + input[0];
    string op2 = output + input[0];

    input.erase(input.begin());
    createPermutations(input, op1, result);
    createPermutations(input, op2, result);

}

vector<string> permutation2(string S){
    vector<string> result;
    string output(S,0,1);
    S.erase(S.begin());

    createPermutations(S, output, result);

    return result;
}
