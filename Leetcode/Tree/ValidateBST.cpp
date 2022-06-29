
// Method-1 --> iterative Inorder traversal

bool isValidBST(TreeNode* root)
{
    if(!root || (!root->left && !root->right))
        return true;

    stack<TreeNode*> st;
    TreeNode *cur;
    int temp;
    bool flag = true;

    st.push(root);
    cur = root->left;

    while(cur || !st.empty())
    {
        while(cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top();
        st.pop();

        if(flag)                // for initiliazing temp value (leftmost node)
            flag = false;

        else
        {
            if(temp >= cur->val)
                return false;
        }

        temp = cur->val;
        cur = cur->right;
    }

    return true;
}



// Method-2 --> Fix the interval in which a root->val can occur. min & max nodes are used for this.

bool isValidBST2(TreeNode* root) {

    return checkBST(root, NULL, NULL);

}


bool checkBST(TreeNode* root, TreeNode *min, TreeNode *max)
{
    if(!root)
        return true;

    if((min && root->val <= min->val) || (max && root->val >= max->val))
        return false;

    bool left = checkBST(root->left, min, root);            //

    bool right = checkBST(root->right, root, max);

    return left && right;
}



bool isValidBST3(TreeNode* root)
{
    return checkBST(root, LONG_MIN, LONG_MAX);
}

bool checkBST2(TreeNode* root, long min, long max)
{
    if(!root)
        return true;

    if((root->val <= min) || (root->val >= max))
        return false;

    bool left = checkBST(root->left, min, root->val);

    bool right = checkBST(root->right, root->val, max);

    return left && right;

}
