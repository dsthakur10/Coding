// Satisfiability of Equality Equations

/*

You are given an array of strings equations that represent relationships between variables where each string
equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".
Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if it is possible to assign integers to variable names so as to satisfy all the given equations,
or false otherwise.


Example 1:
Input: equations = ["a==b","b!=a"]
Output: false

Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.

Example 2:
Input: equations = ["b==a","a==b"]
Output: true

Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

*/


// Wrong Method

bool equationsPossible(vector<string>& equations)
{
    // creating vertices for every possible variable, i.e. alphabets
    UnionFind ufEqual(26);
    UnionFind ufUnequal(26);

    for(int i=0; i<equations.size(); i++)
    {
        int u = (int)(equations[i][0]-'a');
        int v = (int)(equations[i][3]-'a');

        if(equations[i][1] == '=')
        {
            if(ufEqual.connected(u,v))
                continue;

            if(!ufUnequal.connected(u,v))
            {
                ufEqual.unionSet(u,v);
            }

            else
                return false;
        }

        else
        {
            if(ufUnequal.connected(u,v))
                continue;

            if(!ufEqual.connected(u,v))
            {
                ufUnequal.unionSet(u,v);
            }

            else
                return false;
        }
    }

    return true;
}




bool equationsPossible(vector<string>& equations) {

    // creating vertices for every possible variable, i.e. alphabets
    UnionFind uf(26);

    // 1st pass --> get alligned all the equal variables
    for(int i=0; i<equations.size(); i++)
    {
        int u = (int)(equations[i][0]-'a');
        int v = (int)(equations[i][3]-'a');

        if(equations[i][1] == '=' && !uf.connected(u,v))
            uf.unionSet(u,v);
    }


    for(int i=0; i<equations.size(); i++)
    {
        int u = (int)(equations[i][0]-'a');
        int v = (int)(equations[i][3]-'a');

        if(equations[i][1] == '!')
        {
            if(uf.connected(u,v))
                return false;

            uf.unionSet(u,v);
        }
    }

    return true;
}



bool equationsPossible(vector<string>& equations) {

    // creating vertices for every possible variable, i.e. alphabets
    UnionFind ufEqual(26);
    UnionFind ufUnequal(26);

    // fails here: ["a!=i","g==k","k==j","k!=i","c!=e","a!=e","k!=a","a!=g","g!=c"]
    // This implies you cannot arrange all inequalities in same component.

    for(int i=0; i<equations.size(); i++)
    {
        int u = (int)(equations[i][0]-'a');
        int v = (int)(equations[i][3]-'a');

        if(equations[i][1] == '=' && !ufEqual.connected(u,v))
        {
            ufEqual.unionSet(u,v);
        }

        else if(equations[i][1] == '!')
        {
            if(u == v)
                return false;

            if(!ufUnequal.connected(u,v))
                ufUnequal.unionSet(u,v);
        }
    }

    for(int i=0; i<equations.size(); i++)
    {
        int u = (int)(equations[i][0]-'a');
        int v = (int)(equations[i][3]-'a');

        // fails when u & v are same vertices

//          if(ufEqual.connected(u,v) && ufUnequal.connected(u,v))
//              return false;

        if(u!=v && ufEqual.connected(u,v) && ufUnequal.connected(u,v))
            return false;
    }

    return true;
}



// Method-1 --> Disjoint-Set

// We must needed 2 pass to solve this problem. WHY ? Because you cannot identify relationships in 1 pass
// 1st PASS (==)--> Collect all equalities in the form of components. A component contains all the alphabets that
//                  are equal
// 2nd PASS (!=)--> Check for component of u & v --> Return false if same component

// You cannot have a != b when a & b are in same component (a == b)

bool equationsPossible(vector<string>& equations) {

    // creating vertices for every possible variable, i.e. alphabets
    UnionFind uf(26);

    int counter = 0;
    for(int i=0; i<equations.size(); i++)
    {
        int u = equations[i][0]-'a';
        int v = equations[i][3]-'a';

        if(equations[i][1] == '=' && !uf.connected(u,v))
            uf.unionSet(u,v);
    }

    for(int i=0; i<equations.size(); i++)
    {
        int u = equations[i][0]-'a';
        int v = equations[i][3]-'a';

        if(equations[i][1] == '!' && uf.connected(u,v))
            return false;
    }

    return true;
}


// Method-2 --> DFS

// 1. Create a graph such that edge(u,v) represents "u==v" string
// 2. Color every vertex using DFS. Color of vertices in same DFS search must kept same.
// 3. Now for every other string "u!=v", check if color[u] == color[v] & return FALSE
//      --> Nodes from same Connected component must not have inequality between them.

bool equationsPossible(vector<string>& equations) {

    // creating vertices for every possible variable, i.e. alphabets
    vector<int> color(26, 0);
    vector<vector<int>> nodes = buildGraph(equations);

    int count = 0;
    for(int i=0; i<26; i++)
    {
        count++;
        if(!color[i])
            DFS(nodes, color, i, count);
    }


    for(int i=0; i<equations.size(); i++)
    {
        if(equations[i][1] != '=')
        {
            int u = equations[i][0]-'a';
            int v = equations[i][3]-'a';

            if(color[u] == color[v])
                return false;
        }
    }

    return true;
}


void DFS(vector<vector<int>>& nodes, vector<int>& color, int u, int count)
{
    color[u] = count;

    for(int v : nodes[u])
    {
        if(!color[v])
            DFS(nodes, color, v, count);
    }
}


vector<vector<int>> buildGraph(vector<string>& equations){

    vector<vector<int>> adj(26);

    for(int i=0; i<equations.size(); i++)
    {
        if(equations[i][1] == '=')
        {
            int u = equations[i][0]-'a';
            int v = equations[i][3]-'a';

            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    return adj;
}
