/*

A gene string can be represented by an 8-character long string, with choices from 'A', 'C', 'G', and 'T'.

Suppose we need to investigate a mutation from a gene string start to a gene string end where one mutation
is defined as one single character changed in the gene string.

For example, "AACCGGTT" --> "AACCGGTA" is one mutation.
There is also a gene bank bank that records all the valid gene mutations.
A gene must be in bank to make it a valid gene string.

Given the two gene strings start and end and the gene bank bank, return the minimum number of mutations
needed to mutate from start to end. If there is no such a mutation, return -1.

Note that the starting point is assumed to be valid, so it might not be included in the bank.

Example 1:
Input: start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
Output: 1

Example 2:
Input: start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
Output: 2

Example 3:
Input: start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
Output: 3

*/


int minMutation(string start, string end, vector<string>& bank) {

    vector<char> choices = {'A', 'C', 'G', 'T'};
    unordered_set<string> us(bank.begin(), bank.end());
    queue<string> q;

    if(us.find(end) == us.end())
        return -1;

    int level = 0;
    q.push(start);

    while(!q.empty())
    {
        int n = q.size();
        level++;

        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;
            us.erase(cur);

            if(cur == end)
                return level-1;

            for(int i=0; i<cur.size(); i++)
            {
                char x = cur[i];
                for(int j=0; j<choices.size(); j++)
                {
                    cur[i] = choices[j];

                    if(us.find(cur) != us.end())
                        q.push(cur);
                }
                cur[i] = x;
            }
        }
    }

    return -1;
}
