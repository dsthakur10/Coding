// Given tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15
// print reverse level order -->
// 8,9,10,11,12,13,14,15
// 7,6,5,4
// 2,3
// 1


#include<iostream>
#include<queue>
#include<stack>
#include<deque>

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

void levelorderReverse(TreeNode *root);                          // queue + stack - O(n) time & O(n) space
void levelorderReverse2(TreeNode *root);                         // recursive method - O(n^2) time & O(1) space
void currentLevel(TreeNode *root, int level);
int height(TreeNode *root);


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

    insertNode(&root,1);
    insertNode(&root,2);
    insertNode(&root,3);
    insertNode(&root,4);
    insertNode(&root,5);
    insertNode(&root,6);
    insertNode(&root,7);
    insertNode(&root,8);
    insertNode(&root,9);
    insertNode(&root,10);
    insertNode(&root,11);
    insertNode(&root,12);
    insertNode(&root,13);
    insertNode(&root,14);
    insertNode(&root,15);
    insertNode(&root,16);
    insertNode(&root,17);
    insertNode(&root,18);
    insertNode(&root,19);
    insertNode(&root,20);
    insertNode(&root,21);

/*
    root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);
*/
    std::cout<<"\nLevel-order line by line traversal of tree: \n";
    levelorderReverse(root);

    std::cout<<"\nLevel-order line by line traversal-2 of tree: \n";
    levelorderReverse2(root);

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


// -------------Method-1-------------


void levelorderReverse(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    std::stack<TreeNode*> s;
    TreeNode *temp;

    q.push(root);
    while(!q.empty())
    {
        temp = q.front();
        q.pop();


        if(temp->right)
            q.push(temp->right);

        if(temp->left)
            q.push(temp->left);

        s.push(temp);
    }

    while(!s.empty())
    {
        std::cout<<(s.top())->val<<" ";
        s.pop();
    }
}


// ----------Method-2----------


int height(TreeNode *root)
{
    if(root == NULL)
        return 0;

    int l = height(root->left);
    int r = height(root->right);
    int x = (l>r) ? l : r;

    return 1 + x;
}


void currentLevel(TreeNode *root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        std::cout << root->val << " ";
    else if(level > 1)
    {
        currentLevel(root->left, level-1);
        currentLevel(root->right, level-1);
    }
}



void levelorderReverse2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    int h = height(root);

    for (int i = h; i >= 1; i--)
        currentLevel(root, i);
}
