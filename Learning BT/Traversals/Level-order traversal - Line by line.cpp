// Given tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15
// print level order line by line -->
// 1
// 2,3
// 7,6,5,4
// 8,9,10,11,12,13,14,15


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

void levelorderLineByLine(TreeNode *root);                          // 1 queue with counting #nodes at every level - O(n) time & O(n) space
void levelorderLineByLine2(TreeNode *root);                         // 2 queues - O(n) time & O(n) space
void levelorderLineByLine3(TreeNode *root);                         // 1 queue with NULL insertion to check end of certain level - O(n) time & O(n) space

void levelorderLineByLine4(TreeNode *root);                         // recursive method - O(n^2) time & O(1) space
void currentLevel(TreeNode *root, int level);
int height(TreeNode *root);


int main()
{
    TreeNode *root = NULL;

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

/*
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
*/
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
    levelorderLineByLine(root);

    std::cout<<"\nLevel-order line by line traversal-2 of tree: \n";
    levelorderLineByLine2(root);

    std::cout<<"\nLevel-order line by line traversal-3 of tree: \n";
    levelorderLineByLine3(root);

    std::cout<<"\nLevel-order line by line traversal-4 of tree: \n";
    levelorderLineByLine4(root);

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

// Count the nodes at current level (queue size) & then print only that many elements which are on specific level. Then use newline at the end of loop
// Time = O(n) Space = O(n)


void levelorderLineByLine(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    int n;
    std::queue<TreeNode*> q;
    TreeNode* temp;

    q.push(root);

    while(!q.empty())
    {
        n = q.size();

        for(int i=1; i<=n; i++)
        {
            temp = q.front();
            q.pop();

            std::cout<<temp->val<<' ';

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);
        }

        std::cout<<"\n";
    }
}



// -------------Method-2-------------

// Create 2 queues. Each key is used to print alternate levels. Queue-1 is used to print odd levels. Queue-2 is used to print even levels.
// Pop nodes from 1 queue. print them. Push its child nodes into other queue at every level.
// Before jumping from 1 queue to other queue traversal, use newline for separate printing of nodes.
// Continue until both the queues becomes empty.

// Time = O(n) Space = O(n)


void levelorderLineByLine2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q1,q2;
    TreeNode *temp;

    q1.push(root);

    while(!q1.empty() || !q2.empty())
    {
        while(!q1.empty())
        {
            temp = q1.front();
            q1.pop();

            if(temp->left)
                q2.push(temp->left);

            if(temp->right)
                q2.push(temp->right);

            std::cout<<temp->val<<" ";
        }

        std::cout<<"\n";

        while(!q2.empty())
        {
            temp = q2.front();
            q2.pop();

            if(temp->left)
                q1.push(temp->left);

            if(temp->right)
                q1.push(temp->right);

            std::cout<<temp->val<<" ";
        }

        std::cout<<"\n";
    }
}



// -------------Method-3-------------

// First insert the root and a NULL element into the queue. This NULL element acts as a delimiter.
// Next, pop from the top of the queue and add its left and right child nodes to the end of the queue and then print the top of the queue just popped.
// Continue this process till the queues become empty.

// Time = O(n) Space = O(n)


void levelorderLineByLine3(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *temp;

    q.push(root);
    q.push(NULL);

    while(q.size() > 1)
    {
        temp = q.front();
        q.pop();

        if(!temp)
        {
            q.push(NULL);                                       // NULL has been removed. So re-add it.
            std::cout<<"\n";
        }

        else
        {
            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            std::cout<<temp->val<<" ";
        }
    }

}



// -------------Method-4-------------

// Time = O(n^2) Space = O(1)


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


void levelorderLineByLine4(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    int h = height(root);

    for (int i = 1; i <= h; i++)
    {
        currentLevel(root, i);
        std::cout<<"\n";
    }

}
