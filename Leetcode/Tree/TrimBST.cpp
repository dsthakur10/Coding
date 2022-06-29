
TreeNode *newRoot;

void trim(TreeNode* parent, TreeNode* cur, int low, int high)
{
    if(!cur)
        return;

    if(cur->left)
        trim(cur, cur->left, low, high);

    if(cur->right)
        trim(cur, cur->right, low, high);


    if(cur->val < low || cur->val > high)
    {
        if(parent)
        {
            if(parent->left == cur)
            {
                parent->left = (cur->left) ? cur->left : cur->right;
            }

            else if(parent->right == cur)
            {
                parent->right = (cur->left) ? cur->left : cur->right;
            }

        }

        else
        {
            if(cur->val > high)
            {
                parent = cur->left;
                cur->left = NULL;

            }

            else if(cur->val < low)
            {
                parent = cur->right;
                cur->right = NULL;

            }

            newRoot = parent;
        }
    }

}


TreeNode* trimBST(TreeNode* root, int low, int high) {

    newRoot = root;

    trim(NULL, root, low, high);

    return newRoot;
}



