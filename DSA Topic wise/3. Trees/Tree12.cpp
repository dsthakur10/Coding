// Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree,
// CONSTRUCT AND RETURN THE BINARY TREE.


/*
    - preorder and inorder consist of UNIQUE values.
    - Each value of inorder also appears in preorder.
    - preorder is guaranteed to be the preorder traversal of the tree.
    - inorder is guaranteed to be the inorder traversal of the tree.

*/

#include<iostream>
#include<queue>
#include<stack>
#include<vector>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x, TreeNode *lptr, TreeNode *rptr)
    {
        val = x;
        left = lptr;
        right = rptr;
    }
};


TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                     // iterative way (using queue)
void levelorder(TreeNode *root);

int findIndex(std::vector<int>& inorder, int key);
TreeNode* build(std::vector<int>& preorder, std::vector<int>& inorder, int len);
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder);

int main()
{
    std::vector<int> in,pre;

    pre = {1,2,4,5,3,6,7,8};
    in = {4,2,5,1,3,7,6,8};

    TreeNode *root = buildTree(pre,in);

    std::cout << "\nTree :\n";

    levelorder(root);

    return 0;
}



TreeNode* createNode(int x)
{
    TreeNode *ptr = new TreeNode(x);
    return ptr;
}



void insertNode(TreeNode **root,int x)
{
    if(!(*root))
    {
        *root = createNode(x);
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *ptr , *temp;
    ptr = createNode(x);

    q.push(*root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(!temp->left)
        {
            temp->left = ptr;
            return;
        }

        if(!temp->right)
        {
            temp->right = ptr;
            return;
        }

        q.push(temp->left);
        q.push(temp->right);
    }
}



void levelorder(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode* temp;

    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        std::cout<<temp->val<<' ';

        if(temp->left)
            q.push(temp->left);

        if(temp->right)
            q.push(temp->right);
    }
}



int findIndex(std::vector<int>& inorder, int key, int len)
{
    for(int i=0;i<len;i++)
    {
        if(inorder[i] == key)
            return i;
    }

    return -1;
}



TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
{
    int len = preorder.size();

    return build(preorder, inorder, len);
}



TreeNode* build(std::vector<int>& preorder, std::vector<int>& inorder, int len)
{
/*
    if(len == 0)
        return NULL;
*/
    int index, key;

    key = preorder[0];

    index = findIndex(inorder,key,len);

    TreeNode *root = createNode(key);

    if(index != 0)
    {
        std::vector<int> pre1(preorder.begin()+1,preorder.begin()+index);
        std::vector<int> in1(inorder.begin(), inorder.begin()+index-1);

        root->left = build(pre1, in1, index);
    }

    if(index != len-1)
    {
        std::vector<int> pre2(preorder.begin()+index+1, preorder.end()-1);
        std::vector<int> in2(inorder.begin()+index+1, inorder.end()-1);

        root->right = build(pre2, in2, len-index-1);
    }

    return root;
}
