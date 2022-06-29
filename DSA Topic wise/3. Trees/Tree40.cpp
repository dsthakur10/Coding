// Two Sum IV - Input is a BST

/*

Given the root of a Binary Search Tree and a target number k, return true if there exist two elements in the BST
such that their sum is equal to the given target.

*/




// Method-1 --> O(n) time | O(n) space --> DOUBLE PASS

/*

This method also works for those who are not BSTs.
The idea is to use a hashtable to save the values of the nodes in the BST.
Each time when we insert the value of a new node into the hashtable, we check if the table contains k - node->val

*/

unordered_map<int, TreeNode*> mp;

bool findTarget(TreeNode* root, int k) {

    inorder(root);

    if(!root)
        return false;

    int target = k - root->val;

    if(mp.find(target) != mp.end() && mp[target] != root)
        return true;

    return findTarget(root->left, k) || findTarget(root->right, k);

}

void inorder(TreeNode* root)
{
    if(!root)
        return;

    inorder(root->left);

    mp[root->val] = root;

    inorder(root->right);
}



// Method-2 --> O(n) time | O(n) space --> SINGLE PASS

// Finding values on fly

unordered_map<int, TreeNode*> mp;

bool findTarget(TreeNode* root, int k) {

    if(!root)
        return false;

    int target = k - root->val;

    if(mp.find(target) != mp.end())
        return true;

    mp[root->val] = root;

    return findTarget(root->left, k) || findTarget(root->right, k);

}
