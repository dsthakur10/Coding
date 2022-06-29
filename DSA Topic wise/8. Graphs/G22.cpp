// Redundant Connection

/*
In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added.
The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that
there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes.
If there are multiple answers, return the answer that occurs last in the input

*/


// Method-1 --> Disjoint Set

// There are total n edges (n-1 of original tree + 1 redundant edge). We know this redundant edge will form a cycle
// We have to detect that edge which will create cycle in our graph
// --> This is nothing but detecting cycle which can be done easily by Disjoint-Set DS.

// NOTE: Question asks to return last edge that occurred in the graph formation --> not any random edge of cycle
// Disjoint-Set will take care of this because until this last edge, there won't be a cycle in graph.

vector<int> findRedundantConnection(vector<vector<int>>& edges) {

// Since we are given tree + an edge --> number of edges = (N-1) + 1 = N

    int n = edges.size();
    UnionFind uf(n+1);          // Vertex starts from 1

    for(int i=0; i<n; i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];

        if(uf.connected(u,v))       // cycle will be detected only once --> return this edge immediately
            return {u,v};

        uf.unionSet(u,v);
    }

    return {};
}



// Method-2 --> DFS --> Use cycle detection in undirected graph
// But here lies a problem --> Normal Cycle detection won't give last added edge in cycle. It will give random
// edge of cycle. To get last added edge, we need to keep track of cycle start node & end of cycle.


