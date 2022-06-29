#include<iostream>
#include<queue>

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
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)

void inorder(TreeNode* root);                           // recursive
void preorder(TreeNode* root);                          // recursive
void postorder(TreeNode* root);                         // recursive


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

    std::cout<<"In-order traversal of tree: ";
    inorder(root);

    std::cout<<"\n\nPre-order traversal of tree: ";
    preorder(root);

    std::cout<<"\n\nPost-order traversal of tree: ";
    postorder(root);

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



void inorder(TreeNode* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    std::cout << root->val << ' ';
    inorder(root->right);
}


void preorder(TreeNode* root)
{
    if (root == NULL)
        return;

    std::cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}


void postorder(TreeNode* root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    std::cout << root->val << ' ';
}
