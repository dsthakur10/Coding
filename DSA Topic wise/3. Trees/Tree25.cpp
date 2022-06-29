// Maximum Width of Binary Tree

/*

Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes),
where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that
level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed integer.

Example 1:
Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).

Example 2:
Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).

Example 3:
Input: root = [1,3,2,5]
Output: 2
Explanation: The maximum width exists in the second level with length 2 (3,2).

*/



// Calculate the index of nodes to be pushed onto queue alongside pushing nodes. Indexing is done as follows:
//      Left child = 2*parent
//      Right child = 2*parent + 1
// Difference between 1st node index & last node index of each level is width of level. Get the max of all width
// "uint_64" is used because 2*parent on a skew tree is an overkill for "int"


int widthOfBinaryTree(TreeNode* root) {

    if(!root)
        return 0;

    uint64_t maxWidth = 0;
    queue<pair<TreeNode*, uint64_t>> q;
    q.push({root, 1});

    while(!q.empty())
    {
        int n = q.size();
        uint64_t width = q.back().second - q.front().second + 1;
        maxWidth = max(maxWidth, width);

        while(n>0)
        {
            TreeNode* cur = q.front().first;
            uint64_t number = q.front().second;
            q.pop();

            if(cur->left)
            {
                q.push({cur->left, 2*number});
            }

            if(cur->right)
            {
                q.push({cur->right, 2*number+1});
            }

            n--;
        }
    }

    return maxWidth;
}
