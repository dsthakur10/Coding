// Given an array of elements, our task is to construct a complete binary tree from this array in level order fashion.
// That is, elements from left in the array will be filled in the tree level wise starting from level 0.


// Array ==> 10,12,15,25,30,36

// Complete BT ==>
//                    10
//             12           15
//          25    30    36

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
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);
void inorder(TreeNode *root);

TreeNode* convertListToBT(std::vector<int> level, int i);


int main()
{
    std::vector<int> level = {1,2,3,4,5,6,7,8,9,10};

    TreeNode *root;
    root = convertListToBT(level,0);

    std::cout<<"Complete Binary Tree from given array: \n";
    levelorder(root);

    std::cout<<"\nInorder traversal: ";
    inorder(root);

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

        std::cout<<"\n";
    }
}


void inorder(TreeNode *root)
{
    if(!root)
        return;

    inorder(root->left);

    std::cout<<root->val<<" ";

    inorder(root->right);
}



TreeNode* convertListToBT(std::vector<int> level, int i)
{
    if(i >= level.size())
        return NULL;

    TreeNode *root = createNode(level[i]);

    root->left = convertListToBT(level, 2*i+1);
    root->right = convertListToBT(level, 2*i+2);

    return root;
}
