// Given Inorder Traversal of a Special Binary Tree in which key of every node is greater than keys in left and right children, construct the Binary Tree and return root.

/*
Examples:

Input: inorder[] = {5, 10, 40, 30, 28}
Output: root of following tree
         40
       /   \
      10     30
     /         \
    5          28

Input: inorder[] = {1, 5, 10, 40, 30,
                    15, 28, 20}
Output: root of following tree
          40
        /   \
       10     30
      /         \
     5          28
    /          /  \
   1         15    20

*/



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
void levelorder(TreeNode *root);
void inorder(TreeNode *root);

int searchGreatest(int in[],int size);
TreeNode* constructSpecialBTFromIn(int in[], int n);

int searchGreatest2(int in[],int start, int end);
TreeNode* constructSpecialBTFromIn2(int in[], int start, int end);



int main()
{

    //int in[] = {1, 5, 10, 40, 30, 15, 28, 20};
    //int in[] = {5, 10, 40, 30, 28};
    int in[] = {60,80,20,100,1,5,50,12};
    //int in[] = {20,40,60,80,100};

    TreeNode *root;
    int n = sizeof(in)/sizeof(in[0]);

    root = constructSpecialBTFromIn(in,n);

    std::cout<<"Level-order traversal of Special Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Special Binary Tree:\n";
    inorder(root);


    root = constructSpecialBTFromIn2(in,0,n-1);

    std::cout<<"\n\nLevel-order traversal-2 of Special Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal-2 of Special Binary Tree:\n";
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


int searchGreatest(int in[],int size)
{
    int maxx = in[0];
    int highest = 0;

    for(int i=1; i<size; i++)
    {
        if(in[i] > maxx)
        {
            maxx = in[i];
            highest = i;
        }
    }

    return highest;
}



TreeNode* constructSpecialBTFromIn(int in[], int n)
{
    int index = searchGreatest(in,n);

    TreeNode *root = createNode(in[index]);

    if(index != 0)                                                          // index=0 ==> LST absent
        root->left = constructSpecialBTFromIn(in, index);

    if(index != n-1)                                                        // index=n-1 ==> RST absent
        root->right = constructSpecialBTFromIn(in+index+1, n-index-1);

    return root;                                                            // in case of leaf, index = 0 & index=n-1(1-1=0)
}



//---------------Method-2-----------------


int searchGreatest2(int in[],int start, int end)
{
    int maxx = in[start];
    int highest = start;

    for(int i=start+1; i<=end; i++)
    {
        if(in[i] > maxx)
        {
            maxx = in[i];
            highest = i;
        }
    }

    return highest;
}


TreeNode* constructSpecialBTFromIn2(int in[], int start, int end)
{
    if(start > end)                                                 // in case root has only 1 child(subtree)
        return NULL;

    if(start == end)                                                // leaf node
        return createNode(in[start]);

    int index = searchGreatest2(in, start, end);

    TreeNode *root = createNode(in[index]);

    root->left = constructSpecialBTFromIn2(in, start, index-1);

    root->right = constructSpecialBTFromIn2(in, index+1, end);

    return root;
}
