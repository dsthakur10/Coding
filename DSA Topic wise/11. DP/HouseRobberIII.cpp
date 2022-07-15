
/*

The thief has found himself a new place for his thievery again. There is only 1 entrance to this area, called root.

Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that
all houses in this place form a binary tree. It will automatically contact the police if two directly-linked
houses were broken into on the same night.

Given the root of binary tree, return the maximum amount of money the thief can rob without alerting the police.

*/

unordered_map<TreeNode*, int> mp;
int maxSum = 0;

int rob(TreeNode* root) {
    solve(root);
    return maxSum;
}


int solve(TreeNode* root){
    if(!root)
        return 0;

    if(mp.find(root) != mp.end())
        return mp[root];

    if(!root->left && !root->right)
    {
        mp[root] = root->val;
        maxSum = max(maxSum, mp[root]);
        return mp[root];
    }

    int x = 0, y = 0;
    x = solve(root->left) + solve(root->right);     // Exclude current house

                                                // Include curent house
    if(root->left)
        y += solve(root->left->left) + solve(root->left->right);

    if(root->right)
        y += solve(root->right->left) + solve(root->right->right);

    mp[root] = max(x, y + root->val);

    maxSum = max(maxSum, mp[root]);

    return mp[root];
}
