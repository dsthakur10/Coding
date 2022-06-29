// Given an array ‘pre[]’ that represents Preorder traversal of a special binary tree where every node has either 0 or 2 children.

// One more array ‘preLN[]’ is given which has only two possible values ‘L’ and ‘N’.
// Value ‘L’ in ‘preLN[]’ indicates that the corresponding node in Binary Tree is a leaf node and value ‘N’ indicates that the corresponding node is a non-leaf node.

// Write a function to construct the tree from the given two arrays.


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

//int searchPartition(int preMirror[],int val,int size);
TreeNode* constructFullBTFromPreAndSpecial(int pre[], char preLN[], int& index);

//int searchPartition2(int preMirror[],int val,int pmStart, int pmEnd);
TreeNode* constructFullBTFromPreAndSpecial2(int pre[], char preLN[]);



int main()
{

    //int pre[] = {1,2,4,5,3,6,7};
    //char preLN[] = {'N','N','L','L','N','L','L'};

    //int pre[] = {1,2,4,5,3};
    //char preLN[] = {'N','N','L','L','L'};

    //int pre[] = {1,2,4,5,3,6,8,9,7};
    //char preLN[] = {'N','N','L','L','N','N','L','L','L'};

    int pre[] = {1,2,3,4,5,6,7};
    char preLN[] = {'N','L','N','L','N','L','L'};

    //int pre[] = {5};
    //char preLN[] = {'L'};

    int index = 0;
    TreeNode *root = constructFullBTFromPreAndSpecial(pre,preLN,index);

    std::cout<<"Level-order traversal of Full Binary Tree:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of Full Binary Tree:\n";
    inorder(root);


    root = constructFullBTFromPreAndSpecial2(pre,preLN);

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

TreeNode* constructFullBTFromPreAndSpecial(int pre[], char preLN[], int& index)
{
    TreeNode *root = createNode(pre[index]);

    if(preLN[index++] == 'L')
        return root;

    root->left = constructFullBTFromPreAndSpecial(pre,preLN,index);

    root->right = constructFullBTFromPreAndSpecial(pre,preLN,index);

    return root;
}



// --------------Method-2--------------

TreeNode* constructFullBTFromPreAndSpecial2(int pre[], char preLN[])
{
    static int counter=0;

    TreeNode *root = createNode(pre[counter]);

    if(preLN[counter++] == 'L')
        return root;

    root->left = constructFullBTFromPreAndSpecial2(pre,preLN);

    root->right = constructFullBTFromPreAndSpecial2(pre,preLN);

    return root;
}
