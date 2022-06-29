// Construct a tree from given inorder & level-order traversal

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

int searchPartition(int in[],int val,int inStart,int inEnd);
int* extractKeys(int level[], int in[], int n, int m);
TreeNode* constructTreeFromInAndLevel(int level[], int in[], int n, int inStart, int inEnd);



int main()
{
    //int in[] = {4, 8, 10, 12, 14, 20, 22};
    //int level[] = {20, 8, 22, 4, 12, 10, 14};

    int in[] = {8,4,9,2,5,1,6,3,10,7,11};
    int level[] = {1,2,3,4,5,6,7,8,9,10,11};

    int n = sizeof(in)/sizeof(in[0]);

    TreeNode *root = constructTreeFromInAndLevel(level, in, n, 0, n-1);

    std::cout<<"Level-order traversal of tree using method-1:\n";
    levelorder(root);

    std::cout<<"\n\nInorder traversal of tree using method-1:\n";
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



int searchPartition(int in[],int val,int inStart, int inEnd)
{
    for(int i=inStart ;i<=inEnd; i++)
    {
        if(in[i] == val)
            return i;
    }
    return -1;
}



int* extractKeys(int level[], int in[], int n, int m)               // m is size of inorder. n is size of level-order.   m < n
{
    int *newlevel = new int[m];
    // static int newlevel[m];                           // error: Cannot provide variable in static initialization of array. size must be constant
    // int newlevel[m];                                 // local variable. Gets deleted after function call is over.
    int j=0;

    for(int i=0; i<n; i++)
    {
        if(searchPartition(in,level[i],0,m-1) != -1)                // order of level order is important.
        {
            newlevel[j] = level[i];
            j++;
        }
    }

    return newlevel;
}


TreeNode* constructTreeFromInAndLevel(int level[], int in[], int n, int inStart, int inEnd)
{
    if(inStart > inEnd)
        return NULL;

    TreeNode *root = createNode(level[0]);

    if(inStart == inEnd)
        return root;

    int index = searchPartition(in,root->val,inStart,inEnd);

    int* LST = extractKeys(level+1, in, n-1, index);

    int* RST = extractKeys(level+1, in+index+1, n-1, n-1);

    root->left = constructTreeFromInAndLevel(LST, in, index-inStart, inStart, index-1);

    root->right = constructTreeFromInAndLevel(RST, in, inEnd-index, index+1, inEnd);

    delete[] LST;
    delete[] RST;

    return root;
}
