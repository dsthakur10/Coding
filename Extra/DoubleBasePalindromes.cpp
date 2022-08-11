
#include<bits/stdc++.h>
using namespace std;

int solve(int number);
string decimalToBinary(int decimal);
bool checkPalindrome(string str);


int main()
{
    int number = 585;
    cout << solve(number);
}



string decimalToBinary(int decimal)
{
    string binary;
    int rem;
    while(decimal > 0)
    {
        rem = decimal%2;
        decimal /= 2;
        binary += to_string(rem);
    }

    return binary;
}

bool checkPalindrome(string str)
{
    int i=0, j=str.size()-1;

    while(i < j)
    {
        if(str[i] != str[j])
            return false;

        i++;
        j--;
    }

    return true;
}


// Method-1 --> Brute-force
int solve(int number)
{
    int count = 0;
    for(int i=1; i<=number; i++)
    {
        string str = decimalToBinary(i);

        if(checkPalindrome(str))
            count++;
    }

    return count;
}


// Method-2 --> recursively create palindromic string
int solve(int number)
{
    vector<string> result;

    if(number < 3)
        return 1;

    if(number == 3)
        return 2;

    result.push_back('1');
    result.push_back('11');

    helper(result);
}

int helper(vector<string>& result)
{
    int i=0; i<

}
