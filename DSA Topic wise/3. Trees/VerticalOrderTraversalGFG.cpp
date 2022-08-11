
/*


*/

struct myComp{

    bool operator()(const vector<int>& a, const vector<int>& b)
    {
        if(a[0] == b[0] && a[1] == b[1])
            return a[2] > b[2];

        else if(a[0] == b[0])
            return a[1] > b[1];

        return a[0] > b[0];
    }
};

priority_queue< vector<int>, vector<vector<int>>, myComp > pq;
int counter = 0;

void preorder(Node* root, int row, int col)
{
    if(!root)
        return;

    counter++;
    pq.push({col, row, counter, root->data});

    preorder(root->left, row+1, col-1);
    preorder(root->right, row+1, col+1);
}

vector<int> verticalOrder(Node *root)
{
    preorder(root, 0, 0);
    vector<int> result;

    while(!pq.empty())
    {
        result.push_back(pq.top()[3]);
        pq.pop();
    }

    return result;
}
