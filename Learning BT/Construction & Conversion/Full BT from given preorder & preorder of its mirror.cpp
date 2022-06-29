// Given two arrays that represent Preorder traversals of a full binary tree and its mirror tree, construct the binary tree using these two preorder traversals.


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

int searchPartition(int preMirror[],int val,int size);
TreeNode* constructFullBTFromPreAndPreMirror(int pre[], int preMirror[], int n);

int searchPartition2(int preMirror[],int val,int pmStart, int pmEnd);
TreeNode* constructFullBTFromPreAndPreMirror2(int pre[], int preMirror[], int pmStart, int pmEnd);



int main()
{

    int pre[] = {1,2,4,5,3,6,7};
    int preMirror[] = {1,3,7,6,2,5,4};

    //int pre[] = {1,2,4,5,3};
    //int preMirror[] = {1,3,2,5,4};

    //int pre[] = {1,2,3,4,5};
    //int preMirror[] = {1,3,5,4,2};

    //int pre[] = {1,2,4,5,3,6,8,9,7};
    //int preMirror[] = {1,3,7,6,9,8,2,5,4};

    //int pre[] = {1,2,3,4,5,6,7};
    //int preMirror[] = {1,3,5,7,6,4,2};


    int n = sizeof(pre)/sizeof(pre[0]);
    TreeNode *root = constructFullBTFromPreAndPreMirror(pre,preMirror,n);

    std::cout<<"Level-order traversal of Full Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Full Binary Tree:\n";
    inorder(root);


    root = constructFullBTFromPreAndPreMirror2(pre,preMirror,0,n-1);

    std::cout<<"\n\nLevel-order traversal-2 of Full Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal-2 of Full Binary Tree:\n";
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




// --------------Method-1--------------


int searchPartition(int preMirror[],int val,int size)
{
    for(int i=0; i<size; i++)
    {
        if(preMirror[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructFullBTFromPreAndPreMirror(int pre[], int preMirror[], int n)
{
    TreeNode *root = createNode(pre[0]);

    if(n==1)
        return root;

    int index = searchPartition(preMirror,pre[1],n);

    root->left = constructFullBTFromPreAndPreMirror(pre+1, preMirror+index, n-index);

    root->right = constructFullBTFromPreAndPreMirror(pre+n-index+1, preMirror+1, index-1);

    return root;
}




//-------------Method-2-------------


int searchPartition2(int preMirror[],int val,int pmStart, int pmEnd)
{
    for(int i=pmStart; i<=pmEnd; i++)
    {
        if(preMirror[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructFullBTFromPreAndPreMirror2(int pre[], int preMirror[], int pmStart, int pmEnd)
{
    if(pmStart > pmEnd)
        return NULL;

    static int counter = 0;
    int x = pre[counter++];
    TreeNode *root = createNode(x);

    if(pmStart == pmEnd)
        return root;

    int index = searchPartition2(preMirror, pre[counter], pmStart, pmEnd);

    root->left = constructFullBTFromPreAndPreMirror2(pre, preMirror, index, pmEnd);

    root->right = constructFullBTFromPreAndPreMirror2(pre, preMirror, pmStart+1, index-1);

    return root;
}
