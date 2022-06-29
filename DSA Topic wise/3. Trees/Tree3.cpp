// Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).

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
void insertNode(TreeNode **root,int x);                     // iterative way (using queue)
void levelorder(TreeNode *root);

void inorderSym(TreeNode *root);
bool isSymmetric(TreeNode* root);               // failure

bool isSymmetric2(TreeNode *root);

bool symmetric(TreeNode *lc, TreeNode *rc);                 // Recursive
bool isSymmetric3(TreeNode *root);

int main()
{
    TreeNode *root = NULL;

    insertNode(&root,5);
    insertNode(&root,7);
    insertNode(&root,69);
    insertNode(&root,11);
    insertNode(&root,100);
    insertNode(&root,12);
    insertNode(&root,8);

    std::cout << "\nTree:\n";
    bool flag = isSymmetric3(root);

    if(flag)
        std::cout << "\nTree is symmetric\n";

    else
        std::cout << "\nTree is NOT";

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
        temp = q.front();
        q.pop();

        std::cout<<temp->val<<' ';

        if(temp->left)
            q.push(temp->left);

        if(temp->right)
            q.push(temp->right);
    }
}




void inorderSym(TreeNode *root, std::vector<TreeNode *>& nodes)
{
    if(!root)
        return ;

    inorderSym(root->left,nodes);

    nodes.push_back(root);

    inorderSym(root->right,nodes);
}


// This method fails when duplicate entries at all positions with different structure apppears. eg. [1,2,2,2,null,2]

bool isSymmetric(TreeNode* root)
{
    if(!root)
        return false;

    std::vector<TreeNode *> nodes;

    inorderSym(root,nodes);
    int len = nodes.size();

    for(int i=0; i<len; i++)
    {
        if(nodes[i]->val != nodes[len-i-1]->val)
            return false;
    }

    return true;
}


// BFS (Level-order) --> Iterative

bool isSymmetric2(TreeNode *root)
{
    queue<TreeNode*> q;
    q.push(root->left);
    q.push(root->right);

    while(!q.empty())
    {
        TreeNode *l, *r;
        l = q.front(); q.pop();
        r = q.front(); q.pop();

        if(!l && !r)
            continue;
            //return true;

        if(!l || !r)
            return false;

        if(l->val != r->val)
            return false;

        q.push(l->left);
        q.push(r->right);

        q.push(l->right);
        q.push(r->left);
    }

    return true;
}



// DFS (In-order) --> Recursive

bool isSymmetric3(TreeNode *root)
{
    if(!root)
        return false;

    return symmetric(root->left, root->right);
}


bool symmetric(TreeNode *lc, TreeNode *rc)
{
    if(!lc && !rc)
        return true;

    if(!lc || !rc)
        return false;

    if(lc->val != rc->val)
        return false;

    return symmetric(lc->left, rc->right) && symmetric(lc->right, rc->left);

}
