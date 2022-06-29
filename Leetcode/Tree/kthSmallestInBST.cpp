int count = 0;
int value = -1;

int kthSmallest(TreeNode* root, int k) {

    inorder(root, k);

    return value;
}


void inorder(TreeNode* root, int k)
{
    if(!root || value != -1)                // avoids unnecessary traversal after finding required value.
        return;

    inorder(root->left, k);

    count++;
    if(count == k)
        value = root->val;

    inorder(root->right, k);

}

