// Letter Combinations of a Phone Number

/*

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number
could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below.
Note that 1 does not map to any letters.

    1 - NULL
    2 - abc
    3 - def
    4 - ghi
    5 - jkl
    6 - mno
    7 - pqrs
    8 - tuv
    9 - wxyz

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]

Constraints:

0 <= digits.length <= 4

NOTE: digits[i] is a digit in the range ['2', '9'].

*/


// Method-1 --> Pass by Value

vector<string> result;

vector<string> letterCombinations(string digits) {

    if(digits.empty())
        return {};

    string output;
    getLetterCombinations(output, digits, 0);

    return result;
}


void getLetterCombinations(string output, string digits, int k)
{
    if(output.size() == digits.size())
    {
        result.push_back(output);
        return;
    }

    string characters = getAlphabets(digits[k]);

    for(int j=0; j<characters.size(); j++)
        getLetterCombinations(output + characters[j], digits, k+1);

}

string getAlphabets(char ch)
{
    switch(ch)
    {
        case '2':
            return "abc";
        case '3':
            return "def";
        case '4':
            return "ghi";
        case '5':
            return "jkl";
        case '6':
            return "mno";
        case '7':
            return "pqrs";
        case '8':
            return "tuv";
        case '9':
            return "wxyz";
        default:
            return "";
    }
}



// Method-2 --> Pass by Reference

vector<string> result;

vector<string> letterCombinations(string digits) {

    if(digits.empty())
        return {};

    string output;
    getLetterCombinations(output, digits, 0);

    return result;
}


void getLetterCombinations(string& output, string digits, int k)
{
    if(output.size() == digits.size())
    {
        result.push_back(output);
        return;
    }

    string characters = getAlphabets(digits[k]);

    for(int j=0; j<characters.size(); j++)
    {
        output.push_back(characters[j]);
        getLetterCombinations(output, digits, k+1);
        output.pop_back();
    }

}

string getAlphabets(char ch)
{
    switch(ch)
    {
        case '2':
            return "abc";
        case '3':
            return "def";
        case '4':
            return "ghi";
        case '5':
            return "jkl";
        case '6':
            return "mno";
        case '7':
            return "pqrs";
        case '8':
            return "tuv";
        case '9':
            return "wxyz";
        default:
            return "";
    }
}



// Method-3 --> Without using switch

vector<string> result;
vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

vector<string> letterCombinations(string digits) {

    if(digits.empty())
        return {};

    string output;
    getLetterCombinations(output, digits, 0);

    return result;
}


void getLetterCombinations(string& output, string digits, int k)
{
    if(output.size() == digits.size())
    {
        result.push_back(output);
        return;
    }

    string characters = mapping[digits[k] - '0'];

    for(int j=0; j<characters.size(); j++)
    {
        output.push_back(characters[j]);
        getLetterCombinations(output, digits, k+1);
        output.pop_back();
    }

}
