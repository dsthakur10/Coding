vector<int> result;

void preorder(Node *root)
{
    if(!root)
        return;

    if(!root->left && !root->right)
    {
        result.push_back(root->data);
        return;
    }

    preorder(root->left);
    preorder(root->right);
}

void leftBoundary(Node *root)
{
    Node* temp = root;

    while(temp)
    {
        // break out of loop when leaf is encountered
        if(!temp->left && !temp->right)
            break;

        result.push_back(temp->data);

        if(temp->left)
            temp = temp->left;

        else if(temp->right)
            temp = temp->right;
    }
}


void rightBoundary(Node *root)
{
    vector<int> vec;
    Node* temp = root;

    while(temp)
    {
        // break out of loop when leaf is encountered
        if(!temp->left && !temp->right)
            break;

        vec.push_back(temp->data);

        if(temp->right)
            temp = temp->right;

        else if(temp->left)
            temp = temp->left;
    }

    // insert elements in reverse order
    for(int i=vec.size()-1; i>=0; i--)
        result.push_back(vec[i]);
}

vector <int> boundary(Node *root)
{
    result.push_back(root->data);

    // traverse only if left-child exist
    if(root->left)
        leftBoundary(root->left);

    // traverse only if child exist
    if(root->left || root->right)
        preorder(root);

    // traverse only if right-child exist
    if(root->right)
        rightBoundary(root->right);

    return result;
}
