

// Queue & reversing the array according to the level number

vector<vector<int>> zigzagLevelOrder(TreeNode* root)
{
    if(!root)
        return {};

    queue<TreeNode*> q;
    vector<vector<int>> result;
    vector<int> temp;
    TreeNode* cur;

    int counter = 1;
    q.push(root);

    while(!q.empty())
    {
        int n = q.size();

        while(n>0)
        {
            cur = q.front();
            q.pop();

            if(cur->left)
                q.push(cur->left);

            if(cur->right)
                q.push(cur->right);

            temp.push_back(cur->val);
            n--;
        }

        if(counter % 2 == 0)
            reverse(temp.begin(), temp.end());

        result.push_back(temp);
        counter++;
        temp.clear();
    }

    return result;
}


// Dequeu --> push from both sides according to level number

vector<vector<int>> zigzagLevelOrder2(TreeNode* root)
{
    if(!root)
        return {};

    deque<TreeNode*> dq;
    vector<vector<int>> result;
    vector<int> temp;
    TreeNode* cur;

    bool flag = true;
    dq.push_back(root);

    while(!dq.empty())
    {
        int n = dq.size();

        while(n>0)
        {
            if(flag)
            {
                cur = dq.front();
                dq.pop_front();

                if(cur->left)
                    dq.push_back(cur->left);

                if(cur->right)
                    dq.push_back(cur->right);
            }

            else
            {
                cur = dq.back();
                dq.pop_back();

                if(cur->right)
                    dq.push_front(cur->right);

                if(cur->left)
                    dq.push_front(cur->left);

            }

            temp.push_back(cur->val);
            n--;
        }

        result.push_back(temp);
        flag = !flag;
        temp.clear();
    }

    return result;
}


// 2 stacks --> 1st stack prints from left->right. 2nd prints from right->left.

vector<vector<int>> zigzagLevelOrder3(TreeNode* root)
{
    if(!root)
        return {};

    vector<vector<int>> result;
    vector<int> temp;
    stack<TreeNode*> curSt;
    stack<TreeNode*> nextSt;
    TreeNode *cur;

    curSt.push(root);

    while(!curSt.empty() || !nextSt.empty())
    {
        while(!curSt.empty())
        {
            cur = curSt.top();
            curSt.pop();

            if(cur->left)
                nextSt.push(cur->left);

            if(cur->right)
                nextSt.push(cur->right);

            temp.push_back(cur->val);
        }

        if(!temp.empty())
        {
            result.push_back(temp);
            temp.clear();
        }

        while(!nextSt.empty())
        {
            cur = nextSt.top();
            nextSt.pop();

            if(cur->right)
                curSt.push(cur->right);

            if(cur->left)
                curSt.push(cur->left);

            temp.push_back(cur->val);
        }

        if(!temp.empty())
        {
            result.push_back(temp);
            temp.clear();
        }
    }

    return result;
}
