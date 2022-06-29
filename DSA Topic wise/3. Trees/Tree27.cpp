// Binary Tree Paths

/*
Given the root of a binary tree, return all root-to-leaf paths in any order.

A leaf is a node with no children.
*/


vector<string> result;

vector<string> binaryTreePaths(TreeNode* root) {

    if(!root)
        return {};

    string output;
    inorder(root, output);
    return result;
}

void inorder(TreeNode* root, string output)
{
    output += to_string(root->val);

    if(!root->left && !root->right)
    {
        result.push_back(output);
        return;
    }

    if(root->left)
        inorder(root->left, output + "->");
    if(root->right)
        inorder(root->right, output + "->");

}
