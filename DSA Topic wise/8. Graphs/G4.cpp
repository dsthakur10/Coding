
// Clone Graph

/*

Given a reference of a node in a CONNECTED UNDIRECTED graph.
Return a DEEP COPY (clone) of the graph.

Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}


TEST CASE FORMAT:

For simplicity, each node's value is the same as the node's index (1-indexed).
For example, the first node with val == 1, the second node with val == 2, and so on.
The graph is represented in the test case using an adjacency list.

An adjacency list is a collection of unordered lists used to represent a finite graph.
Each list describes the set of neighbors of a node in the graph.

THE GIVEN NODE WILL ALWAYS BE THE FIRST NODE WITH VAL = 1.
You must return the copy of the given node as a reference to the cloned graph.

EXAMPLE-1:

Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
Output: [[2,4],[1,3],[2,4],[1,3]]

Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).


EXAMPLE-2:

Input: adjList = [[]]
Output: [[]]

Explanation: Note that the input contains one empty list.
The graph consists of only one node with val = 1 and it does not have any neighbors.

*/


class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


/*
    Structure:
    Node is an object consisting of 2 datatypes -> val & neighbors
    val --> simply value of node
    neighbors --> vector of Node addresses which stores neighboring nodes of current given Node

*/

/*
    LOGIC:

    We have to create a deep copy of graph --> create a new node for every original node.
    We shall use a map for keeping a track of original nodes & copied(newly created) nodes
    so that you don't copy same node multiple times.
    Mapping = original --> copied

    To clone a graph, Traverse it through BFS or DFS.

    Given graph is said to be undirected + connected. Hence there is no need for a loop to check for connected components
    in either of BFS or DFS.
*/



// Method-1 --> BFS

/*
    1. Initially create a head node which defines the 1st node of adjacency list of graph.
        Equate it with given original node. Push the original node in queue
    2. Create a queue DS that will hold address of original nodes as you traversed them.
    3. Repeat while the queue is NOT EMPTY:
        a. Pop original node from front. Iterate through its neighbors.
        b. For every neighbor, check if there's a corresponding copy created (check in map).
           If not, create it & push original neighbor onto queue for BFS traversal.
        c. Now your task is to push this address of original neighbor's copy into current node's copy.
    4. Return head.

*/


Node* cloneGraph(Node* node) {

    if(!node)
        return NULL;

    unordered_map<Node*, Node*> copies;         // <original, copy>

    // head node represents the starting of ADJACENCY LIST

    Node* head = new Node(node->val, {});
    copies[node] = head;

    // We will push original graph nodes because we have to traverse the original graph to get the neighbors & clone it

    queue<Node*> q;                             // <original>
    q.push(node);

    while(!q.empty())
    {
        Node *cur = q.front();                  // cur is orginal node
        q.pop();

        for(Node* x : cur->neighbors)           // iterate over all neighboring nodes of current node in original graph
        {
            if(copies.find(x) == copies.end())      // if entry <neighbor, neighbor copy> does not exist, create
            {
                copies[x] = new Node(x->val, {});
                q.push(x);                          // Push the neighbor onto queue for traversal
            }

            copies[cur]->neighbors.push_back(copies[x]);

            // Neighbor copies must be added to neighbor property of current node's copy
        }
    }

    return head;
}



// Method-2 --> DFS

unordered_map<Node*, Node*> copies;

Node* cloneGraph(Node* node) {

    if(!node)
        return NULL;

    Node* head = new Node(node->val, {});
    copies[node] = head;

    DFS(node);

    return head;
}

void DFS(Node *cur)
{
    for(Node* x : cur->neighbors)
    {
        if(copies.find(x) == copies.end())      // works as !visited[x]
        {
            copies[x] = new Node(x->val, {});
            DFS(x);
        }
        copies[cur]->neighbors.push_back(copies[x]);
    }
}



// Method-3 --> DFS

Node* cloneGraph(Node* node)
{
    if (!node)
        return NULL;

    if (copies.find(node) == copies.end())
    {
        copies[node] = new Node(node -> val, {});

        for (Node* neighbor : node -> neighbors)
            copies[node] -> neighbors.push_back(cloneGraph(neighbor));
    }

    return copies[node];
}
