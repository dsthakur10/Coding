// Given a binary tree and a node, write a program to find inorder successor of this node

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
void insertNode(TreeNode **root,int x);                                         // iterative way (using queue)
void levelorder(TreeNode *root);
TreeNode* searchNode(TreeNode* root, int key);

// Method-1
TreeNode* findSuccessor(TreeNode *root, TreeNode *node);                        // store nodes by Inorder traversal in an array. Then simply traverse array
void getSuccessor(TreeNode *root, std::vector<TreeNode*>& in);                  // If node is find at arr[i], return arr[i+1]
                                                                                // Time = 3*O(n) + O(n) Space = O(n)

// Method-2
TreeNode* findSuccessor2(TreeNode *root, TreeNode *node);                       // Apply reverse Inorder traversal & store previously visited node. If root = node,
                                                                                // return the stored value as it will be inorder successor of this root node.
                                                                                // Time = 3*O(n) Space = O(1)

// Method-3
TreeNode* findSuccessor3(TreeNode *root, TreeNode *node);
bool isRightMost(TreeNode *root, TreeNode *node);
TreeNode* leftmostInRST(TreeNode *node);
TreeNode* leftOfParent(TreeNode *root, TreeNode *node);



int main()
{
    int key;
    TreeNode *root = NULL,*temp,*node;


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

    temp = root;

    while(temp->right)
        temp = temp->right;

    temp->left = createNode(12);
    temp->right = createNode(13);

/*
    node = root;
    node = node->left;
    node = node->right;
    node = node->left;

    temp = findSuccessor(root,node);
*/

    levelorder(root);
    std::cout<<"\n\nEnter node value of whose inorder you want: ";
    std::cin>>key;

    node = searchNode(root,key);

    if(!node)
    {
        std::cout<<"\nGiven key value does not exist in root";
        return 0;
    }

    //temp = findSuccessor(root,node);
    temp = findSuccessor2(root,node);

    if(temp)
        std::cout<<"\nInorder successor of node "<<node->val<<" = "<<temp->val;

    else
        std::cout<<"\nRightmost Node. Inorder does not exist.";

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



// -------------Method-1-------------

// Store nodes by Inorder traversal in an array. Then simply traverse array. Return arr[i+1] if arr[i] = node since in inorder traversal
// (i+1)th node is the successor of ith node

// Time = 3*O(n) + O(n) Space = O(n)


TreeNode* findSuccessor(TreeNode *root,TreeNode *node)
{
    std::vector<TreeNode*> arr;
    getSuccessor(root,arr);

    arr.push_back(nullptr);                                        // for rightmost element, successor will be NULL

    for(int i=0;i<arr.size()-1;i++)
    {
        if(arr[i] == node)
            return arr[i+1];
    }

    return NULL;
}



void getSuccessor(TreeNode *root, std::vector<TreeNode*>& in)
{
    if(!root)
        return;

    getSuccessor(root->left,in);

    in.push_back(root);

    getSuccessor(root->right,in);
}



// -------------Method-2-------------

// Apply reverse Inorder traversal & store previously visited node. If root = node, return the stored value as it will be inorder successor of this root node.

// Time = 3*O(n) Space = O(1)


TreeNode* findSuccessor2(TreeNode *root, TreeNode *node)
{
    static TreeNode *succ = nullptr;

    if(!root)
        return NULL;

    TreeNode *l = findSuccessor2(root->right,node);

    if(root == node)
        return succ;

    succ = root;

    TreeNode *r = findSuccessor2(root->left,node);

    if(l != nullptr)
        return l;

    return r;
}







TreeNode* findSuccessor3(TreeNode *root, TreeNode *node)
{
    if(isRightMost(root,node))
        return NULL;

    if(node->right)
        return leftmostInRST(node);

    return leftOfParent(root,node);
}



bool isRightMost(TreeNode *root, TreeNode *node)
{
    while(root->right)
        root = root->right;

    if(root == node)
        return true;

    return false;
}



TreeNode* leftmostInRST(TreeNode *node)
{
    node = node->right;

    while(node->left)
        node = node->left;

    return node;
}



TreeNode* leftOfParent(TreeNode *root, TreeNode *node)
{
    static TreeNode *succ = NULL;

    if(!root)
        return NULL;

    if(root == node)
    {
        succ = node;
        return succ;
    }

    TreeNode *l = leftOfParent(root->left,node);

    TreeNode *r = leftOfParent(root->right,node);


    if(l)
    {
        if(root->left == l)
            succ = root;

        else
            succ = l;
    }

    if(r)
    {
        if(root->left == r)
            succ = root;

        else
            succ = r;
    }

    return succ;
}
