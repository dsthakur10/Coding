// Given the root of a binary tree and an integer targetSum,
// return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

// A leaf is a node with no children.


#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include <algorithm>

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
bool hasPathSum(TreeNode* root, int targetSum);             // recursive way
bool hasPathSum2(TreeNode* root, int targetSum);            // iterative way

int main()
{
    TreeNode *root = NULL;
    int x;

    for(int i=1; i<=7; i++)
        insertNode(&root,i);

    std::cout << "\nTree:\n";
    levelorder(root);

    std::cout << "Enter the sum value: ";
    std::cin >> x;
    bool flag = hasPathSum2(root,x);

    if(flag)
        std::cout << "\n\nTRUE";
    else
        std::cout << "\n\nFALSE";

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
        int n = q.size();
        while(n>0)
        {
            temp = q.front();
            q.pop();

            std::cout<<temp->val<<' ';

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }
        std::cout << "\n";
    }
}


bool hasPathSum(TreeNode* root, int targetSum)
{
    if(!root)
        return false;

    if(!root->left && !root->right)
    {
        if(targetSum == root->val)
            return true;
        else
            return false;
    }

    bool l = hasPathSum(root->left, targetSum - root->val);

    bool r = hasPathSum(root->right, targetSum - root->val);

    return l || r;
}



bool hasPathSum2(TreeNode *root, int targetSum)
{
    if(!root)
        return false;

    std::stack<TreeNode*> path;
    std::stack<int> sub;

    path.push(root);
    sub.push(root->val);

    while(!path.empty())
    {
        TreeNode *temp = path.top();
        path.pop();
        int tempval = sub.top();
        sub.pop();

        if(!temp->left && !temp->right && tempval == targetSum)
            return true;

        else
        {
            if(temp->right)
            {
                path.push(temp->right);
                sub.push(temp->right->val + tempval);
            }

            if(temp->left)
            {
                path.push(temp->left);
                sub.push(temp->left->val + tempval);
            }
        }
    }

    return false;
}
