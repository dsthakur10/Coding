/*

Given a binary tree

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
            4 ------->  5 ----->       7 -------> NULL


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
    Node *next;

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
Node* connect3(Node* root);                             // recursive
Node* connect4(Node* root);                             // iterative

Node* fnext(Node* root);

int main()
{
    Node *root = NULL, *temp, *temp2;

/*
    for(int i=1; i<=15; i++)
        insertNode(&root,i);

*/

    insertNode(&root,1);
    insertNode(&root,2);
    insertNode(&root,3);

    temp = root->right;
    temp->left = createNode(4);
    temp->right = createNode(5);
    temp2 = temp->right;
    temp = temp->left;
    temp->right = createNode(6);
    temp2->left = createNode(7);

    std::cout << "root : " << root->val << "\n";

    levelorder(root);

    root = connect2(root);

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

/*

Since we need to find "next" left most, we should call right first to make sure the nexts(on the right side) are already well connected,
otherwise there would be gap which will not let you connect those leftmost nodes with their next nodes in right side.
For example this is what would happen for this input if we call left first:

                   2
                  /  \
                 1-> 3
                / \  / \
               0->7->9->1
              /  / \  / \
            2-> 1->"0"8  8

When the recursion comes to the "0" in the lowest level, the next step is to connect 0 with 8. However since 9 and 1 on the upper level haven't been connected yet
(because we execute left part before we do right), fnext() is not able to reach the left most child of 1, due to the gap between 9 and 1.

*/


Node* connect(Node* root)
{
    if(!root || (!root->left && !root->right))              // Simply return the node if it's a leaf node.
        return root;

    Node *lc , *rc, *temp;

    if(root->left)
    {
        lc = root->left;

        if(root->right)
            lc->next = root->right;

        else
        {
            temp = root->next;

            while(temp)
            {
                if(temp->left)
                {
                    lc->next = temp->left;
                    break;
                }

                else if(temp->right)
                {
                    lc->next = temp->right;
                    break;
                }

                else
                    temp = temp->next;

            }
        }
    }

    if(root->right)
    {
        rc = root->right;

        temp = root->next;

        while(temp)
        {
            if(temp->left)
            {
                rc->next = temp->left;
                break;
            }

            else if(temp->right)
            {
                rc->next = temp->right;
                break;
            }

            else
                temp = temp->next;
        }
    }

    root->right = connect(root->right);                 // populate RST pointers first so that while populating LST, nodes does not have to face any issues in finding next nodes

    root->left = connect(root->left);

    return root;
}



Node* connect2(Node* root)
{
    if(!root || (!root->left && !root->right))              // Simply return the node if it's a leaf node.
        return root;

    Node *cur = root;
    Node *temp = NULL;
    Node *prev = NULL;
    Node *lc,*rc;

    while(cur)                                        // prev is used to keep track of every level's 1st node to start with.
    {
        if(cur->left)
            prev = cur->left;

        else if(cur->right)
            prev = cur->right;

        else
        {
            temp = cur->next;
            while(temp)
            {
                if(temp->left)
                {
                    prev = temp->left;
                    break;
                }

                else if(temp->right)
                {
                    prev = temp->right;
                    break;
                }

                else
                    temp = temp->next;
            }

            prev = NULL;
        }

        while(cur)
        {
            if(cur->left)
            {
                lc = cur->left;

                if(cur->right)
                    lc->next = cur->right;

                else
                {
                    temp = cur->next;

                    while(temp)
                    {
                        if(temp->left)
                        {
                            lc->next = temp->left;
                            break;
                        }

                        else if(temp->right)
                        {
                            lc->next = temp->right;
                            break;
                        }

                        else
                            temp = temp->next;
                    }
                }

                std::cout <<"\n" << lc->val << " -> " << (lc->next ? lc->next->val : -1) ;
            }

            if(cur->right)
            {
                rc = cur->right;

                temp = cur->next;

                while(temp)
                {
                    if(temp->left)
                    {
                        rc->next = temp->left;
                        break;
                    }

                    else if(temp->right)
                    {
                        rc->next = temp->right;
                        break;
                    }

                    else
                        temp = temp->next;
                }

                std::cout <<"\n" << rc->val <<" -> " << (( rc->next != nullptr ) ? rc->next->val : -1);
            }

            cur = cur->next;                                                // cur->next will point to the next node in sequence in the same level
        }

        cur = prev;
    }

    return root;

}



// ------------------ Method-3 ---------------------


Node* fnext(Node* root)
{
    if(!root)
        return NULL;

    if(root->left)
        return root->left;

    if(root->right)
        return root->right;

    return fnext(root->next);
}



Node* connect3(Node *root)
{
    if(!root || (!root->left && !root->right))
        return root;

    if(root->left)
    {
        if (root->right)
            root->left->next = root->right;

        else
            root->left->next = fnext(root->next);
    }

    if(root->right)
        root->right->next = fnext(root->next);

    root->right = connect3(root->right);
    root->left = connect3(root->left);

    return root;
}



// ---------------- Method-4 -----------------

Node* connect4(Node *root)
{
    Node* head = NULL;                               //head of the next level
    Node* prev = NULL;                               //current node on the NEXT level
    Node* cur = root;                                //current node of CURRENT level

    while(cur)
    {
        while(cur)
        {                                                                   //iterate on the current level
                                                    //left child
            if(cur->left)
            {
                if(prev)
                    prev->next = cur->left;

                else
                    head = cur->left;

                prev = cur->left;
            }

                                                    //right child
            if(cur->right)
            {
                if(prev)
                    prev->next = cur->right;

                else
                    head = cur->right;

                prev = cur->right;
            }
                                                                    //move to next node
            cur = cur->next;
        }

                                                                    //move to next level
        cur = head;
        head = NULL;
        prev = NULL;
    }

    return root;
}
