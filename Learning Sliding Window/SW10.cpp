// Count #substrings with atmost K-distinct characters

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

int substringWithAtmostKDistinct(string str, int k);
int substringWithAtmostKDistinct2(string str, int k);

int main()
{
    //string s = "ababc";
    string s = "aabcbcdbca";
    int k;

    cout << "Enter k-value : ";
    cin >> k;
    int counter = substringWithAtmostKDistinct(s, k);
    cout << "\n" << counter;

    counter = substringWithAtmostKDistinct2(s, k);
    cout << "\n" << counter;
    return 0;
}


// Current Window size (j-i+1) denotes --> #subarrays ending at index j (with unique digits <= k)
// Total #subarrays for a given window = j-i+1
// Calculation of answer (number += j-i+1) is necessary even in else part because without this,
// we would be skipping many valid answers.


int substringWithAtmostKDistinct(string s, int k)
{
    unordered_map<char, int> mp;
    int number = 0;
    int i=0, j=0;

    while(j < s.size())
    {
        mp[s[j]]++;

        if(mp.size() <= k)
        {
            number += j-i+1;
            j++;
        }

        else
        {
            while(mp.size() > k)
            {
                mp[s[i]]--;

                if(mp[s[i]] == 0)
                    mp.erase(s[i]);
                i++;
            }

            number += j-i+1;
            j++;
        }
    }

    return number;
}




int substringWithAtmostKDistinct2(string s, int k)
{
    unordered_map<char, int> mp;
    int number = 0;
    int i=0, j=0;

    while(j < s.size())
    {
        mp[s[j]]++;

        if(mp.size() <= k)
        {
            j++;
        }

        else
        {
            while(mp.size() > k)
            {
                mp[s[i]]--;

                if(mp[s[i]] == 0)
                    mp.erase(s[i]);
                i++;
            }

            j++;
        }

        number += j-i;
    }

    return number;
}
