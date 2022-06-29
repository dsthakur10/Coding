#include<iostream>
#include<queue>
#include<stack>

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

void deleteNode(TreeNode **root, int key);              // deletes node from BT by making sure that tree shrinks from the bottom
TreeNode* findLast(TreeNode *root);                     // i.e. deleted node is replaced by the bottom-most and rightmost node.

TreeNode* searchNode(TreeNode* root, int key);

void inorder(TreeNode* root);
void preorder(TreeNode* root);
void postorder(TreeNode* root);
void levelorder(TreeNode *root);                        // queue

void currentLevel(TreeNode *root, int level);
int height(TreeNode *root);
void levelorder2(TreeNode *root);                       // There are basically two functions in this method.
                                                        // One is to print all nodes at a given level (CurrentLevel),
                                                        // & other is to print level order traversal of the tree (levelorder2).
                                                        // levelorder2 makes use of currentLevel to print nodes at all levels
                                                        // one by one starting from the root.
int main()
{
    TreeNode *root = NULL;
    int val,key;
/*
    while(true)
    {
        std::cout<<"Enter node->value. Press 0 to end insertion process:\n";
        std::cin>>val;

        if(val == 0)
            break;

        insertNode(&root,val);
    }
*/


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

    //insertNode(&root,500);

    std::cout<<"\n\nIn-order traversal of tree: ";
    inorder(root);

    std::cout<<"\n\nPre-order traversal of tree: ";
    preorder(root);

    std::cout<<"\n\nPost-order traversal of tree: ";
    postorder(root);

    std::cout<<"\n\nLevel-order traversal of tree: ";
    levelorder(root);


    std::cout<<"\n\nEnter the node to be searched:";
    std::cin>>key;

    temp = searchNode(root,key);
    if(temp)
        std::cout<<"\n\nFound = "<<temp->val;
    else
        std::cout<<"\n\nNot found";


    std::cout<<"\n\nEnter the node to be deleted:";
    std::cin>>key;

    deleteNode(&root,key);

    if(root == NULL)
        std::cout<<"\n\n ROOT NULLLLL";
    else
        std::cout<<"\nroot:"<<root->val;

    std::cout<<"\n\nLevel-order traversal of tree: ";
    levelorder(root);

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


void levelorder2(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    int h = height(root);

    for (int i = 1; i <= h; i++)
        currentLevel(root, i);
}



TreeNode* findLast(TreeNode *root)
{
    if(!root)
        return NULL;

    if(!root->left && !root->right)
        return root;

    std::queue<TreeNode *> q;
    TreeNode *temp,*parent;
    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->left)
        {
            parent = temp;
            q.push(temp->left);
        }

        if(temp->right)
        {
            parent = temp;
            q.push(temp->right);
        }
    }

    if(parent->left == temp)
        parent->left = NULL;

    if(parent->right == temp)
        parent->right = NULL;

    return temp;
}


void deleteNode(TreeNode **root, int key)
{
    if(!(*root))
    {
        std::cout<<"\n\nTree Empty";
        return;
    }

    if((*root)->left == NULL && (*root)->right == NULL)
    {
        if((*root)->val == key)
        {
            delete *root;
            *root = NULL;                                               // most important step - to make root point to NULL after deleting node allocated
            std::cout<<"\n\nOnly root Node deleted";
        }

        else
            std::cout<<"\n\nNode not found";

        return;
    }

    std::queue<TreeNode *> q;
    TreeNode *temp;
    q.push(*root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->val == key)
            break;

        if(temp->left)
        {
            q.push(temp->left);
        }

        if(temp->right)
        {
            q.push(temp->right);
        }
    }

    if(temp->val == key)
    {
        TreeNode *ptr = findLast(*root);
        temp->val = ptr->val;
        delete ptr;
        ptr = NULL;
        std::cout<<"\n\nNode deleted";
        return;
    }

    std::cout<<"\n\nNode not found";
}



TreeNode* searchNode(TreeNode* root, int key)
{
    if(!root)
    {
        std::cout<<"\n\n Tree empty";
        return NULL;
    }

    TreeNode* temp = root;
    std::queue<TreeNode*> q;

    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->val == key)
            return temp;

        if(temp->left)
            q.push(temp->left);

        if(temp->right)
            q.push(temp->right);
    }

    return NULL;
}
