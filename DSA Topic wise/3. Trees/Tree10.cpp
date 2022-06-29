/*

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the LENGTH OF THE LONGEST PATH BETWEEN ANY TWO NODES IN A TREE. THIS PATH MAY OR MAY NOT PASS THROUGH THE ROOT.

The length of a path between two nodes is represented by the number of edges between them.

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
int diameterOfBinaryTree(TreeNode* root);                   // time complexity = O(n^2) --> in every traversal, height of subtree is calculated.

int DFSdiameter(TreeNode *root, int& maxx);
int diameterOfBinaryTree2(TreeNode* root);


int main()
{
    TreeNode *root = NULL, *temp;
    int x;

/*
    for(int i=1; i<=20; i++)
        insertNode(&root,i);
*/
    insertNode(&root,1);
    insertNode(&root,2);
    insertNode(&root,3);
    insertNode(&root,4);
    insertNode(&root,5);

    temp = root;

    while(temp->right)
        temp = temp->right;

    temp->right = createNode(6);
    temp = temp->right;

    insertNode(&temp,7);
    insertNode(&temp,8);
    insertNode(&temp,9);

    levelorder(root);

    int dia = diameterOfBinaryTree2(root);

    std::cout << "\nDiameter of binary tree = " << dia;

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
/*

Diameter is length of longest path from 1 node to other. Hence we can calculate farthest located nodes from given root on both its side & return that value.

Diameter is nothing but
        - in case of non-NULL subtrees --> 2 + height(LST) + height(RST)
        - while in case of NULL LST or NULL RST --> 1 + height(RST) OR 1 + height(LST)

Also after calculating above value, check the diameters of both LST & RST
Maximum value of all the 3 will be the new diameter for the current tree.


Time complexity =
    For balanced tree --> T(n) = 2T(n/2) + O(n) --> O(nlogn)  {O(n) for height() of 2 subtrees}
    For skew tree --> T(n) = T(n-1) + O(n) --> O(n^2)
*/

int height(TreeNode* root)
{
    if(!root)
        return 0;

    if(!root->left && !root->right)
        return 0;

    return 1 + std::max(height(root->left),height(root->right));
}


int diameterOfBinaryTree(TreeNode* root)
{
    static int maxx = 0;

    if(!root)
        return 0;

    if(!root->left && !root->right)                     // return 0 for leaf
        return 0;

    maxx = std::max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right));           // check if there's a diameter without involving root.

    int l = height(root->left);
    int r = height(root->right);

    if(root->left && !root->right)                      // RST = NULL. Diameter --> 1 + height(LST) OR diameter(LST) OR diameter(RST)
        maxx = std::max(maxx,1+l);

    else if(!root->left && root->right)                 // LST = NULL. Diameter --> 1 + height(RST) OR diameter(LST) OR diameter(RST)
        maxx = std::max(maxx,1+r);

    else                                                // 2 + height(LST) + height(RST)
        maxx = std::max(maxx,2+l+r);

    return maxx;
}


//----------------- Method-2 ---------------------

/*

Idea - Keep track of maximum diameter during traversal and find the height of the subtrees.

We are using helper function DFSdiameter() which does 2 things.
    (1) Recursively finds the height of root's both subtrees (LST & RST) & returns the height of given tree rooted at root
    (2) In this process, it also calculates diameter which it stores in its argument variable 'maxx' which is passed by reference to it.

This method reduces the time complexity to O(n) as now there is no need to separately calculate height in each iteration of function.

*/

int diameterOfBinaryTree2(TreeNode* root)
{
    int maxx = 0;
    int dia = DFSdiameter(root,maxx);

    return maxx;
}


int DFSdiameter(TreeNode *root, int& maxx)
{
    if(!root)
        return 0;

    if(!root->left && !root->right)             // height of leaf = 0
        return 0;

    int l = 0, r = 0;

    if(root->left)
        l = 1 + DFSdiameter(root->left, maxx);

    if(root->right)
        r = 1 + DFSdiameter(root->right, maxx);

    maxx = std::max(maxx, l+r);             // this is diameter of given tree

    return std::max(l,r);                   // this is height of given tree rooted at root
}

/*

some more modifications can be done to reduce the complexity of code (not the time complexity):
    - Returning height of leaf = 1
    - No +1 in maxx

*/
