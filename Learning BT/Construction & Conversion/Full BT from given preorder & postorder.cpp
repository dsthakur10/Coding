// Given two arrays that represent preorder and postorder traversals of a full binary tree, construct the binary tree.

// A Full Binary Tree is a binary tree where every node has either 0 or 2 children
// Following are examples of Full Trees.

/*
        1
      /   \
    2       3
  /  \     /  \
 4    5   6    7

          1
        /   \
      2       3
    /  \     /  \
   4    5   6    7
 /  \
8    9


       1
     /   \
   2      3
        /   \
       4     5
           /   \
          6    7
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

int searchPartition(int post[],int val,int size);
TreeNode* constructFullBTFromPreAndPost(int pre[], int post[], int n);


int searchPartition2(int post[],int val,int postStart,int postEnd);
TreeNode* constructFullBTFromPreAndPost2(int pre[], int post[], int postStart, int postEnd);


int main()
{

    //int pre[] = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    //int post[] = {8, 9, 4, 5, 2, 6, 7, 3, 1};

    //int pre[] = {1, 2, 3, 4, 5, 6, 7};
    //int post[] = {2, 4, 6, 7, 5, 3, 1};

    //int pre[] = {1,2,3,4,6,7,5};
    //int post[] = {2,6,7,4,5,3,1};

    //int pre[] = {2};
    //int post[] = {2};

    int pre[] = {1,2,3,4,5};
    int post[] = {2,4,5,3,1};

    int n = sizeof(pre)/sizeof(pre[0]);
    TreeNode *root = constructFullBTFromPreAndPost(pre,post,n);

    std::cout<<"Level-order traversal of Full tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Full tree:\n";
    inorder(root);

    root = constructFullBTFromPreAndPost2(pre,post,0,n-1);

    std::cout<<"\n\nLevel-order traversal-2 of Full tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal-2 of Full tree:\n";
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


//-------------Method-1----------------


int searchPartition(int post[],int val,int size)
{
    for(int i=0; i<size; i++)
    {
        if(post[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructFullBTFromPreAndPost(int pre[], int post[], int n)
{
    TreeNode *root = createNode(pre[0]);

    if(n==1)
        return root;

    int index = searchPartition(post,pre[1],n);

    root->left = constructFullBTFromPreAndPost(pre+1, post, index+1);

    root->right = constructFullBTFromPreAndPost(pre+2+index, post+1+index, n-index-2);

    return root;
}



//---------------Method-2-----------------


int searchPartition2(int post[],int val,int postStart,int postEnd)
{
    for(int i=postStart; i<=postEnd; i++)
    {
        if(post[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructFullBTFromPreAndPost2(int pre[], int post[], int postStart, int postEnd)
{
    if(postStart > postEnd)
        return NULL;

    static int counter = 0;
    int x = pre[counter++];
    TreeNode *root = createNode(x);

    if(postStart == postEnd)
        return root;

    int index = searchPartition2(post, pre[counter], postStart, postEnd);

    root->left = constructFullBTFromPreAndPost2(pre, post, postStart, index);

    root->right = constructFullBTFromPreAndPost2(pre, post, index+1, postEnd-1);

    return root;
}
