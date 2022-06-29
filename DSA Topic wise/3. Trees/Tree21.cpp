// Binary Tree Right Side View

/*
Given the root of a binary tree, imagine yourself standing on the right side of it, return the values of the nodes
you can see ordered from top to bottom.

Example 1:
Input: root = [1,2,3,null,5,null,4]
Output: [1,3,4]

Example 2:
Input: root = [1,null,3]
Output: [1,3]

Example 3:
Input: root = []
Output: []

*/



// Method-1 --> Reverse level order traversal

vector<int> rightSideView(TreeNode* root)
{
    if(!root)
        return {};

    vector<int> result;
    queue<TreeNode*> q;

    q.push(root);

    while(!q.empty())
    {
        int n = q.size();
        bool flag = true;

        while(n > 0)
        {
            TreeNode* cur = q.front();
            q.pop();

            // Push right child before left child to get level rightmost node first
            if(cur->right)
                q.push(cur->right);

            if(cur->left)
                q.push(cur->left);

            // flag is used to just print the first node which is rightmost node as well.
            if(flag)
            {
                result.push_back(cur->val);
                flag = !flag;
            }

            n--;
        }
    }

    return result;
}



// Method-2 --> Modified Reverse PreOrder traversal

/*

We will push one element at each level. So, size of the result vector will actually be equal to number of levels
we have already stored the result. If the level of some element is more than the size of result vector that means
this will be a new level for which we have not pushed anything in the result vector. So, we will push this element
in the result vector. The size of result in next iterations will increase by one and for all the other elements
in same level result.size() > level will be false

*/


vector<int> rightSideView2(TreeNode* root)
{
    vector<int> result;

    preorder(root, result, 1);

    return result;
}

void preorder(TreeNode* root, vector<int>& result, int level)
{
    if(!root)
        return;

    if(result.size() < level)
        result.push_back(root->val);

    preorder(root->right, result, level+1);
    preorder(root->left, result, level+1);
}
