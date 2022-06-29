// Binary Tree Level Order Traversal II

/*

Given the root of a binary tree, return the bottom-up level order traversal of its nodes' values.
(i.e., from left to right, level by level from leaf --> root).

*/



// Method-1 --> Reverse the output of top-down approach

vector<vector<int>> levelOrderBottom(TreeNode* root)
{
    if(!root)
        return {};

    vector<vector<int>> tree;
    vector<int> level;
    queue<TreeNode*> q;

    q.push(root);

    while(!q.empty())
    {
        int n = q.size();

        while(n > 0)
        {
            TreeNode* cur = q.front();
            q.pop();

            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);

            level.push_back(cur->val);
            n--;
        }

        //tree.insert(tree.begin(), level);
        tree.push_back(level);
        level.clear();
    }

    reverse(tree.begin(), tree.end());
    return tree;
}



// Method-2 -->

