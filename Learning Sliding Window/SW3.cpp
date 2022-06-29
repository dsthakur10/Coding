/*

COUNT OCCURRENCES OF ANAGRAMS           (FIND ALL ANAGRAMS OF GIVEN WORD IN CERTAIN TEXT)

Given a word and a text, return the count of the occurrences of anagrams of the word in the text
    For eg: anagrams of word "for" --> for, ofr, rof , fro, orf, rfo


Input : forxxorfxdofr
        for
Output : 3

Explanation : Anagrams of the word for - for, orf, ofr appear in the text and hence the count is 3.


Input : aabaabaa
        aaba
Output : 4

Explanation : Anagrams of the word aaba - aaba, abaa each appear twice in the text and hence the count is 4.

*/


#include<climits>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
#include<unordered_map>


int countAnagrams(std::string text, std::string word);              // BRUTE FORCE --> Time = O(n*k^2)  --> every k-length substring of "text" is checked for anagram in "word"
                                                                    // (n-k) times this is done. Work done for 1 comparison = k^2

int countAnagrams2(std::string text, std::string word);


int main()
{
    std::string s1,s2;

    std::cout << "Enter string text: ";
    std::cin >> s1;

    std::cout << "\nEnter string to find its anagrams: ";
    std::cin >> s2;

    std::cout << "\n\nText = "<< s1;
    std::cout << "\nSample string = " << s2;

    int counter = countAnagrams2(s1,s2);

    std::cout << "\nNumber of anagrams = " << counter;
}



int countAnagrams(std::string text, std::string word)
{
    std::vector<int> vec;
    int n = text.size();
    int k = word.size();
    int counter = 0, temp;
    std::string str;

    for(int i=0; i<n-k+1; i++)
    {
        temp = 0;
        str = word;
        for(int j=i; j<i+k; j++)
        {
            for(int x=0; x<k; x++)
            {
                if(text[j] == str[x])
                {
                    str.erase(x,1);
                    temp++;
                    break;
                }
            }
        }

        if(temp == k)
        {
            counter++;
            //std::cout << " " << i;
            vec.push_back(i);
        }

    }

    //return vec;
    return counter;
}



// ------------------ Method-2 -------------------

/*
    Anagram is nothing but permutation of given word. Hence we cannot find k! words & check every k-size substring with them.
    What we can do is store 2 information: (1) #Distinct letters (2) Count of each letter ---> Unordered_map

    Now we have stored every letter of given word. Traverse through the text & for every k-length substring, if text[j] belongs to map,
    keep decrementing the count of letters in map. Also increment the count of text[i] if it belongs to map, once the window is slided.
    Once all the keys of map shows 0 mapped value --> we have found our anagram.

    Can we improve the time complexity ? YES --> use a counter variable to help reduce unnecessary traversals to map to check for 0 values of all elements.
    Initially counter = map.size() - Counter is decremented when a certain map element's frequency becomes 0. It is again incremented if the frequency becomes 1.

    In a particular sliding window, if counter==0 --> anagram is found.

    At the time of sliding the window, reverse the calculation done for the ith index. Increment the key text[i]'s mapped value & if it equals 1 --> increment counter

*/

int countAnagrams2(std::string text, std::string word)
{
    std::vector<int> vec;
    int n = text.size();
    int k = word.size();
    int i, j,anagram = 0;

    std::unordered_map<char,int> mp;            // to store <letter, frequency>
    int counter;                                // to let us not traverse the map repeatedly --> stores map size

    for(int i=0; i<k; i++)
        mp[word[i]]++;

    counter = mp.size();

    i = 0;
    j = 0;
    std::unordered_map<char,int>::iterator it = mp.begin();

    while(j < n)
    {
        /*
        it = mp.find(text[j]);          // find the desired key's location in map. If key not found, returns mp.end()

        if(it != mp.end())
        */

        if(mp.count(text[j]))           // returns 1 if key present, else returns 0
        {
            mp[text[j]]--;

            if(mp[text[j]] == 0)
                counter--;
        }

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)                             // writing "else" does not give same results. You must use "else if()"
        {
            if(counter == 0)
            {
                anagram++;
                vec.push_back(i);
            }

            /*
            it = mp.find(text[i]);

            if(it != mp.end())
            */

            if(mp.count(text[i]))                       // undone the calculation at ith index
            {
                mp[text[i]]++;

                if(mp[text[i]] == 1)
                    counter++;
            }

            i++;
            j++;
        }

    }

    return anagram;
    // return vec;

}


// Method-3 --> vector of alphabets

vector<int> findAnagrams(string s, string p) {

    if(p.length() > s.length())
        return {};

    int letters[26];

    int counter;
    vector<int> index;

    int n = s.length();
    int k = p.length();
    counter = k;

    for(int i=0; i<26; i++)
        letters[i] = 0;

    for(int i=0; i<k; i++)
        letters[p[i] - 'a']++;

    int x,i=0;

    while(i<k)
    {
        x = s[i] - 'a';
        letters[x]--;

        if(letters[x] >= 0)
            counter--;

        i++;
    }

    if(counter == 0)
        index.push_back(0);

    for(int i=k; i<n; i++)
    {
        x = s[i] - 'a';
        letters[x]--;

        if(letters[x] >= 0)
            counter--;

        x = s[i-k] - 'a';
        letters[x]++;

        if(letters[x] > 0)
            counter++;

        if(counter == 0)
            index.push_back(i-k+1);
    }

    return index;
}
