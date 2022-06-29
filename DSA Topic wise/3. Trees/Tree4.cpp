// Given the root of a binary tree, return its maximum depth.

// A binary tree's maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.


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
int maxDepth(TreeNode* root);
int maxDepth2(TreeNode* root);

int main()
{
    TreeNode *root = NULL;
/*
    insertNode(&root,5);
    insertNode(&root,7);
    insertNode(&root,69);
    insertNode(&root,11);
    insertNode(&root,100);
    insertNode(&root,12);
    insertNode(&root,8);

*/

    insertNode(&root,100);
    insertNode(&root,22);
    insertNode(&root,35);
    insertNode(&root,4);
    insertNode(&root,15);

    TreeNode *temp = root;

    while(temp->right)
        temp = temp->right;

    temp->right = createNode(70);
    temp = temp->right;

    temp->left = createNode(12);
    temp->right = createNode(5);

    //insertNode(&root,100);

    std::cout << "\nTree:\n";
    levelorder(root);

    std::cout << "\n\nMax height of Tree = "<< maxDepth2(root);

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


int maxDepth(TreeNode* root)
{
    if(!root)
        return 0;

    int l = 1 + maxDepth(root->left);
    int r = 1 + maxDepth(root->right);

    return std::max(l,r);
}


int maxDepth2(TreeNode* root)
{
    if(!root)
        return 0;

    int height = 0;

    std::queue<TreeNode *> q;
    TreeNode *temp;

    q.push(root);
    while(!q.empty())
    {
        int n = q.size();

        height++;
        while(n>0)
        {
            temp = q.front();
            q.pop();

            if(temp->left)
                q.push(temp->left);
            if(temp->right)
                q.push(temp->right);

            n--;
        }
    }

    return height;
}
