// Populating Next Right Pointers in Each Node

/*

You are given a perfect binary tree where all leaves are on the same level, and every parent has two children.
The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should
be set to NULL.

Initially, all next pointers are set to NULL.

*/


// Method-1 --> BFS Iterative with O(n) space {queue}

Node* connect(Node* root) {

    if(!root)
        return NULL;

    queue<Node*> q;
    q.push(root);

    while(!q.empty())
    {
        int n = q.size();

        while(n > 0)
        {
            Node* node = q.front();
            q.pop();

            if(node->left)
                q.push(node->left);

            if(node->right)
                q.push(node->right);

            if(n > 1)
                node->next = q.front();
            n--;
        }
    }

    return root;
}


// Method-2 --> Iterative BFS with constant space


Node* connect(Node* root)
{
    if(!root || (!root->left && !root->right))
        return root;

    Node *cur = root;

    while(cur->left)
    {
        Node* temp = cur;
        while(temp)
        {
            temp->left->next = temp->right;
            temp->right->next = (temp->next) ? temp->next->left : NULL;

            temp = temp->next;
        }

        cur = cur->left;
    }

    return root;
}




// Method-3 --> Recursive

// inverse Preorder --> Root Right Left

Node* connect(Node* root) {

    preorder(root, root);
    return root;

}


void preorder(Node* root, Node* parent)
{
    if(!root)
        return;

    if(parent->left == root)
        root->next = parent->right;

    else if(parent->right == root)
        root->next = parent->next ? parent->next->left : NULL;

    preorder(root->right, root);
    preorder(root->left, root);
}



// Method-4 --> Recursive (Better)

Node* connect(Node* root)
{
    if(!root || (!root->left && !root->right))
        return root;

    Node *lc , *rc;

    lc = root->left;
    rc = root->right;

    lc->next = rc;
    rc->next = (root->next) ? root->next->left : nullptr;

    root->right = connect(root->right);
    root->left = connect(root->left);

    return root;
}
