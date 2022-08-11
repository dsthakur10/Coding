

// WRONG method --> Cannot use DFS traversals in this problem since DFS not always give
// 1st node in column as top-most node
// Need to add extra parameter like height to take the decision

map<int, int> mp;

// every column's first element is to be placed
void preorder(Node *root, int row, int col)
{
    if(!root)
        return;

    if(mp.find(col) == mp.end())
        mp[col] = root->data;

    preorder(root->left, row+1, col-1);
    preorder(root->right, row+1, col+1);
}


vector<int> topView(Node *root)
{
    vector<int> result;
    preorder(root, 0, 0);

    for(auto it = mp.begin(); it != mp.end(); it++)
    {
        result.push_back(it->second);
    }

    return result;
}




// BFS
map<int, int> mp;

vector<int> topView(Node *root)
{
    vector<int> result;
    queue<pair<Node*, int>> q;

    q.push({root, 0});

    while(!q.empty())
    {
        Node* cur = q.front().first;
        int col = q.front().second;
        q.pop();

        if(mp.find(col) == mp.end())
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
