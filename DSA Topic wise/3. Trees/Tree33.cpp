
// Balanced Binary Tree

/*

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:
A binary tree in which the left and right subtrees of every node differ in height by no more than 1.

*/


// Top-Down approach --> Slower --> O(n^2)

bool isBalanced(TreeNode* root)
{
    if(!root)
        return true;

    int l = height(root->left);
    int r = height(root->right);

    if(abs(l-r) > 1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}


int height(TreeNode* root)
{
    if(!root)
        return 0;

    return 1 + std::max(height(root->left),height(root->right));
}




// Bottom-Up approach --> Faster --> O(n)

bool isBalanced(TreeNode* root) {

    int height;
    return maxHeight(root, height);

}

bool maxHeight(TreeNode* root, int& height)
{
    if(!root)
    {
        height = 0;
        return true;
    }

    int lst, rst;
    bool l = maxHeight(root->left, lst);
    bool r = maxHeight(root->right, rst);

    int diff = abs(lst - rst);
    height = 1 + max(lst, rst);

    return (diff <= 1) && l && r;
}




// OR


bool isBalanced(TreeNode* root)
{
    return DFSheight(root) != -1;
}


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
