// Given tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15       print level order spiral form --> 1  2,3  7,6,5,4  8,9,10,11,12,13,14,15
// 2nd level - left to right
// 3rd level - right to left
// 4th level - left to right
// 5th level - right to left .....


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

void levelorderSpiral(TreeNode *root);                          // stack & queue - O(n) time & O(n) space
void levelorderSpiral2(TreeNode *root);                         // 2 stacks - O(n) time & O(n) space
void levelorderSpiral3(TreeNode *root);                         // double ended queue - O(n) time & O(n) space

void levelorderSpiral4(TreeNode *root);                         // recursive method - O(n^2) time & O(1) space
void currentLevel(TreeNode *root, int level, bool flag);
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

    std::cout<<"Spiral Level-order traversal of tree: ";
    levelorderSpiral(root);

    std::cout<<"\n\nSpiral Level-order traversal-2 of tree: ";
    levelorderSpiral2(root);

    std::cout<<"\n\nSpiral Level-order traversal-3 of tree: ";
    levelorderSpiral3(root);

    std::cout<<"\n\nSpiral Level-order traversal-3 of tree: ";
    levelorderSpiral4(root);

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

// Store nodes in queue from 2 different directions at alternate levels using stack & flag variable to identify the type of direction at each level.
// For odd level, push right child before left child in stack so that at next level printing starts from left.
// For even level, push left child before right child in stack so that printing starts from right in succeeding level.
// After pushing nodes in stack in one of specific ordering, pop all elements from stack & push them in queue for continuing the process in next level.
// Continue until queue becomes empty

// Time = O(n) Space = O(n)


void levelorderSpiral(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    bool flag = true;
    std::queue<TreeNode*> q;
    std::stack<TreeNode*> s;
    TreeNode *temp;

    q.push(root);

    while(!q.empty())
    {
        while(!q.empty())
        {
            temp = q.front();
            q.pop();

            if(flag)                                                // true ==> Left to Right
            {
                if(temp->right)
                    s.push(temp->right);

                if(temp->left)
                    s.push(temp->left);
            }

            else                                                    // true ==> Right to Left
            {
                if(temp->left)
                    s.push(temp->left);

                if(temp->right)
                    s.push(temp->right);
            }

            std::cout<<temp->val<<" ";
        }

        while(!s.empty())
        {
            temp = s.top();
            s.pop();

            q.push(temp);
        }

        flag = !flag;
    }
}



// -------------Method-2-------------

// Store nodes of alternate levels in 2 different stacks. Stack-1 is used to print from Right to Left. Stack-2 other way around.
// Continue printing nodes while poping from 1 stack & pushing onto other.
// For odd level, push right child before left child in stack-2 so that at next level printing starts from left.
// For even level, push left child before right child in stack-1 so that printing starts from right in succeeding level.
// Continue until both stacks becomes empty.

// Time = O(n) Space = O(n)


void levelorderSpiral2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }
    std::stack<TreeNode*> s1,s2;
    TreeNode *temp;

    s1.push(root);

    while(!s1.empty() || !s2.empty())
    {
        while(!s1.empty())
        {
            temp = s1.top();
            s1.pop();

            if(temp->right)
                s2.push(temp->right);

            if(temp->left)
                s2.push(temp->left);

            std::cout<<temp->val<<" ";
        }

        while(!s2.empty())
        {
            temp = s2.top();
            s2.pop();

            if(temp->left)
                s1.push(temp->left);

            if(temp->right)
                s1.push(temp->right);

            std::cout<<temp->val<<" ";
        }
    }
}



// -------------Method-3-------------

// Store nodes of alternate levels in single double ended queue.
// For odd level: Traverse the queue from right to left. Pop nodes from the back. Insert the children of popped nodes at front (right child before left)
// For even level: Traverse the queue from left to right. Pop nodes from the front. Insert the children of popped nodes at back (left child before right)
// Repeat until deque becomes empty.

// Time = O(n) Space = O(n)


void levelorderSpiral3(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    bool flag = true;
    int n;
    std::deque<TreeNode*> dq;
    TreeNode *temp;

    dq.push_back(root);

    while(!dq.empty())
    {
        n = dq.size();

        if(flag)                                                    // true ==> Left to Right
        {
            for(int i=1; i<=n; i++)
            {
                temp = dq.back();
                dq.pop_back();

                if(temp->right)
                    dq.push_front(temp->right);

                if(temp->left)
                    dq.push_front(temp->left);

                std::cout<<temp->val<<" ";
            }
        }

        else                                                        // false ==> Right to Left
        {
            for(int i=1; i<=n; i++)
            {
                temp = dq.front();
                dq.pop_front();

                if(temp->left)
                    dq.push_back(temp->left);

                if(temp->right)
                    dq.push_back(temp->right);

                std::cout<<temp->val<<" ";
            }
        }

        flag = !flag;
    }
}



// -------------Method-4-------------

// Use flag variable to traverse alternate levels in different directions.

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


void currentLevel(TreeNode *root, int level, bool flag)
{
    if (root == NULL)
        return;
    if (level == 1)
        std::cout << root->val << " ";
    else if(level > 1)
    {
        if(flag)
        {
            currentLevel(root->right, level-1, flag);
            currentLevel(root->left, level-1, flag);
        }

        else
        {
            currentLevel(root->left, level-1, flag);
            currentLevel(root->right, level-1, flag);
        }
    }
}


void levelorderSpiral4(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    bool flag = true;
    int h = height(root);

    for (int i = 1; i <= h; i++)
    {
        currentLevel(root, i, flag);
        flag = !flag;
    }

}
