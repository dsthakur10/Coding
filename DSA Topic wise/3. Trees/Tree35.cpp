
// Flatten Binary Tree to Linked List

/*

Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the
list and the left child pointer is always null.

NOTE: The "linked list" should be in the same order as a "pre-order" traversal of the binary tree.


Example 1:
Input: root = [1,2,5,3,4,null,6]
Output: [1,null,2,null,3,null,4,null,5,null,6]

Example 2:
Input: root = []
Output: []

Example 3:
Input: root = [0]
Output: [0]

*/


// Method-1 --> Inverse PostOrder

// Result must be in preorder traversal of tree --> Root -> Left -> Right
// We will do reverse of preOrder traversal, i.e. Inverse PostOrder --> Right --> Left --> Root

TreeNode* prev = NULL;

void flatten(TreeNode* root)
{
    if(!root)
        return;

    flatten(root->right);
    flatten(root->left);

    root->right = prev;
    prev = root;
    root->left = NULL;
}



// Method-2 --> Iterative Preorder Traversal --> STACK

// NOT IN-PLACE solution as asked in question

void flatten(TreeNode* root) {

    if(!root)
        return;

    stack<TreeNode*> st;
    st.push(root);

    TreeNode *prev = NULL, *cur = NULL;
    while(!st.empty())
    {
        cur = st.top();
        st.pop();

        if(prev)
        {
            prev->right = cur;
            cur->left = NULL;
        }

        if(cur->right)
            st.push(cur->right);

        if(cur->left)
            st.push(cur->left);

        prev = cur;
    }
}
