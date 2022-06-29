// Given a binary tree containing n nodes.
// The problem is to replace each node in the binary tree with the sum of its inorder predecessor and inorder successor.


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

TreeNode* sumOfPreAndSucc(TreeNode *root);                                      // creates 2 arrays in[] & sum[] to store inorder & sum of predecessors & successors respectively
std::vector<int> getInorder(TreeNode *root);
TreeNode* putInorder(TreeNode* root, std::vector<int> sum);


TreeNode* sumOfPreAndSucc2(TreeNode *root);                                     // creates 1 array in[] to store inorder. Later sum of predecessors & successors are put
void getInorder2(TreeNode *root, std::vector<int>& in);                         // directly at the time of traversing.
TreeNode* putInorder2(TreeNode* root, std::vector<int> in);                     // NOTE: array in[] is passed by reference in getInorder to reflect changes in it.


// Since Inorder predecessor & successor is what we are looking for, get inorder traversal stored in an array. Then use this array to recursively replace tree values by sum
// For inorder index i , arr[i] = sum = arr[i-1] + arr[i+1]. Perform inorder traversal & modify root values recursively.

int main()
{
    TreeNode *root = NULL;

/*
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

    TreeNode *temp = root;

    while(temp->right)
        temp = temp->right;

    temp->left = createNode(12);
    temp->right = createNode(13);
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


    std::cout<<"Tree before modification: ";
    levelorder(root);
/*
    root = sumOfPreAndSucc(root);

    std::cout<<"\n\nTree after modification: ";
    levelorder(root);
*/

    root = sumOfPreAndSucc2(root);

    std::cout<<"\n\nTree after modification: ";
    levelorder(root);

/*
    std::cout<<"\n\nInorder traversal: ";
    std::vector<int> in = inorder(root);
    for(int nums:in)
        std::cout<<nums<<" ";
*/

    return 0;
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



TreeNode* sumOfPreAndSucc(TreeNode *root)
{
    std::vector<int> in = getInorder(root);
    std::vector<int> sum = in;

    for(int i=0;i<in.size();i++)
    {
        if(i==0)
            sum[i] = in[i+1];

        else if(i==in.size()-1)
            sum[i] = in[i-1];

        else
            sum[i] = in[i-1] + in[i+1];
    }

    return putInorder(root,sum);

}


std::vector<int> getInorder(TreeNode *root)
{
    std::vector<int> in,left,right;

    if(!root)
        return {};

    left = getInorder(root->left);
    if(!left.empty())
        in.insert(in.begin(),left.begin(),left.end());

    in.push_back(root->val);

    right = getInorder(root->right);
    if(!right.empty())
        in.insert(in.end(),right.begin(),right.end());

    return in;
}


TreeNode* putInorder(TreeNode* root, std::vector<int> sum)
{
    static int counter = 0;

    if(!root)
        return NULL;

    root->left = putInorder(root->left,sum);

    root->val = sum[counter++];

    root->right = putInorder(root->right,sum);

    return root;
}







TreeNode* sumOfPreAndSucc2(TreeNode *root)
{
    std::vector<int> arr;
    getInorder2(root,arr);
    return putInorder2(root,arr);
}


void getInorder2(TreeNode *root,std::vector<int>& in)
{
    if(!root)
        return;

    getInorder2(root->left,in);

    in.push_back(root->val);

    getInorder2(root->right,in);

}


TreeNode* putInorder2(TreeNode* root, std::vector<int> in)
{
    static int counter = 0;

    if(!root)
        return NULL;

    root->left = putInorder2(root->left,in);

    if(counter == 0)
        root->val = in[1];

    else if(counter == in.size()-1)
        root->val = in[in.size()-2];

    else
        root->val = in[counter-1] + in[counter+1];

    counter++;

    root->right = putInorder2(root->right,in);

    return root;
}
