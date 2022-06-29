// Delete Node in a BST

/*

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:
    - Search for a node to remove.
    - If the node is found, delete the node.

Constraints:
    Each node has a unique value.
    root is a valid binary search tree.

*/

TreeNode* parent = NULL;

TreeNode* deleteNode(TreeNode* root, int key)
{
    TreeNode* node = searchNode(root, key);

    if(!node)
        return root;

    // case-1: Internal node with 2 children

    if(node->left && node->right)
    {
        TreeNode* succ = findSuccessor(node);
        int value = succ->val;

        parent = NULL;
        deleteNode(root, value);
        node->val = value;
    }

    // case-2: Internal node with 1 child

    else if(node->left || node->right)
    {
        if(node->right)
        {
            if(!parent)
            {
                TreeNode *newRoot = node->right;
                node->right = NULL;
                return newRoot;
            }

            else if(parent->left == node)
            {
                parent->left = node->right;
                node->right = NULL;
            }

            else
            {
                parent->right = node->right;
                node->right = NULL;
            }
        }

        else
        {
            if(!parent)
            {
                TreeNode *newRoot = node->left;
                node->left = NULL;
                return newRoot;
            }

            else if(parent->left == node)
            {
                parent->left = node->left;
                node->left = NULL;
            }

            else
            {
                parent->right = node->left;
                node->left = NULL;
            }
        }
    }

    // case-3: leaf node

    else
    {
        if(!parent)
            return NULL;

        if(parent->left == node)
            parent->left = NULL;

        else
            parent->right = NULL;
    }

    return root;
}


TreeNode* searchNode(TreeNode* root, int key)
{
    TreeNode* temp = root;

    while(temp)
    {
        if(temp->val == key)
            return temp;

        else if(temp->val < key)
        {
            parent = temp;
            temp = temp->right;
        }

        else
        {
            parent = temp;
            temp = temp->left;
        }

    }

    return NULL;
}


TreeNode* findSuccessor(TreeNode* root)
{
    TreeNode* temp = root->left;

    while(temp->right)
        temp = temp->right;

    return temp;
}
