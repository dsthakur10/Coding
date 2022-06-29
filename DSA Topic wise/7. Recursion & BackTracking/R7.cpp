// print powerset

#include<iostream>
#include<string>
#include<vector>

using namespace std;

vector<string> result;

void printPowerSet(string input, string output)
{
    if(input.empty())
    {
        result.push_back(output);
        return;
    }

    string s1 = output;
    string s2 = output + input[0];

    input.erase(input.begin());

    printPowerSet(input, s1);
    printPowerSet(input, s2);
}

//Function to return the lexicographically sorted power-set of the string.
vector <string> powerSet(string s)
{
    printPowerSet(s, "");

    return result;
}



int main()
{
    string input;

    cout << "Enter your string to find powerset: ";
    cin >> input;

    vector<string> myvec = powerSet(input);

    for(int i=0; i<myvec.size(); i++)
        cout << myvec[i] << " ";
}
