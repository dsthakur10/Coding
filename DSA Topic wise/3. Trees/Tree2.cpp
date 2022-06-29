// Given 2 binary trees, check if they are equal - value of every nodes & structure of the tree must be same for both

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
void inorder(TreeNode *root);
bool isSameTree(TreeNode* p, TreeNode* q);                  // recursive
bool isSameTree2(TreeNode* p, TreeNode* q);                 // iterative - using 2 stacks
bool isSameTree3(TreeNode* p, TreeNode* q);                 // iterative - using 1 queue

int main()
{
    TreeNode *root1 = NULL;
    TreeNode *root2 = NULL;
/*
    insertNode(&root,5);
    insertNode(&root,7);
    insertNode(&root,69);
    insertNode(&root,11);
    insertNode(&root,100);
    insertNode(&root,12);
    insertNode(&root,8);
*/


    for(int i=1;i<=5;i++)
        insertNode(&root1,i);

    //insertNode(&root1,8);

    for(int i=1;i<=5;i++)
        insertNode(&root2,i);

    //insertNode(&root2,8);


/*
    TreeNode *temp = root1;
    while(temp->right)
        temp = temp->right;

    temp->right = createNode(6);
    temp = temp->right;
    temp->left = createNode(7);
    temp->right = createNode(8);

    temp = root2;
    while(temp->right)
        temp = temp->right;

    temp->right = createNode(6);
    temp = temp->right;
    temp->left = createNode(7);
    temp->right = createNode(8);

*/
/*
    insertNode(&root1,8);
    insertNode(&root2,8);
*/

    std::cout << "\nTree-1:\n";
    inorder(root1);

    std::cout << "\nTree-2:\n";
    inorder(root2);

    bool flag = isSameTree2(root1,root2);

    if(flag)
        std::cout << "\nTrees are identical\n";
    else
        std::cout << "\nNOT MATCHED\n";

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


void inorder(TreeNode *root)
{
    if(!root)
        return;

    inorder(root->left);

    std::cout<<root->val<<" ";

    inorder(root->right);
}


bool isSameTree(TreeNode* p, TreeNode* q)                       // recursive way
{
    if(!p && !q)
        return true;

    else if((!p && q) || (p && !q))
        return false;

    bool l = isSameTree(p->left, q->left);
    bool r = isSameTree(p->right, q->right);

    bool cur = (p->val == q->val) ? true : false;               // can be optimized if this value check is done before traversing Subtrees.

    bool result = l && r && cur;

    return result;
}



bool isSameTree2(TreeNode* p, TreeNode* q)                      // iterative way - using preorder traversal - 2 stacks
{
    if(!p && !q)
        return true;

    if(!p || !q)
        return false;

    if(p->val != q->val)
        return false;

    std::stack<TreeNode *> pst, qst;
    TreeNode *curp,*curq;

    pst.push(p);
    qst.push(q);

    while(!pst.empty() && !qst.empty())
    {
        curp = pst.top();
        curq = qst.top();
        pst.pop();
        qst.pop();

        if(curp->val != curq->val)
            return false;

        if(curp->right)
            pst.push(curp->right);
        if(curq->right)
            qst.push(curq->right);

        if(pst.size() != qst.size())                // to check if both of the trees have right child at the same position.
            return false;

        if(curp->left)
            pst.push(curp->left);
        if(curq->left)
            qst.push(curq->left);

        if(pst.size() != qst.size())                // to check if both of the trees have left child at the same position.
            return false;
    }

    return pst.size() == qst.size();
}



bool isSameTree3(TreeNode* p, TreeNode* q)              // iterative way - using 1 queue
{
    if(!p && !q)
        return true;

    if(!p || !q)
        return false;

    if(p->val != q->val)
        return false;

    std::queue<TreeNode*> qu;
    TreeNode *curp, *curq;

    qu.push(p);
    qu.push(q);

    while(!qu.empty())
    {
        curp = qu.front();
        qu.pop();
        curq = qu.front();
        qu.pop();

        if(curp->val != curq->val)              // checking value of present nodes
            return false;

        if(curp->left && curq->left)            // push both or none
        {
            qu.push(curp->left);
            qu.push(curq->left);
        }

        else if(!curp->left && !curq->left)     // both nodes don't have left child. That's okay now check for right child
        {

        }

        else                                    // one of them surely has left child & other don't. Return FALSE
            return false;

        if(curp->right && curq->right)
        {
            qu.push(curp->right);
            qu.push(curq->right);
        }

        else if(!curp->right && !curq->right)
            continue;

        else
            return false;
    }

    return true;
}



bool isSymmetric(TreeNode* root)
{

}
