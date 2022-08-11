/*

Two strings X and Y are similar if we can swap two letters (in different positions) of X, so that it equals Y.
Also two strings X and Y are similar if they are equal.

For example, "tars" and "rats" are similar (swapping at positions 0 and 2), and "rats" and "arts" are similar,
but "star" is not similar to "tars", "rats", or "arts".

Together, these form two connected groups by similarity: {"tars", "rats", "arts"} and {"star"}.
Notice that "tars" and "arts" are in the same group even though they are not similar.
Formally, each group is such that a word is in the group if and only if it is similar to at least one other word
in the group.

We are given a list strs of strings where EVERY STRING IN STRS IS AN ANAGRAM OF EVERY OTHER STRING IN STRS.
How many groups are there?

*/



// LOGIC
/*

How do we know if two strings are similar?

This can be determined by calculating hamming distance between them.
Since all strings are anagrams, if two strings have hamming distance of two, then they can be converted into each
other by swapping the only two different characters.

In other wors, two strings are similar if and only if they have hamming distance two.

*/

int numSimilarGroups(vector<string>& strs) {

    int n = strs.size();
    // for each of the string
    UnionFind uf(n);

    int groups = n;
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(!uf.connected(i,j) && isValid(strs[i], strs[j]))
            {
                uf.unionSet(i, j);
                groups--;
            }
        }
    }

    return groups;
}


// anagrams with only 1 swapping are allowed
bool isValid(string str1, string str2)
{
    int count = 0;
    for(int i=0; i<str1.size(); i++)
    {
        if(str1[i] != str2[i])
            count++;

        if(count > 2)
            return false;
    }

    return true;
}
