// Trim a Binary Search Tree


/*

Given the root of a binary search tree and the lowest and highest boundaries as low and high, trim the tree
so that all its elements lies in [low, high]. Trimming the tree should not change the relative structure of the
elements that will remain in the tree (i.e., any node's descendant should remain a descendant).
It can be proven that there is a unique answer.

Return the root of the trimmed binary search tree. Note that the root may change depending on the given bounds.

Example 1:
Input: root = [1,0,2], low = 1, high = 2
Output: [1,null,2]

Example 2:
Input: root = [3,0,4,null,2,null,null,1], low = 1, high = 3
Output: [3,2,null,1]


Constraints:

The number of nodes in the tree is in the range [1, 10^4].
0 <= Node.val <= 10^4
THE VALUE OF EACH NODE IN THE TREE IS UNIQUE.
root is guaranteed to be a valid binary search tree.
0 <= low <= high <= 10^4

*/



/*

Maintain parent pointer for each node in the same recursive call.
Logic is to put a check on each node.
    1. node->val > high --> Remove node & entire RST --> Connect LST to its parent --> parent->right = node->left
    2. node->val < low --> Remove node & entire LST --> Connect LST to its parent --> parent->left = node->right

Only thing to take care of is original ROOT node --> Change the root node if it violates the rule

*/


TreeNode* trimBST(TreeNode* root, int low, int high)
{
    if(!root)
        return NULL;

    while(root && (root->val < low || root->val > high))
    {
        if(root->val < low)
        {
            TreeNode* temp = root->right;
            root->right = NULL;
            root = temp;
        }

        else if(root->val > high)
        {
            TreeNode* temp = root->left;
            root->left = NULL;
            root = temp;
        }
    }

    trim(root, low, high, NULL);
    return root;
}


void trim(TreeNode* root, int low, int high, TreeNode* parent)
{
    if(!root)
        return;

    if(root->val < low)
    {
        parent->left = root->right;
        root->right = NULL;
        trim(parent->left, low, high, parent);
    }

    else if(root->val > high)
    {
        parent->right = root->left;
        root->left = NULL;
        trim(parent->right, low, high, parent);
    }

    trim(root->left, low, high, root);
    trim(root->right, low, high, root);
}




// Method-2 --> Better code

TreeNode* trimBST(TreeNode* root, int low, int high) {

    if(!root)
        return NULL;

    TreeNode* newRoot = root;

    trim(root, low, high, NULL, &newRoot);
    return newRoot;
}

void trim(TreeNode* root, int low, int high, TreeNode* parent, TreeNode** newRoot)
{
    if(!root)
        return;

    if(root->val < low)
    {
        if(!parent)
        {
            TreeNode* temp = root->right;
            root->right = NULL;
            *newRoot = temp;

            trim(temp, low, high, NULL, newRoot);
        }

        else
        {
            parent->left = root->right;
            root->right = NULL;

            trim(parent->left, low, high, parent, newRoot);
        }
    }

    else if(root->val > high)
    {
        if(!parent)
        {
            TreeNode* temp = root->left;
            root->left = NULL;
            *newRoot = temp;

            trim(temp, low, high, NULL, newRoot);
        }

        else
        {
            parent->right = root->left;
            root->left = NULL;

            trim(parent->right, low, high, parent, newRoot);
        }
    }

    trim(root->left, low, high, root, newRoot);
    trim(root->right, low, high, root, newRoot);
}
