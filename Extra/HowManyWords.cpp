
#include <ctype.h>
#include<bits/stdc++.h>
using namespace std;

vector<string> tokenize(string s);

int main()
{
    string s = "How many eggs 55 66, are! in a half-dozen, 13?";

    vector<string> tokens = tokenize(s);
    for(int i=0; i<tokens.size(); i++)
        cout << tokens[i] << "\n";

    return 0;
}

vector<string> tokenize(string s)
{
    string del = " ";
    vector<string> tokens;
    int start = 0;
    int end = s.find(del);

    while (end != -1)
    {
        string str = s.substr(start, end - start);

        if(str[str.size()-1] == '.' || str[str.size()-1] == '?' || str[str.size()-1] == ',' || str[str.size()-1] == '!')
            str.erase(str.begin() + str.size()-1);

        bool flag = true;
        for(int i=0; i<str.size(); i++)
        {
            if(isdigit(str[i]))
            {
                flag = false;
                break;
            }
        }

        if(flag)
            tokens.push_back(str);

        start = end + del.size();
        end = s.find(del, start);
    }

    //s.substr(start, s.size()-start);
    string str = s.substr(start);

    if(str[str.size()-1] == '.' || str[str.size()-1] == '?' || str[str.size()-1] == ',' || str[str.size()-1] == '!')
        str.erase(str.begin() + str.size()-1);

    bool flag = true;
    for(int i=0; i<str.size(); i++)
    {
        if(isdigit(str[i]))
        {
            flag = false;
            break;
        }
    }

    if(flag)
        tokens.push_back(str);

    return tokens;
}
