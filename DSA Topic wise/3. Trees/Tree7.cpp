// Given the root of a binary tree, return the level order traversal of its nodes' values. (i.e., from left to right, level by level).


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
std::vector<std::vector<int>> levelOrder(TreeNode* root);


int main()
{
    std::vector<std::vector<int>> nodes;
    TreeNode *root = NULL;
    int x;

    for(int i=1; i<=7; i++)
        insertNode(&root,i);

    nodes = levelOrder(root);

    std::cout << "\nTree:\n";
    for(int i=0;i<nodes.size();i++)
    {
        for(int j=0;j<nodes[i].size();j++)
            std::cout << nodes[i][j]<< " ";
    }

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



std::vector<std::vector<int>> levelOrder(TreeNode* root)
{
    if(!root)
        return {};

    std::queue<TreeNode*> q;
    TreeNode* temp;
    std::vector<std::vector<int>> nodes;
    std::vector<int> level;

    q.push(root);

    while(!q.empty())
    {
        int n = q.size();

        while(n>0)
        {
            temp = q.front();
            q.pop();

            level.push_back(temp->val);

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }

        nodes.push_back(level);
        level.clear();
    }

    return nodes;
}


