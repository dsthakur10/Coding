/*
PICK TOYS

John wants to purchase toys from toy store. Toys are arranged in the shop in queue.
John's mom agreed to buy him as many toys as he wants with 2 given conditions:
    1. He can only pick toys in order from the queue (No random picking allowed).
    2. He can only pick 2 types of toys, no matter how many instances of these 2 types.

You have to determine the maximum #toys John can pick with the above 2 constraints
*/


#include<iostream>
#include<algorithm>
#include<string>
#include<unordered_map>
using namespace std;


int findMaxToys(string str);

int main()
{
    string str = "abaccab";
    string str2 = "aabacbebebe";

    int maxToys = findMaxToys(str2);

    cout << "\nMaximum #toys = " << maxToys;

    return 0;
}


// Convert the given question into "find longest possible substring that has exactly K unique characters" with K=2

int findMaxToys(string str)
{
    unordered_map<char, int> mp;
    int i=0, j=0, sum = 0, length = 0 ;

    while(j < str.size())
    {
        mp[str[j]]++;
        sum++;

        if(mp.size() < 2)
            j++;

        else if(mp.size() == 2)
        {
            length = max(length, sum);
            j++;
        }

        else
        {
            while(mp.size() > 2)
            {
                mp[str[i]]--;
                sum--;

                if(mp[str[i]] == 0)
                    mp.erase(str[i]);
                i++;
            }

            j++;
        }
    }

    cout << "\n\n Toys rack = " << str;
    return length;
}
