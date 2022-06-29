// inorder successor of node is either a leaf node OR node with only RST
// inorder predecessor of node is either a leaf node OR node with only LST

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

void insertNode(TreeNode **root,int x);                 // iterative
TreeNode* insertNodeRec(TreeNode *root,int x);          // recursive

TreeNode* findSuccessor(TreeNode *root);
TreeNode* findPredecessor(TreeNode *root);

void deleteNode(TreeNode **root, int key);              //

TreeNode* searchNode(TreeNode* root, int key);          // iterative
TreeNode* searchNodeRec(TreeNode* root, int key);       // recursive

void inorder(TreeNode* root);
void levelorder(TreeNode *root);

int main()
{
    int key;
    TreeNode *root = NULL;

    insertNode(&root,50);
    insertNode(&root,40);
    insertNode(&root,100);
    insertNode(&root,80);
    insertNode(&root,120);
    insertNode(&root,60);
    insertNode(&root,90);
    insertNode(&root,55);
    insertNode(&root,110);
    insertNode(&root,200);
    insertNode(&root,140);
    insertNode(&root,20);
    insertNode(&root,10);
    insertNode(&root,30);
    insertNode(&root,25);
    insertNode(&root,58);
    insertNode(&root,57);

/*
    insertNode(&root,7);
    insertNode(&root,6);
    insertNode(&root,5);
    insertNode(&root,4);
    insertNode(&root,3);
    insertNode(&root,2);
    insertNode(&root,1);
*/

/*
    root = insertNodeRec(root,50);
    root = insertNodeRec(root,15);
    root = insertNodeRec(root,62);
    root = insertNodeRec(root,91);
    root = insertNodeRec(root,58);
    root = insertNodeRec(root,5);
    root = insertNodeRec(root,20);
    root = insertNodeRec(root,37);
*/
    std::cout<<"\nIn-order : ";
    inorder(root);
    std::cout<<"\nLevel order : ";
    levelorder(root);

    std::cout<<"\n\nEnter your search: ";
    std::cin>>key;

    //TreeNode *temp = searchNode(root,key);
    TreeNode *temp = searchNodeRec(root,key);
    if(!temp)
        std::cout<<"Not found";

    else
        std::cout<<"Found node with key = "<<temp->val;

    std::cout<<"\n\nEnter key to delete the node: ";
    std::cin>>key;

    deleteNode(&root,key);

    std::cout<<"\nLevel order : ";
    levelorder(root);

}



void inorder(TreeNode* root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    std::cout << root->val << ' ';
    inorder(root->right);
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
        std::cout<<"\n";
        int n = q.size();

        while(n>0)
        {
            temp = q.front();
            q.pop();

            std::cout<<temp->val<<' ';

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }
    }
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

    TreeNode *prev,*temp = *root;

    while(temp)
    {
        prev = temp;

        if(x < temp->val)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if(x<prev->val)
        prev->left = createNode(x);

    else
        prev->right = createNode(x);
}



TreeNode* insertNodeRec(TreeNode* root, int x)
{
    if(!root)
        return createNode(x);

    if(x < root->val)
        root->left = insertNodeRec(root->left,x);

    else
        root->right = insertNodeRec(root->right,x);

    return root;
}



TreeNode* searchNode(TreeNode* root, int x)
{
    if(!root)
        return NULL;

    TreeNode *temp = root;

    while(temp)
    {
        if(temp->val == x)
            return temp;

        if(x < temp->val)
            temp = temp->left;

        else
            temp = temp->right;
    }

    return NULL;
}



TreeNode* searchNodeRec(TreeNode* root, int key)
{
    if(!root || root->val == key)
        return root;

    if(key < root->val)
        return searchNodeRec(root->left, key);

    else
        return searchNodeRec(root->right, key);
}



void deleteNode(TreeNode **root, int key)
{
    if(!(*root))
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    TreeNode *parent = NULL, *temp = *root;

    while(temp)
    {
        if(temp->val == key)
            break;

        parent = temp;

        if(key < temp->val)
            temp = temp->left;
        else
            temp = temp->right;
    }


    if(!temp->left && !temp->right)                             // case - 1 : Leaf
    {
        if(parent->left == temp)
            parent->left = nullptr;

        else if(parent->right == temp)
            parent->right = nullptr;

        delete temp;
    }

    else if(!temp->left)                                        // case-2 : Node with 1 child
    {
        if(parent->left == temp)
            parent->left = temp->right;

        else if(parent->right == temp)
            parent->right = temp->right;

        delete temp;
    }

    else if(!temp->right)
    {
        if(parent->left == temp)
            parent->left = temp->left;

        else if(parent->right == temp)
            parent->right = temp->left;

        delete temp;
    }

    else                                                        // case-3 : Node with 2 children
    {
        // case-3(a) : replace by inorder successor
/*
        TreeNode *succ = findSuccessor(temp->right);            // inorder successor is leftmost node in RST of root
        int x = succ->val;

        deleteNode(root,x);

        temp->val = x;


        // case-3(b) : replace by inorder predecessor
/*
        TreeNode *pred = findPredecessor(temp->left);            // inorder predecessor is rightmost node in LST of root
        int x = pred->val;

        deleteNode(root,x);

        temp->val = x;
*/

        // OPTIMIZED VERSION - avoiding extra recursive delete call by tracking parent of successor node

        TreeNode *succ = temp->right, *succParent = temp;

        while(succ->left)
        {
            succParent = succ;
            succ = succ->left;
        }

        if(succParent != temp)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        temp->val = succ->val;
        delete succ;

    }
}



TreeNode* findSuccessor(TreeNode *root)
{
    while(root->left)
        root = root->left;

    return root;
}


TreeNode* findPredecessor(TreeNode *root)
{
    while(root->right)
        root = root->right;

    return root;
}
