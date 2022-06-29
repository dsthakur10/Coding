// Given an ancestor matrix mat[n][n] where Ancestor matrix is defined as below.

// mat[i][j] = 1 if i is ancestor of j
// mat[i][j] = 0, otherwise
// Construct a Binary Tree from a given ancestor matrix where ALL ITS VALUES OF NODES ARE FROM 0 TO N-1.

// It may be assumed that the input provided the program is valid and tree can be constructed out of it.
// Many Binary trees can be constructed from one input. The program will construct any one of them.

/*

Examples:
Input: 0 1 1
       0 0 0
       0 0 0
Output: Root of one of the below trees.
    0                0
  /   \     OR     /   \
 1     2          2     1

Input: 0 0 0 0 0 0
       1 0 0 0 1 0
       0 0 0 1 0 0
       0 0 0 0 0 0
       0 0 0 0 0 0
       1 1 1 1 1 0
Output: Root of one of the below trees.
      5              5               5
   /    \           / \            /   \
  1      2   OR    2   1    OR    1     2  OR ....
 /  \   /        /    /  \       / \    /
0   4  3        3    0    4     4   0  3
There are different possible outputs because ancestor matrix doesn't store that which child is left and which is right.

*/



#include<iostream>
#include<queue>
#include<stack>

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
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);
void inorder(TreeNode *root);


TreeNode* constructBTFromAncestorMatrix(int mat[][], int row, int col);

int main()
{
    int mat[][] = {};




    std::cout<<"Level-order traversal of Full Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Full Binary Tree:\n";
    inorder(root);

}
