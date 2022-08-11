
// Number of Substrings Containing All Three Characters

/*

Given a string s consisting ONLY of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are
"abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

Example 2:
Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are
"aaacb", "aacb" and "acb".

Example 3:
Input: s = "abc"
Output: 1

*/


// Method-1 --> #substrings having unique-characters <= k - #substrings having unique-characters <= (k-1)

// Since we know, the strings has only 3 unique characters, #substrings having unique-characters <= 3 = n(n+1)/2
// (Basically include every non-empty substring)
// Only need to find #substrings with unique characters <= 2


int numberOfSubstrings(string s) {

    int n = s.size();
    int total;

    total = (long)n*(n+1)/2;        // n*n+1 might cause overflow --> typecast int n to long n

    return total - substringWithAtmostKCharacters(s, 2);
}


int substringWithAtmostKCharacters(string s, int k)
{
    unordered_map<char, int> mp;
    int number = 0;
    int i=0, j=0;

    while(j < s.size())
    {
        mp[s[j]]++;

        if(mp.size() <= k)
            j++;

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



// Method-2

// Logic is to keep counts of a,b,c
// Check if all the characters count >= 1 --> Beyond this last index where we get frequency of all elements >= 1,
// Every substring is to be counted in final answer (as it will contain atleast 1 a,b,c in every follow up strings)

/*
    1. Create count[3] vector for keeping track of all the letters --> a,b,c
    2. Keep incrementing window until you find every character count >= 1
    3. While count >= 1 for all, add (n-1) - j + 1 (All substrings covering mandatory [i,j]+other till end of string)
    4. Decrement window & undo the work.
*/

int numberOfSubstrings(string s) {
    int n = s.size();
    vector<int> count(3,0);
    int number = 0;

    int i=0, j=0;

    while(j < n)
    {
        count[s[j] - 'a']++;

        if(count[0] < 1 || count[1] < 1 || count[2] < 1)
            j++;

        else
        {
            while(count[0] >= 1 && count[1] >= 1 && count[2] >= 1)
            {
                number += n-j;
                count[s[i] - 'a']--;
                i++;
            }
            j++;
        }

    }

    return number;
}




// Method-3 --> Maintain last occurrence of each character

/*

Take three pointers l1, l2, l3 to keep track of last occurrences of a, b and c.
Now as you iterate over the string of length n, you can count the number of sub-strings ending at that particular
index. How can we do that is here ->

    1. Keep on updating l1, l2 and l3.
    2. And take the minimum of l1, l2 and l3.
    3. Now from this min-index (min(l1, l2, l3)) to the curr index i this is the smallest possible sub-string
        ending at curr-index i which follows the constraint.
    4. If the smallest sub-string is from min-index to curr-index, then for every sub-string starting from
        index 0,1, 2, 3, ......min-index and ending at curr-index is valid,
        (So how many are these...... So there are min-index + 1 sub-strings)
    5. Add this min-index + 1 to the count.

*/

int numberOfSubstrings(string s)
{
    vector<int> last(3,-1);
    int number = 0;

    for(int i=0; i<s.size(); i++)
    {
        last[s[i] - 'a'] = i;

        int x = min(last[0], min(last[1], last[2]));
        number += 1 + x;
    }

    return number;
}
