

TreeNode* sortedArrayToBST(vector<int>& nums)
{
    if(nums.empty())
        return NULL;

    if(nums.size() == 1)
        return new TreeNode(nums[0]);

    int mid = nums.size()/2;

    TreeNode *root = new TreeNode(nums[mid]);

    vector<int> left(nums.begin(), nums.begin() + mid);
    vector<int> right(nums.begin() + mid + 1, nums.end());

    root->left = sortedArrayToBST(left);
    root->right = sortedArrayToBST(right);

    return root;
}




TreeNode* sortedArrayToBST2(vector<int>& nums)
{
    int n = nums.size();

    return constructBST(nums, 0, n-1);
}

TreeNode* constructBST(vector<int>& nums, int start, int end)
{
    if(start > end)
        return NULL;

    if(start == end)
        return new TreeNode(nums[start]);

    int mid = (start + end)/2;

    TreeNode *root = new TreeNode(nums[mid]);

    root->left = constructBST(nums, start, mid-1);
    root->right = constructBST(nums, mid+1, end);

    return root;

}
