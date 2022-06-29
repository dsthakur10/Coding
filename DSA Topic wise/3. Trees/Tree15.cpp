//  Minimum Depth of Binary Tree

/*

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

*/


// This is not as simple as you think it is just like maximum depth of Binary tree --> Read definition carefully
// Min Depth --> Shortest path from root -> leaf --> Leaf must exist for a path to be candidate of answer

    /*
        int minDepth(TreeNode* root) {

            if(!root)
                return 0;

            int l = minDepth(root->left);
            int r = minDepth(root->right);

            return 1 + min(l,r);

        }
    */

// If we modify maximum Depth by applying min in place of max, our result will be wrong.
// This will fetch minimum height even when leaf nodes are not available, as its only work is to find minimum of 2
// We have to make sure there exist a leaf node before applying our function recursively.


int minDepth(TreeNode* root)
{
    if(!root)
        return 0;

    int depth;

    if(root->left && root->right)                                       // both LST & RST exist. Find minimum
        depth = 1 + min(minDepth(root->left), minDepth(root->right));

    else if(root->left)                                                 // Only LST exist. Return its height
        depth = 1 + minDepth(root->left);

    else if(root->right)                                                // Only RST exist. Return its height
        depth = 1 + minDepth(root->right);

    else                                                                // leaf node --> return 1
        depth = 1;

    return depth;
}
