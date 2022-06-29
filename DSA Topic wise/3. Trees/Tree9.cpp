/*
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:
    - binary tree in which the left and right subtrees of every node differ in height by no more than 1.

*/


#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include <algorithm>
#include<cmath>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x, TreeNode *lptr, TreeNode *rptr)
    {
        val = x;
        left = lptr;
        right = rptr;
    }
};


TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                     // iterative way (using queue)
void levelorder(TreeNode *root);
int height(TreeNode* root);
int DFSheight(TreeNode *root);
bool isBalanced(TreeNode* root);                            // top-down approach - O(n^2)
bool isBalanced2(TreeNode* root);                           // bottom-up approach - O(n)

int main()
{
    TreeNode *root = NULL;
    int x;

    for(int i=1; i<=20; i++)
        insertNode(&root,i);

    levelorder(root);

    bool flag = isBalanced2(root);

    if(flag)
        std::cout << "\n\nBalanced Binary Tree";

    else
        std::cout << "\n\nImBalanced\n";


    return 0;
}


TreeNode* createNode(int x)
{
    TreeNode *ptr = new TreeNode(x);
    return ptr;
}


void insertNode(TreeNode **root,int x)
{
    if(!(*root))
    {
        *root = createNode(x);
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *ptr , *temp;
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



void levelorder(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode* temp;

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


//------------------ Method-1 ------------------

// Helper function height() is used to get the height of LST & RST for every node.
// This function is used for every node recursively to calculate difference in heights of LST & RST. Even if at one node, there is imbalance --> return false
// return true if there is no imbalance found in any node.

// Time complexity = O(n^2) because we are calculating heights of LST & RST for every node. And calculating heights requires traversing every nodes of that subtree.

int height(TreeNode* root)
{
    if(!root)
        return 0;

    return 1 + std::max(height(root->left),height(root->right));
}



bool isBalanced(TreeNode* root)
{
    if(!root)
        return true;

    int l = height(root->left);
    int r = height(root->right);

    if(abs(l-r) > 1)
    {
        return false;                           // Even if the tree is balanced from this root, it might be imbalanced somewhere else in subtrees. So check every subtree.
    }

    return isBalanced(root->left) && isBalanced(root->right);       // Both LST & RST must be balanced.
}




//---------------- Method-2 -------------------

// The 2nd method is based on DFS. Instead of calling height() explicitly for each child node, we return the height of the current node in DFS recursion.
// When the sub tree of the current node (inclusive) is balanced, the function DFSheight() returns a non-negative value as the height. Otherwise -1 is returned.
// According to the leftHeight and rightHeight of the two children, the parent node could check if the sub treeis balanced, and decides its return value.

// Time Complexity T(n) = O(n) --> every node is accessed once & height is returned.


int DFSheight(TreeNode *root)
{
    if(!root)
        return 0;

    int l,r;

    l = DFSheight(root->left);
    if(l == -1)
        return -1;

    r = DFSheight(root->right);
    if(r == -1)
        return -1;

    if(abs(l-r) > 1)
        return -1;

    return 1 + std::max(l,r);
}


bool isBalanced2(TreeNode* root)
{
    return DFSheight(root) != -1;
}
