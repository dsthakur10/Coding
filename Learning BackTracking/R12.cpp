
// LetterCase Permutation

/*
Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.

Return a list of all possible strings we could create. Return the output in any order.

Example 1:
Input: s = "a1b2"
Output: ["a1b2", "a1B2", "A1b2", "A1B2"]

Example 2:
Input: s = "3z4"
Output: ["3z4", "3Z4"]

*/


vector<string> result;

vector<string> letterCasePermutation(string s)
{
    string output;

    createPermutations(s, output);

    return result;
}


void createPermutations(string input, string output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    char ch = input[0];
    input.erase(input.begin());

    if(!isdigit(ch))
    {
        string op1 = output + (char)tolower(ch);
        string op2 = output + (char)toupper(ch);

        createPermutations(input, op1);
        createPermutations(input, op2);
    }

    else
    {
        string op = output + ch;
        createPermutations(input, op);
    }
}

