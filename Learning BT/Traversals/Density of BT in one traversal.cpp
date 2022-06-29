// Find density of BT in one traversal

// Density = Size/height

#include<iostream>
#include<queue>
#include<stack>
#include<deque>
#include<vector>
#include<algorithm>

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
void insertNode(TreeNode **root,int x);                         // iterative way (using queue)
void levelorder(TreeNode *root);

float densityOfBT(TreeNode *root);                              // iterative
float densityOfBT2(TreeNode *root);                             // recursive

int heightAndSize(TreeNode *root,int& length);

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

    for(int i=1; i<=27; i++)
        insertNode(&root,i);


    levelorder(root);

    std::cout<<"\n\nDensity of Binary tree = "<<densityOfBT2(root);

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

        std::cout<<"\n";
    }
}


float densityOfBT(TreeNode *root)
{

    if(!root)
        return 0;

    int height = 0, length = 0;
    std::queue<TreeNode*> q;
    TreeNode *temp;

    q.push(root);

    while(!q.empty())
    {
        height++;
        int n = q.size();

        while(n>0)
        {
            length++;
            temp = q.front();
            q.pop();

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }
    }

    float density = (float)length/height;

    return density;
}



float densityOfBT2(TreeNode *root)
{
    if(!root)
        return 0;

    int length = 0;

    int height = heightAndSize(root,length);

    float density = (float)length/height;

    return density;
}


int heightAndSize(TreeNode *root,int& length)
{
    if(!root)
        return 0;

    int l = heightAndSize(root->left,length);
    int r = heightAndSize(root->right,length);

    length++;

    return 1 + (l>r  ? l : r);
}
