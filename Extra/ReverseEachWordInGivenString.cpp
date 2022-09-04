
/*

Given a String. Reverse each word in it where the words are separated by dots.

Example 1:
Input:
S = "i.like.this.program.very.much"
Output:
i.ekil.siht.margorp.yrev.hcum

*/


string reverseWords (string s)
{
    int i=0;
    int j=0;

    while(j < s.size())
    {
        while(j < s.size() && s[j] != '.')
            j++;

        reverse(s.begin()+i, s.begin()+j);

        j++;
        i=j;
    }

    //reverse(s.begin()+i, s.begin()+j);
    return s;
}
