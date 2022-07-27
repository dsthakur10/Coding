/*

A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge
connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass
through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path

*/



// store maximum path sum ending at vertex 'v'
int maxSum = INT_MIN;

int maxPathSum(TreeNode* root) {

    solve(root);
    return maxSum;
}

int solve(TreeNode* root)
{
    if(!root)
        return 0;

    if(!root->left && !root->right)
    {
        maxSum = max(maxSum, root->val);
        return root->val;
    }

    int leftSum = solve(root->left);
    int rightSum = solve(root->right);

    int maxLeftRight = max(leftSum, rightSum);
    int maxSumUntilRoot = max(root->val, root->val + maxLeftRight);
    int localMax = max(root->val + leftSum + rightSum, maxSumUntilRoot);

    maxSum = max(maxSum, localMax);

    return maxSumUntilRoot;
}
