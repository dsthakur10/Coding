// Copy List with Random Pointer

/*

A linked list of length n is given such that each node contains an additional random pointer, which could point to
any node in the list, or null.

Construct a deep copy of the list. The deep copy should consist of exactly n brand new nodes, where each new node
has its value set to the value of its corresponding original node. Both the next and random pointer of the new nodes
should point to new nodes in the copied list such that the pointers in the original list and copied list represent
the same list state. None of the pointers in the new list should point to nodes in the original list.

For example, if there are two nodes X and Y in the original list, where X.random --> Y, then for the corresponding
two nodes x and y in the copied list, x.random --> y.

Return the head of the copied linked list.

The linked list is represented in the input/output as a list of n nodes. Each node is represented as a
pair of [val, random_index] where:

val: an integer representing Node.val
random_index: the index of the node (range from 0 to n-1) that the random pointer points to, or null if it does not
point to any node.
Your code will only be given the head of the original linked list.

*/


// Method-1 --> HashMap --> O(n) time | O(n) space --> TWO pass

// Logic is to create a new node for every node in original list & store the address of newly created node
// alongside original node.

Node* copyRandomList(Node* head)
{
    unordered_map<Node*, Node*> mp;
    Node* temp = head;

    Node* newHead = NULL;

    // 1st pass --> Storing nodes
    while(temp)
    {
        mp[temp] = new Node(temp->val);
        temp = temp->next;
    }

    temp = head;

    // 2nd pass --> Mapping
    while(temp)
    {
        mp[temp]->next = mp[temp->next];
        mp[temp]->random = mp[temp->random];
        temp = temp->next;
    }

    return mp[head];
}



// Same method --> ONE pass
Node* copyRandomList(Node* head) {

    unordered_map<Node*, Node*> mp;
    Node* temp = head;

    Node* newHead = NULL;

    while(temp)
    {
        if(mp.find(temp) == mp.end())
            mp[temp] = new Node(temp->val);

        if(temp->next && mp.find(temp->next) == mp.end())       // checking if temp->next != NULL
            mp[temp->next] = new Node(temp->next->val);

        if(temp->random && mp.find(temp->random) == mp.end())   // checking if temp->random != NULL
            mp[temp->random] = new Node(temp->random->val);

        mp[temp]->next = mp[temp->next];
        mp[temp]->random = mp[temp->random];

        temp = temp->next;
    }

    return mp[head];
}



// Method-2 --> O(n) time | O(1) space

/*
The idea is to associate the original node with its copy node in a single linked list. In this way, we don't need
extra space to keep track of the new nodes.

The algorithm is composed of the following three steps which are also 3 iteration rounds.

    a. Iterate the original list and duplicate each node. Duplicate of each node follows its original immediately.
    b. Iterate the new list and assign the random pointer for each duplicated node.
    c. Restore the original list and extract the duplicated nodes.


    a. 1 | 3 --> 1' --> 2 | 4 --> 2' --> 3 | NULL --> 3' --> 4 | NULL --> 4'

    b. 1 | 3 --> 1' | 3' --> 2 | 4 --> 2' | 4' --> 3 | NULL --> 3' | NULL --> 4 | NULL --> 4' | NULL

    c. 1 | 3 --> 2 | 4 -->  3 | NULL -->  4 | NULL
        1' | 3' --> 2' | 4' --> 3' | NULL --> 4' | NULL
*/


Node* copyRandomList(Node* head) {

    if(!head)
        return NULL;

    Node *cur, *succ, *temp, *newHead;

    // Creating just copies
    cur = head;
    while(cur)
    {
        succ = cur->next;
        temp = new Node(cur->val);
        cur->next = temp;
        temp->next = succ;

        cur = succ;
    }


    // Assigning random pointers to copied nodes
    cur = head;
    while(cur)
    {
        temp = cur->next;

        // Note that random pointer of copied node must point to copy of the node pointed by random pointer
        if(cur->random)
            temp->random = cur->random->next;

        cur = temp->next;
    }


    // Segregating original nodes from copied nodes while maintaining the links between them.
    cur = head;
    newHead = cur->next;
    temp = cur->next;
    while(temp)
    {
        succ = temp->next;
        cur->next = succ;
        temp->next = (succ == NULL ? NULL : succ->next);

        cur = cur->next;
        temp = temp->next;
    }

    return newHead;
}
