// Validate Binary Search Tree

/*

Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:

    - The left subtree of a node contains only nodes with keys less than the node's key.
    - The right subtree of a node contains only nodes with keys greater than the node's key.
    - Both the left and right subtrees must also be binary search trees.

Example 1:
Input: root = [2,1,3]
Output: true

Example 2:
Input: root = [5,1,4,null,null,3,6]
Output: false
Explanation: The root node's value is 5 but its right child's value is 4.

Constraints:

The number of nodes in the tree is in the range [1, 10^4].
-2^31 <= Node.val <= 2^31 - 1

*/


//

bool isValidBST(TreeNode* root) {

    long minimum = LONG_MIN, maximum = LONG_MAX;

    return valid(root, minimum, maximum);
}

bool valid(TreeNode* root, long minimum, long maximum)
{
    if(!root)
        return true;

    if(root->val <= minimum || root->val >= maximum)
        return false;

    bool l = valid(root->left, minimum, root->val);
    bool r = valid(root->right, root->val, maximum);

    return l && r;
}


// Method-2 --> Iterative In-order to keep track of values --> Since inorder traversal will always give you ASC order

bool isValidBST(TreeNode* root)
{
    if(!root || (!root->left && !root->right))
        return true;

    stack<TreeNode*> st;
    TreeNode *cur;
    int temp;
    bool flag = true;

    st.push(root);
    cur = root->left;

    while(cur || !st.empty())
    {
        while(cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top();
        st.pop();

        if(flag)
        {
            flag = false;
        }

        else
        {
            if(temp >= cur->val)
                return false;
        }

        temp = cur->val;
        cur = cur->right;
    }

    return true;
}
