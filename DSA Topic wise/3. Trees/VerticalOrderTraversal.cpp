/*

Given the root of a binary tree, calculate the vertical order traversal of the binary tree.

For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and
(row + 1, col + 1) respectively. The root of the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting
from leftmost column and ending on the rightmost column. There may be multiple nodes in the same row and same column.
In such a case, sort these nodes by their values.

*/

// Ambiguity in question
//      --> Print from leftmost column --> rightmost column while maintaining top --> bottom order
//      --> If rows are equal --> print smallest value node first



// Method-1 --> Storing in 2D vector & custom sorting

vector<vector<int>> mp;

static bool myComp(const vector<int>& a, const vector<int>& b)
{
    if(a[0] == b[0] && a[1] == b[1])        // same col & same row --> return smallest value
        return a[2] < b[2];

    else if(a[0] == b[0])                   // same col --> return smallest row
        return a[1] < b[1];

    return a[0] < b[0];                     // return smallest col
}


void preorder(TreeNode* root, int row, int col)
{
    if(!root)
        return;

    mp.push_back({col, row, root->val});

    preorder(root->left, row+1, col-1);
    preorder(root->right, row+1, col+1);
}


vector<vector<int>> verticalTraversal(TreeNode* root) {

    vector<vector<int>> result;
    vector<int> temp;

    preorder(root, 0, 0);
    sort(mp.begin(), mp.end(), myComp);

    int i=0;
    while(i < mp.size())
    {
        int x = mp[i][0];

        while(i < mp.size() && mp[i][0] == x)
        {
            temp.push_back(mp[i][2]);
            i++;
        }

        result.push_back(temp);
        temp.clear();
    }

    return result;
}



// Method-2 --> Using custom min-heap

struct myComp{

    bool operator()(const vector<int>& a, const vector<int>& b)
    {
        if(a[0] == b[0] && a[1] == b[1])        // same col & same row --> return smallest value
            return a[2] > b[2];

        else if(a[0] == b[0])                   // same col --> return smallest row
            return a[1] > b[1];

        return a[0] > b[0];                     // return smallest col
    }
};

priority_queue< vector<int>, vector<vector<int>>, myComp > pq;

void preorder(TreeNode* root, int row, int col)
{
    if(!root)
        return;

    pq.push({col, row, root->val});

    preorder(root->left, row+1, col-1);
    preorder(root->right, row+1, col+1);
}

vector<vector<int>> verticalTraversal(TreeNode* root) {

    preorder(root, 0, 0);
    vector<vector<int>> result;
    vector<int> temp;

    while(!pq.empty())
    {
        int col = pq.top()[0];        // grouping with column number

        while(!pq.empty() && pq.top()[0] == col)
        {
            temp.push_back(pq.top()[2]);
            pq.pop();
        }

        result.push_back(temp);
        temp.clear();
    }

    return result;
}


// Method-3 --> Map of < int, map of <int, multiSet> >    // < col, < row, nodes in sorted order> >

vector<vector<int>> verticalTraversal(TreeNode* root) {

    map<int, map<int, multiset<int>>> nodes;
    queue<pair<TreeNode*, pair<int, int>>> todo;

    todo.push({root, {0, 0}});

    while (!todo.empty())
    {
        auto p = todo.front();
        todo.pop();
        TreeNode* node = p.first;
        int x = p.second.first, y = p.second.second;
        nodes[x][y].insert(node -> val);

        if (node -> left)
            todo.push({node -> left, {x - 1, y + 1}});

        if (node -> right)
            todo.push({node -> right, {x + 1, y + 1}});
    }

    vector<vector<int>> ans;
    for (auto p : nodes)
    {
        vector<int> col;
        for (auto q : p.second) {
            col.insert(col.end(), q.second.begin(), q.second.end());
        }
        ans.push_back(col);
    }

    return ans;
}


