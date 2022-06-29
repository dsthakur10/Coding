
// Path Sum II

/*

Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.



Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22
Example 2:


Input: root = [1,2,3], targetSum = 5
Output: []
Example 3:

Input: root = [1,2], targetSum = 0
Output: []

*/


// Method-1 --> Recursive (Pre-order traversal)
// Pass by value

vector<vector<int>> result;

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

    if(!root)
        return {};

    vector<int> output;
    inorderPathSum(root, targetSum, output);
    return result;

}

void inorderPathSum(TreeNode* root, int sum, vector<int> output)
{
    sum -= root->val;
    output.push_back(root->val);

    if(!root->left && !root->right)
    {
        if(sum == 0)
            result.push_back(output);
        return;
    }

    if(root->left)
        inorderPathSum(root->left, sum, output);

    if(root->right)
        inorderPathSum(root->right, sum, output);
}



// Pass by reference --> saves space

vector<vector<int>> result;

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

    if(!root)
        return {};

    vector<int> output;
    inorderPathSum(root, targetSum, output);
    return result;

}

void inorderPathSum(TreeNode* root, int sum, vector<int>& output)
{
    sum -= root->val;
    output.push_back(root->val);

    if(!root->left && !root->right)
    {
        if(sum == 0)
            result.push_back(output);

        output.pop_back();
        return;
    }

    if(root->left)
        inorderPathSum(root->left, sum, output);

    if(root->right)
        inorderPathSum(root->right, sum, output);

    output.pop_back();
}



// Method-2 --> Iterative (level-order traversal)

vector<vector<int>> result;

vector<vector<int>> pathSum(TreeNode* root, int targetSum) {

    if(!root)
        return {};

    queue<pair<TreeNode*,pair<int,vector<int>>>> q;

    q.push({root, {root->val, {root->val}}});

    while(!q.empty())
    {
        int n = q.size();

        while(n > 0)
        {
            TreeNode* node = q.front().first;
            int sum = q.front().second.first;
            vector<int> path = q.front().second.second;
            q.pop();

            if(!node->left && !node->right)
            {
                if(sum == targetSum)
                    result.push_back(path);
            }

            if(node->left)
            {
                path.push_back(node->left->val);
                q.push( {node->left,
                         {sum + node->left->val, path}} );
                path.pop_back();
            }

            if(node->right)
            {
                path.push_back(node->right->val);
                q.push( {node->right,
                         {sum + node->right->val, path}} );
                path.pop_back();
            }

            n--;
        }
    }

    return result;
}
