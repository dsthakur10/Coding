int sum = 0;

TreeNode* convertBST(TreeNode* root) {

    convert(root);

    return root;
}


void convert(TreeNode* root)
{
    if(!root)
        return;

    convert(root->right);

    sum += root->val;
    root->val = sum;

    convert(root->left);

}

