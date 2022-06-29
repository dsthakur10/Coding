/*
    Given the root of a complete binary tree, return the number of the nodes in the tree.

    According to Wikipedia, every level, except possibly the last, is completely filled in a complete binary tree, and all nodes in the last level are as far left as possible.
    It can have between 1 and 2^h nodes inclusive at the last level h.

    DESIGN AN ALGORITHM THAT RUNS IN LESS THAN O(N) TIME COMPLEXITY.

*/


#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include <algorithm>
#include<cmath>

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
int countNodes(TreeNode* root);
int countNodes2(TreeNode* root);
int countNodes3(TreeNode* root);



int main()
{
    TreeNode *root = NULL;
    int x;

    for(int i=1; i<=20; i++)
        insertNode(&root,i);

    levelorder(root);

    int number = countNodes2(root);

    std::cout << "\nNumber of nodes = "<< number;

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


//-----------------Method-1----------------------

// Idea is to count #levels from leftmost node --> It will give exact number of levels.

// Now traverse the tree in level-order manner for #times = (level-1)

// At last second level, check if every node has left & right child. Increment counter with each such entry. As soon as 1st absentee is identified, break the loop & return
// (2^level - 1 + counter) to get total number of nodes


int countNodes(TreeNode* root)
{
    if(!root)
        return 0;

    if(!root->left && !root->right)
        return 1;

    TreeNode *cur;
    int level, n, counter, i;

    level = -1;
    cur = root;

    while(cur)
    {
        cur = cur->left;
        level++;
    }

    std::queue<TreeNode *> q;
    q.push(root);

    i = 0;
    while(i < level)
    {
        counter = 0;
        n = q.size();
        while(n > 0)
        {
            cur = q.front();
            q.pop();

            if(cur->left)
            {
                q.push(cur->left);
                counter++;
            }

            else
                break;

            if(cur->right)
            {
                q.push(cur->right);
                counter++;
            }

            else
                break;

            n--;
        }

        i++;
    }

    return std::pow(2,level) - 1 + counter;
}



// ----------------Method-2-----------------

// Subtree of almost complete binary tree is also almost complete.
// Find if the LST & RST of root are full tree ---> only possible is leftmost child & rightmost child of subtree are at same level
// Since tree is almost complete, atleast one of the LST/RST will always be full. 2nd recursive call will immediately stops. Now simply return for full tree:
//          return 2^level - 1
// The whole process is recursively repeated for the other tree if it is not full.
//          return 1 + count(LST) + count(RST)

// Time complexity T(n) = T(n/2) + 2*(logn) --> O(logn)^2


int countNodes2(TreeNode* root)
{
    if(!root)
        return 0;

    int hl=0, hr=0;

    TreeNode *l=root, *r=root;

    while(l)
    {   hl++;
        l = l->left;
    }

    while(r)
    {
        hr++;
        r = r->right;
    }

    if(hl==hr)
        return pow(2,hl) - 1;

    return 1 + countNodes2(root->left) + countNodes2(root->right);
}



int countNodes3(TreeNode* root)
{
    int h, nodes;
    h = height(root);
    nodes = 0;

    while(root)
    {
        if(height(root->right) == h-1)

    }
}



int height(TreeNode* root)
{
    if(!root)
        return 0;

    return 1 + height(root->left);
}
