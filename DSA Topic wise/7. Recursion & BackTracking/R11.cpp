
// Permutation with case change

/*
Print all permutations of a string keeping the sequence but changing cases.

Examples:

Input : ab
Output : AB Ab ab aB

Input : ABC
Output : abc Abc aBc ABc abC AbC aBC ABC

*/


#include<iostream>
#include<vector>
#include<string>

using namespace std;


void createPermutations(string input, string output, vector<string>& result);
vector<string> permutationWithCaseChange(string S);


int main()
{
    string input;
    cout << "Enter the string: ";
    cin >> input;

    vector<string> result = permutationWithCaseChange(input);

    cout << "\nPermutations = ";
    for(int i=0; i<result.size(); i++)
        cout << result[i] << " ";

    return 0;
}


void createPermutations(string input, string output, vector<string>& result){

    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    string op1 = output + (char)tolower(input[0]);
    string op2 = output + (char)toupper(input[0]);

    input.erase(input.begin());
    createPermutations(input, op1, result);
    createPermutations(input, op2, result);

}


vector<string> permutationWithCaseChange(string S){
    vector<string> result;
    string output;

    createPermutations(S, output, result);

    return result;
}
