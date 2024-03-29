
map<int, int> mp;

vector<int> bottomView(Node *root)
{
    vector<int> result;
    queue<pair<Node*, int>> q;

    q.push({root, 0});

    while(!q.empty())
    {
        Node* cur = q.front().first;
        int col = q.front().second;
        q.pop();

        mp[col] = cur->data;

        if(cur->left)
            q.push({cur->left, col-1});

        if(cur->right)
            q.push({cur->right, col+1});
    }

    for(auto it : mp)
        result.push_back(it.second);

    return result;
}

