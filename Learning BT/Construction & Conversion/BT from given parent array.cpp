// Given an array that represents a tree in such a way that ARRAY INDEXES ARE VALUES IN TREE NODES & ARRAY VALUES GIVE THE PARENT NODE OF THAT PARTICULAR INDEX (or node).
// The value of the root node index would always be -1 as there is no parent for root. Construct Binary Tree from this given representation.

/*
Examples:

Input: parent[] = {1, 5, 5, 2, 2, -1, 3}
Output: root of below tree
          5
        /  \
       1    2
      /    / \
     0    3   4
         /
        6

Explanation:
Index of -1 is 5. So 5 is root.
5 is present at indexes 1 and 2.  So 1 and 2 are children of 5.
1 is present at index 0, so 0 is child of 1.
2 is present at indexes 3 and 4.  So 3 and 4 are children of 2.
3 is present at index 6, so 6 is child of 3.


Input: parent[] = {-1, 0, 0, 1, 1, 3, 5};
Output: root of below tree
         0
       /   \
      1     2
     / \
    3   4
   /
  5
 /
6

*/



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
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);
void inorder(TreeNode *root);

TreeNode* constructBTFromParent(int parent[], int n);               // iterative - Time = O(n) & Space = O(n)

int searchChild(int parent[],int n,int val);
void constructChild(int parent[], int n, TreeNode *temp);
TreeNode* constructBTFromParent2(int parent[], int n);              // recursive - Time = O(n^2) & Space = O(1)


int main()
{
    //int parent[] = {1, 5, 5, 2, 2, -1, 3};
    //int parent[] = {-1, 0, 0, 1, 1, 3, 5};
    //int parent[] = {2,2,4,0,-1,7,5,1};
    //int parent[] = {-1};
    int parent[] = {5,2,3,4,0,-1};

    TreeNode *root;
    int n = sizeof(parent)/sizeof(parent[0]);

    root = constructBTFromParent(parent,n);

    std::cout<<"Level-order traversal of Parent Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Parent Binary Tree:\n";
    inorder(root);


    root = constructBTFromParent2(parent,n);

    std::cout<<"\n\nLevel-order traversal-2 of Parent Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal-2 of Parent Binary Tree:\n";
    inorder(root);

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

        std::cout<<"\n";
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



//--------------Method-1---------------


TreeNode* constructBTFromParent(int parent[], int n)
{
    std::vector<TreeNode*> nodes;
    TreeNode *root;

    for(int i=0;i<n;i++)                            // create every node & store their addresses in array to combine them into tree later.
        nodes.push_back(createNode(i));

    for(int i=0;i<n;i++)                            // Traverse every node in array. 'i' represents node number itself
    {
        if(parent[i] == -1)                                 // this condition represents 'i' is root node. Make it root.
            root = nodes[i];

        else
        {
            TreeNode *temp = nodes[parent[i]];              // store parent of current node 'i' in temp

            if(!temp->left)                                 // if left pointer is empty, make node 'i' left child of its parent
                temp->left = nodes[i];
            else
                temp->right = nodes[i];                     // if left pointer is occupied, make node 'i' right child
        }
    }

    return root;
}



//---------------Method-2-----------------


int searchChild(int parent[],int n, int val)
{
    for(int i=0;i<n;i++)                                // Search the child of node with key 'val'
    {
        if(parent[i] == val)                            // there exist at most 2 children for node with key 'val'
        {                                               // After extracting child node, make its parent (-1) to let the program know that this child has already been considered.
            parent[i] = -1;
            return i;
        }
    }

    return -1;                                          // for leaf nodes, (-1) will be returned as they do not hold child.
}


void constructChild(int parent[], int n, TreeNode *temp)
{
    int val = searchChild(parent,n,temp->val);                  // Extract child of parent

    if(val == -1)                                               // val = -1 ==> leaf node OR right child of temp does not exist
        return;

    if(!temp->left)                                             // if left child is empty, make the new node - left child of present node.
    {
        temp->left = createNode(val);
        constructChild(parent, n, temp->left);                          // traverse LST
        constructChild(parent, n, temp->left);                          // traverse RST
    }

    else                                                        // if left child is occupied, store the node as right child
    {
        temp->right = createNode(val);
        constructChild(parent, n, temp->right);                         // traverse LST
        constructChild(parent, n, temp->right);                         // traverse RST
    }

}


TreeNode* constructBTFromParent2(int parent[], int n)
{
    TreeNode *root;

    for(int i=0;i<n;i++)                                // Create root node first as construction will start from top.
    {
        if(parent[i] == -1)
        {
            root = createNode(i);
            break;
        }
    }

    constructChild(parent, n, root);                    // This will create left child of root
    constructChild(parent, n, root);                    // This will create right child of root (if it exists)

    return root;
}
