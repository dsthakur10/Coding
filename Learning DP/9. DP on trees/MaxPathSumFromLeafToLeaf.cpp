

/*

You are given a non-empty binary tree where each node has a non-negative integer value.
Return the maximum possible sum of path between any two leaves of the given tree.
The path is also inclusive of the leaf nodes and the maximum path sum may or may not go through the root of
the given tree.

If there is only one leaf node in the tree, then return -1.

*/

long long int maxSum = -1;
std::tr1::unordered_map<TreeNode<int> *, long long int> mp;

long long int solve(TreeNode<int> *root)
{
    if(!root)
        return 0;

    if(mp.find(root) != mp.end())
        return mp[root];

    if(!root->left && !root->right)
        return root->val;

    if(!root->left)
    {
        long long int rightSum = solve(root->right);
        mp[root] = root->val + rightSum;
    }

    else if(!root->right)
    {
        long long int leftSum = solve(root->left);
        mp[root] = root->val + leftSum;
    }

    else
    {
        long long int leftSum = solve(root->left);
        long long int rightSum = solve(root->right);
        mp[root] = root->val + max(leftSum, rightSum);
        long long int sum = root->val + leftSum + rightSum;
        maxSum = max(maxSum, sum);
    }

    return mp[root];
}


long long int findMaxSumPath(TreeNode<int> *root)
{
    maxSum = -1;
    mp.clear();
    solve(root);
    return maxSum;
}
