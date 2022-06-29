// Given perfect binary tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15

// print following order: 1  2,3  4,7,5,6  8,15,9,14,10,13,11,12


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

void perfectBTlevelorder(TreeNode *root);                          // 2 queues - O(n) time & O(n) space
void perfectBTlevelorder2(TreeNode *root);                         // queue - O(n) time & O(n) space



int main()
{
    TreeNode *root = NULL;

    for(int i=1; i<=31; i++)
        insertNode(&root,i);

    std::cout<<"\nPerfect BT specific Level order traversal: \n";
    perfectBTlevelorder(root);

    std::cout<<"\nLevel-order line by line traversal-2 of tree: \n";
    perfectBTlevelorder2(root);

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



//-----------Method-1------------

// 2 queues is to be taken. Queue-1 for storing LST of root. Queue-2 for storing RST of root. LST to be printed normally. RST to be printed reverse ordering.
// Queue-1 : Pop the node. Store left child of it first & then the right child
// Queue-2 : Pop the node. Vice versa of Queue-1
// Print from queue-1 before queue-2 to get the required sequence

void perfectBTlevelorder(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q1,q2;
    TreeNode *temp;

    std::cout<<root->val<<" ";

    if(root->left)
    {
        q1.push(root->left);
        q2.push(root->right);
    }

    while(!q1.empty() && !q2.empty())
    {
        temp = q1.front();
        q1.pop();

        if(temp->left)                              // Only condition to check since BT is perfect. If leftmost node at some level exist ==> all the nodes at that level exist
        {
            q1.push(temp->left);
            q1.push(temp->right);                           // Store nodes in queue-1 in normal order starting from leftmost node at that level.
        }

        std::cout<<temp->val<<" ";

        temp = q2.front();
        q2.pop();

        if(temp->right)                             // At last level, we cannot directly push temp->right/left as they are NULL.
        {
            q2.push(temp->right);                               // Store nodes in queue-2 in reverse order starting from rightmost node at that level.
            q2.push(temp->left);
        }

        std::cout<<temp->val<<" ";

    }
}




// -----------Method-2------------

// Modification to Standard level order traversal. Instead of processing 1 node at a time, we will process to nodes simultaneously.
// Initially push left & right child of root in queue.
// While queue is NOT empty, continue:
// (1) Pop first 2 elements from queue. Store it in 2 pointers: first & second.
// (2) Push their children in following order: first->left , second right, first right, second left

void perfectBTlevelorder2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *first, *second;

    if(root->left)
    {
        q.push(root->left);
        q.push(root->right);
    }

    std::cout<<root->val<<" ";

    while(!q.empty())
    {
        first = q.front();
        q.pop();

        second = q.front();
        q.pop();

        if(first->left)                             // Since the BT is perfect, we do not need to check for remaining nodes if leftmost node is available.
        {
            q.push(first->left);
            q.push(second->right);                              // order of insertion is VIMP
            q.push(first->right);
            q.push(second->left);
        }


        std::cout<<first->val<<" ";
        std::cout<<second->val<<" ";
    }
}

