// Given perfect binary tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15

// print following order: 8,15,9,14,10,13,11,12  4,7,5,6  2,3  1

#include<iostream>
#include<queue>
#include<stack>
#include<deque>
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
void insertNode(TreeNode **root,int x);                         // iterative way (using queue)

void perfectBTlevelorderBottom(TreeNode *root);                             // 2 queues + stack - O(n) time & O(n) space
void perfectBTlevelorderBottom2(TreeNode *root);                            // queue + stack - O(n) time & O(n) space
void perfectBTlevelorderBottom3(TreeNode *root);                            // queue + stack + vector - 2*O(n) time & O(n) space


int main()
{
    TreeNode *root = NULL;

    for(int i=1; i<=31; i++)
        insertNode(&root,i);

    std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    perfectBTlevelorderBottom(root);

    std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    perfectBTlevelorderBottom2(root);

    std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    perfectBTlevelorderBottom3(root);

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

void perfectBTlevelorderBottom(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q1,q2;
    std::stack<TreeNode*> s;
    TreeNode *temp;

    s.push(root);
    if(root->left)
    {
        q1.push(root->left);
        q2.push(root->right);
    }

    while(!q1.empty() && !q2.empty())
    {
        temp = q2.front();
        q2.pop();
        s.push(temp);

        if(temp->right)
        {
            q2.push(temp->left);
            q2.push(temp->right);
        }

        temp = q1.front();
        q1.pop();
        s.push(temp);

        if(temp->left)
        {
            q1.push(temp->right);
            q1.push(temp->left);
        }

    }

    while(!s.empty())
    {
        std::cout<<(s.top())->val<<" ";

        s.pop();
    }
}



// ------------Method-2--------------


void perfectBTlevelorderBottom2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    std::stack<TreeNode*> s;
    TreeNode *first, *second;

    s.push(root);
    if(root->left)
    {
        q.push(root->right);
        q.push(root->left);
    }

    while(!q.empty())
    {
        first = q.front();
        q.pop();
        s.push(first);

        second = q.front();
        q.pop();
        s.push(second);

        if(second->left)
        {
            q.push(first->left);
            q.push(second->right);
            q.push(first->right);
            q.push(second->left);
        }

    }

    while(!s.empty())
    {
        std::cout<<(s.top())->val<<" ";

        s.pop();
    }
}



// -------------Method-3--------------

void perfectBTlevelorderBottom3(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    std::stack<std::vector<int>> s;
    TreeNode *temp;

    if(root->left)
    {
        q.push(root->left);
        q.push(root->right);
    }

    while(!q.empty())
    {
        std::vector<int> nodes;
        int n = q.size();

        while(n>0)
        {
            temp = q.front();
            q.pop();

            if(temp->left)
            {
                q.push(temp->left);
                q.push(temp->right);
            }

            nodes.push_back(temp->val);
            n--;
        }

        s.push(nodes);
    }

    while(!s.empty())
    {
        std::vector<int> vec = s.top();
        s.pop();

        for(int i=0,j=vec.size()-1; i < j; i++,j--)
            std::cout<<vec[i]<<" "<<vec[j]<<" ";
    }

    std::cout<<root->val;
}
