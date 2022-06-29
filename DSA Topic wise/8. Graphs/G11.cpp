// Find the Town Judge

/*

In a town, there are n people labeled from 1 to n. There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

    1. The town judge trusts nobody.
    2. Everybody (except for the town judge) trusts the town judge.
    3. There is exactly one person that satisfies properties 1 and 2.

You are given an array trust where trust[i] = [ai, bi] representing that the person labeled ai trusts the person labeled bi.

Return the label of the town judge if the town judge exists and can be identified, or return -1 otherwise.

Example 1:
Input: n = 2, trust = [[1,2]]
Output: 2

Example 2:
Input: n = 3, trust = [[1,3],[2,3]]
Output: 3

Example 3:
Input: n = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1

NOTE : All the pairs of trust are UNIQUE.

*/


// Method-1 --> Without converting edges to Adjacency List of Graph form

// indegree of judge = n-1 | outdegree = 0

int findJudge(int n, vector<vector<int>>& trust)
{
    unordered_set<int> out;          // Keep a track of outdegree of all nodes
    int counter = 0;                // indegree of possible candidate for judge

    for(int i=1; i<=n; i++)
        out.insert(i);

    for(int i=0; i<trust.size(); i++)
    {
        int x = trust[i][0];

        if(out.find(x) != out.end())
            out.erase(x);
    }

    if(out.size() != 1)             // only 1 node with outdegree = 0 (Because there can be only 1 judge)
        return -1;

    int possible = *(out.begin());

    for(int i=0; i<trust.size(); i++)
    {
        int y = trust[i][1];

        if(y == possible)
            counter++;
    }

    if(counter == n-1)              // indegree = n-1 (All must trust judge)
        return possible;

    return -1;
}



// Method-2 --> indegree[judge] - outdegree[judge] = n-1
// In every iteration increment indegree of y & decrement outdegree of x

int findJudge(int n, vector<vector<int>>& trust) {

    vector<int> inout(n+1, 0);

    for(int i=0; i<trust.size(); i++)
    {
        // add indegree | subtract outdegree
        int x = trust[i][0];
        int y = trust[i][1];

        // x-->y is an edge - +1 indegree to y & -1 outdegree to x
        inout[y]++;
        inout[x]--;
    }

    for(int i=1; i<=n; i++)
    {
        if(inout[i] == n-1)
            return i;
    }

    return -1;
}
