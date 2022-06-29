// Recover Binary Search Tree

/*

You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree
were swapped by mistake. Recover the tree without changing its structure.

Example 1:
Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:
Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.


Constraints:

The number of nodes in the tree is in the range [2, 1000].
-2^31 <= Node.val <= 2^31 - 1

*/



// WRONG Approach

void recoverTree(TreeNode* root)
{
    TreeNode* minimum = NULL;
    TreeNode* maximum = NULL;

    findErrorNodes(root, minimum, maximum);

}

void findErrorNodes(TreeNode* root, TreeNode* minimum, TreeNode* maximum)
{
    if(!root)
        return;

    if(minimum != NULL && root->val <= minimum->val)
    {
        swap(root->val, minimum->val);
        return;
    }

    else if(maximum != NULL && root->val >= maximum->val)
    {
        swap(root->val, maximum->val);
        return;
    }

    findErrorNodes(root->left, minimum, root);
    findErrorNodes(root->right, root, maximum);
}



