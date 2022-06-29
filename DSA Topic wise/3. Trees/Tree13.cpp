// Binary Tree Zigzag Level Order Traversal

/*
Given the root of a binary tree, return the zigzag level order traversal of its nodes' values.
(i.e., from left to right, then right to left for the next level and alternate between)

*/


// Method-1 --> DEQUE

// flag = true --> Left->right (POP from FRONT | PUSH at BACK) --> Left-pointer before Right-pointer
// flag = false --> right->left (POP from BACK | PUSH at FRONT) --> Right-pointer before Left-pointer

vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
    if(!root)
        return {};

    vector<vector<int>> tree;
    vector<int> level;
    deque<TreeNode*> dq;

    dq.push_front(root);
    bool flag = true;

    while(!dq.empty())
    {
        int n = dq.size();

        if(flag)
        {
            while(n > 0)
            {
                TreeNode* cur = dq.front();
                dq.pop_front();

                if(cur->left)
                    dq.push_back(cur->left);

                if(cur->right)
                    dq.push_back(cur->right);

                level.push_back(cur->val);
                n--;
            }
        }

        else
        {
            while(n > 0)
            {
                TreeNode* cur = dq.back();
                dq.pop_back();

                if(cur->right)
                    dq.push_front(cur->right);

                if(cur->left)
                    dq.push_front(cur->left);

                level.push_back(cur->val);
                n--;
            }
        }

        tree.push_back(level);
        level.clear();
        flag = !flag;
    }

    return tree;
}



// Method-2 --> 2 stacks

// flag = true --> Left->right (POP from s1 | PUSH into s2)
// flag = false --> right->left (POP from s2 | PUSH into s1)

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

    if(!root)
        return {};

    vector<vector<int>> tree;
    vector<int> level;
    stack<TreeNode*> s1, s2;

    s1.push(root);
    bool flag = true;

    while(!s1.empty() || !s2.empty())
    {
        if(flag)
        {
            while(!s1.empty())
            {
                TreeNode* cur = s1.top();
                s1.pop();

                if(cur->left)
                    s2.push(cur->left);

                if(cur->right)
                    s2.push(cur->right);

                level.push_back(cur->val);
            }
        }

        else
        {
            while(!s2.empty())
            {
                TreeNode* cur = s2.top();
                s2.pop();

                if(cur->right)
                    s1.push(cur->right);

                if(cur->left)
                    s1.push(cur->left);

                level.push_back(cur->val);
            }
        }

        tree.push_back(level);
        level.clear();
        flag = !flag;
    }

    return tree;
}
