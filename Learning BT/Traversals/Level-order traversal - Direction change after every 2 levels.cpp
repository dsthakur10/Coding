// Given tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15  16,17,18,19,20,21
// print level order with direction change after every 2 levels -->
// 1
// 2,3
// 7,6,5,4
// 15,14,13,12,11,10,9,8
// 16,17,18,19,20,21


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
void reverseStack(std::stack<TreeNode*> s);

void levelorderChangeAfterTwoLevel(TreeNode *root);                          // 1 queue & 2 stacks - O(n) time & O(n) space
void levelorderChangeAfterTwoLevel2(TreeNode *root);                         // 1 queue & 1 stack - O(n) time & O(n) space

void levelorderChangeAfterTwoLevel3(TreeNode *root);                         // recursive method - O(n^2) time & O(1) space
void currentLevel(TreeNode *root, int level, bool flag);
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

    root = createNode(20);
    root->left = createNode(8);
    root->right = createNode(22);
    root->left->left = createNode(4);
    root->left->right = createNode(12);
    root->left->right->left = createNode(10);
    root->left->right->right = createNode(14);

    std::cout<<"\nLevel-order direction change after every 2 levels traversal of tree: \n";
    levelorderChangeAfterTwoLevel(root);

    std::cout<<"\nLevel-order direction change after every 2 levels traversal-2 of tree: \n";
    levelorderChangeAfterTwoLevel2(root);

    std::cout<<"\nLevel-order direction change after every 2 levels traversal-3 of tree: \n";
    levelorderChangeAfterTwoLevel3(root);

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


void levelorderChangeAfterTwoLevel(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    bool flag = true, current = true;                                         // flag ==> direction current ==> 1st or 2nd level in printing
    std::queue<TreeNode*> q;
    std::stack<TreeNode*> s1,s2;
    TreeNode *temp;

    q.push(root);

    while(!q.empty())
    {
        while(!q.empty())
        {
            temp = q.front();
            q.pop();

            if(flag && current)                                         // left to right level 1
            {
                if(temp->right)
                    s1.push(temp->right);

                if(temp->left)
                    s1.push(temp->left);
            }

            else if(flag && !current)                                   // left to right level 2
            {
                if(temp->left)
                    s1.push(temp->left);

                if(temp->right)
                    s1.push(temp->right);
            }

            else if(!flag && current)                                   // right to left level 1
            {
                if(temp->right)
                    s2.push(temp->right);

                if(temp->left)
                    s2.push(temp->left);
            }

            else                                                        // right to left level 2
            {
                if(temp->right)
                    s1.push(temp->right);

                if(temp->left)
                    s1.push(temp->left);

            }

            std::cout<<temp->val<<" ";
        }

        while(!s2.empty())
        {
            temp = s2.top();
            s2.pop();

            s1.push(temp);
        }

        while(!s1.empty())
        {
            temp = s1.top();
            s1.pop();

            q.push(temp);
        }

        std::cout<<"\n";

        current = !current;

        if(current)
            flag = !flag;
    }

}




void levelorderChangeAfterTwoLevel2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *temp;
    std::stack<TreeNode*> s;

    q.push(root);

    bool flag = true, current=true;

    while(!q.empty())
    {
        int n = q.size();
        while(n>0)
        {
            temp = q.front();
            q.pop();

            if(flag)
                std::cout<<temp->val<<" ";

            else
                s.push(temp);

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);
            n--;
        }


        while(!s.empty())
        {
            std::cout<<(s.top())->val<<" ";
            s.pop();
        }

        std::cout<<"\n";

        current = !current;

        if(current)
            flag = !flag;

    }
}



// -------------Method-3-------------

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


void currentLevel(TreeNode *root, int level,bool flag)
{
    if (root == NULL)
        return;
    if (level == 1)
        std::cout << root->val << " ";
    else if(level > 1)
    {
        if(flag)
        {
            currentLevel(root->left, level-1,flag);
            currentLevel(root->right, level-1,flag);
        }

        else
        {
            currentLevel(root->right, level-1,flag);
            currentLevel(root->left, level-1,flag);
        }

    }
}


void levelorderChangeAfterTwoLevel3(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    bool flag = true, current = true;
    int h = height(root);

    for (int i = 1; i <= h; i++)
    {
        currentLevel(root, i, flag);
        std::cout<<"\n";

        current = !current;

        if(current)
            flag = !flag;

    }

}
