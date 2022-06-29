// Construct Binary Tree from Preorder and Inorder Traversal

/*
    Divide & conquer approach --> Divide array into 2 halves to get 2 SUBTREES:
    T(n) = T(x) + T(n-x-1) + work done

    Best case --> x = n/2       (Balanced BT)
    Worst case --> x = n-1      (Skewed Tree)

    Method-1 --> work done = O(n) --> Searching for root node linearly in INORDER array
    Method-2 --> work done = O(1) --> Searching for root node in constant time using HashMap

    Worst case:
    Method-1 --> T(n) = T(n-1) + O(n) = O(n^2)
    Method-2 --> T(n) = T(n-1) + O(1) = O(n)

*/

// Method-1 --> O(n^2) --> Linear Search everytime in every call

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
{
    int n = inorder.size();

    return build(preorder, 0, n-1, inorder, 0, n-1);
}


TreeNode* build(vector<int>& preorder, int preStart, int preEnd, vector<int>& inorder, int inStart, int inEnd)
{
    if(inStart > inEnd)
        return NULL;

    int x = preorder[preStart];

    if(inStart == inEnd)
        return new TreeNode(x);

    TreeNode* root = new TreeNode(x);

    int index = searchNode(inorder, inStart, inEnd, x);

//      root->left = build(preorder, preStart+1, index, inorder, inStart, index-1);
//      root->right = build(preorder, index+1, preEnd, inorder, index+1, inEnd);

    int numbers = index-inStart;

    root->left = build(preorder, preStart+1, preStart+numbers, inorder, inStart, index-1);
    root->right = build(preorder, preStart+numbers+1, preEnd, inorder, index+1, inEnd);

    return root;
}


int searchNode(vector<int>& inorder, int low, int high, int key)
{
    for(int i=low; i<=high; i++)
    {
        if(inorder[i] == key)
            return i;
    }

    return -1;
}




// Method-2 --> Search using unordered_map --> Time = O(n) even when tree is skewed | Space = O(n)

unordered_map<int, int> mp;

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

    int n = inorder.size();

    // storing indexes in map to reduce search time to O(1)
    for(int i=0; i<n; i++)
        mp[inorder[i]] = i;

    return build(preorder, 0, n-1, inorder, 0, n-1);
}


TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                vector<int>& inorder, int inStart, int inEnd)
{
    if(inStart > inEnd)
        return NULL;

    int x = preorder[preStart];

    if(inStart == inEnd)
        return new TreeNode(x);

    TreeNode* root = new TreeNode(x);

//      int index = searchNode(inorder, inStart, inEnd, x);

//      root->left = build(preorder, preStart+1, index, inorder, inStart, index-1);
//      root->right = build(preorder, index+1, preEnd, inorder, index+1, inEnd);

    int index = mp[x];

    int numbers = index-inStart;

    root->left = build(preorder, preStart+1, preStart+numbers, inorder, inStart, index-1);
    root->right = build(preorder, preStart+numbers+1, preEnd, inorder, index+1, inEnd);

    return root;
}
