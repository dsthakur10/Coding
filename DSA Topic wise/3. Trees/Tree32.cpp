// Construct Binary Tree from Inorder and Postorder Traversal


unordered_map<int, int> mp;
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {

    int n = inorder.size();

    // storing indexes in map to reduce search time to O(1)
    for(int i=0; i<n; i++)
        mp[inorder[i]] = i;

    return build(inorder, 0, n-1, postorder, 0, n-1);
}


TreeNode* build(vector<int>& inorder, int inStart, int inEnd,
                vector<int>& postorder, int postStart, int postEnd)
{
    if(inStart > inEnd)
        return NULL;

    int x = postorder[postEnd];

    if(inStart == inEnd)
        return new TreeNode(x);

    TreeNode* root = new TreeNode(x);

    int index = mp[x];

    int numbers = index-inStart;

    root->left = build(inorder, inStart, index-1, postorder, postStart, postStart+numbers-1);
    root->right = build(inorder, index+1, inEnd, postorder, postStart+numbers, postEnd-1);

    return root;
}

