// Pendant node --> node which is connected to single node

/*

Given a binary tree in which each node element contains a number.
Find the maximum possible path sum from one leaf node to another leaf node.

*/


unordered_map<Node* , int> mp;
int maxSum = INT_MIN;

int solve(Node* root)
{
   if(!root)
        return 0;

    if(mp.find(root) != mp.end())
        return mp[root];

    if(!root->left && !root->right)
        return root->data;

    if(!root->left)
    {
        int rightSum = solve(root->right);
        mp[root] = root->data + rightSum;
    }

    else if(!root->right)
    {
        int leftSum = solve(root->left);
        mp[root] = root->data + leftSum;
    }

    else
    {
        int leftSum = solve(root->left);
        int rightSum = solve(root->right);
        mp[root] = root->data + max(leftSum, rightSum);
        int sum = root->data + leftSum + rightSum;
        maxSum = max(maxSum, sum);
    }

    return mp[root];
}


int maxPathSum(Node* root)
{
    int x = solve(root);

    if(!root->left || !root->right)
        maxSum = max(maxSum, x);

    return maxSum;
}
