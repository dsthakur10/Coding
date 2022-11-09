/*

Given a string s, reverse only all the vowels in the string and return it.

The vowels are 'a', 'e', 'i', 'o', and 'u', and they can appear in both lower and upper cases, more than once.

Example 1:
Input: s = "hello"
Output: "holle"

Example 2:
Input: s = "leetcode"
Output: "leotcede"

*/


string reverseVowels(string s) {

    unordered_set<char> st = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    int n = s.size();
    vector<int> index(n, 0);
    int i=0, j=n-1;

    while(i <= n-1 && j >= 0)
    {
        while(i <= n-1)
        {
            if(!index[i] && st.find(s[i]) != st.end())
                break;
            i++;
        }

        if(i == n)
            break;

        while(j >= 0)
        {
            if(!index[j] && st.find(s[j]) != st.end())
                break;
            j--;
        }

        if(j == -1)
            break;

        swap(s[i], s[j]);
        index[i] = 1;
        index[j] = 1;

        i++;
        j--;
        // Now increment (after swapping)
    }

    return s;
}
