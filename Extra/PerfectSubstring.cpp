
#include<bits/stdc++.h>
using namespace std;

int solve(string s, int k);

int main()
{
    string s = "1102021222";
    int k = 2;

    cout << "Number of perfect substrings = " << solve(s, k);
}


int solve(string s, int k)
{
    unordered_map<char, int> mp;        // <number, freq>
    int n = s.size();
    int result = 0;

    // "check counter #unique chars to be repeated k times in window"
    // window size = counter*k

    for(int counter = 1; counter <= 10; counter++)
    {
        int check = 0;
        int window = counter*k;
        int i=0, j=0;

        while(j < n)
        {
            mp[s[j]]++;
            if(mp[s[j]] == k)
                check++;

            if(j-i+1 < window)
                j++;

            else if(j-i+1 == window)
            {
                if(check == counter)
                {
                    result++;
                    //cout << i << "\n";
                }

                mp[s[i]]--;

                if(mp[s[i]] < k)
                    check--;

                i++;
                j++;
            }
        }

        cout << "counter = " << counter << " result = " << result << "\n";
    }

    return result;
}
