/*

You are given a PERFECT binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

                            1 -------> NULL
                2   --------->  3 -------> NULL
            4 ------->  5 --------> 6 ---------> 7 -------> NULL


*/


#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include <algorithm>
#include<cmath>

struct Node
{
    int val;
    Node *left;
    Node *right;

    Node()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }

    Node(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }

    Node(int x, Node *lptr, Node *rptr, Node *nptr)
    {
        val = x;
        left = lptr;
        right = rptr;
        next = nptr;
    }

};


Node* createNode(int x);
void insertNode(Node **root,int x);                     // iterative way (using queue)
void levelorder(Node *root);

Node* connect(Node* root);                              // recursive
Node* connect2(Node* root);                             // iterative


int main()
{
    Node *root = NULL;

    for(int i=1; i<=15; i++)
        insertNode(&root,i);

    levelorder(root);

    root = connect(root);

    return 0;
}


Node* createNode(int x)
{
    Node *ptr = new Node(x);
    return ptr;
}


void insertNode(Node **root,int x)
{
    if(!(*root))
    {
        *root = createNode(x);
        return;
    }

    std::queue<Node*> q;
    Node *ptr , *temp;
    ptr = createNode(x);

    q.push(*root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(!temp->left)
        {
            temp->left = ptr;
            return;
        }

        if(!temp->right)
        {
            temp->right = ptr;
            return;
        }

        q.push(temp->left);
        q.push(temp->right);
    }
}



void levelorder(Node *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<Node*> q;
    Node* temp;

    q.push(root);

    while(!q.empty())
    {
        int n = q.size();
        while(n>0)
        {
            temp = q.front();
            q.pop();

            std::cout<<temp->val<<' ';

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }
        std::cout << "\n";
    }
}



// Idea is simple.
// For any left child of any parent node,       left_child->next = parent->right
// For any right child of any parent node,      right_child->next = parent->next->left

Node* connect(Node* root)
{
    if(!root || (!root->left && !root->right))              // Simply return the node if it's a leaf node.
        return root;

    Node *lc , *rc;

    lc = root->left;
    rc = root->right;

    lc->next = rc;
    rc->next = (root->next) ? root->next->left : nullptr;           // what if the node is the rightmost node ? ---> simply point the next pointer to NULL

    root->left = connect(root->left);

    root->right = connect(root->right);

    return root;
}


Node* connect2(Node* root)
{
    if(!root || (!root->left && !root->right))              // Simply return the node if it's a leaf node.
        return root;

    Node *cur = root;
    Node *temp = NULL;

    while(cur->left)                                        // temp is used to keep track of every level's 1st node to start with.
    {
        temp = cur->left;

        while(cur)
        {
            cur->left->next = cur->right;
            cur->right->next = (cur->next) ? cur->next->left : nullptr;

            cur = cur->next;                                                // cur->next will point to the next node in sequence in the same level
        }

        cur = temp;
    }

}
