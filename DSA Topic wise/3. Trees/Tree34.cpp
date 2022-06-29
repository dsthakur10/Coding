// Diameter of a tree

/*

Given the root of a binary tree, return the length of the diameter of the tree.

The diameter of a binary tree is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root.

The length of a path between two nodes is represented by the number of edges between them.

*/


int diameter = 0;

int diameterOfBinaryTree(TreeNode* root) {

    height(root);
    return diameter;
}


int height(TreeNode* root)
{
    if(!root)
        return 0;

    int l = height(root->left);
    int r = height(root->right);

    diameter = max(diameter, l + r);
    return 1 + max(l, r);
}
