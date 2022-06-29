TreeNode *parent = NULL;



TreeNode* findNode(TreeNode* root, int key)
{
    if(!root)
        return NULL;

    if(root->val == key)
        return root;

    else if(root->val > key)
    {
        parent = root;
        return findNode(root->left, key);
    }

    else
    {
        parent = root;
        return findNode(root->right, key);
    }

}



TreeNode* deleteNode(TreeNode* root, int key) {

    TreeNode *cur = findNode(root, key);

    if(!cur)
        return root;

    if(!cur->left && !cur->right)
    {
        if(!parent)
            return NULL;

        if(parent->left == cur)
            parent->left = NULL;

        else
            parent->right = NULL;
    }


    else if(!cur->left && cur->right)
    {
        if(!parent)
        {
            root = cur->right;
            cur->right = NULL;
            return root;
        }

        if(parent->left == cur)
            parent->left = cur->right;

        else
            parent->right = cur->right;

    }


    else if(cur->left && !cur->right)
    {
        if(!parent)
        {
            root = cur->left;
            cur->left = NULL;
            return root;
        }

        if(parent->left == cur)
            parent->left = cur->left;

        else
            parent->right = cur->left;

    }

    else
    {
        TreeNode *temp, *prev;

        temp = cur->right;
        prev = NULL;

        while(temp->left)
        {
            prev = temp;
            temp = temp->left;
        }

        if(!prev)
        {
            cur->val = temp->val;
            cur->right = temp->right;
        }

        else
        {
            cur->val = temp->val;
            prev->left = temp->right;
        }

    }

    return root;

}

