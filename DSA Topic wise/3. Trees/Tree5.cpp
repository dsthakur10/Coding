// Given the root of a binary tree, invert the tree, and return its root.

/*
                    4
            2               7
        1       3       6       9


Inverted tree:
                    4
            7               2
        9       6       3       1

*/

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
TreeNode* invertTree(TreeNode* root);
TreeNode* invertTree2(TreeNode* root);


int main()
{
    TreeNode *root = NULL;
/*
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
*/
    //insertNode(&root,100);

    for(int i=1; i<=15; i++)
        insertNode(&root,i);

    std::cout << "\nTree:\n";
    levelorder(root);

    std::cout << "\n\nInverted Tree: \n";
    //root = invertTree(root);
    root = invertTree2(root);

    levelorder(root);

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




TreeNode* invertTree(TreeNode* root)
{
    if(!root || (!root->left && !root->right))
        return root;

    TreeNode *temp;

    temp = root->left;
    root->left = root->right;
    root->right = temp;

    root->left = invertTree(root->left);
    root->right = invertTree(root->right);

    return root;
}



TreeNode* invertTree2(TreeNode* root)
{
    if(!root || (!root->left && !root->right))
        return root;

    std::queue<TreeNode*> q;
    TreeNode *temp, *cur;

    q.push(root);

    while(!q.empty())
    {
        cur = q.front();
        q.pop();

        temp = cur->left;
        cur->left = cur->right;
        cur->right = temp;

        //std::swap(cur->left,cur->right);

        if(cur->left)
            q.push(cur->left);

        if(cur->right)
            q.push(cur->right);

    }

    return root;
}
