// Construct a tree from given inorder & preorder traversal

#include<iostream>
#include<queue>
#include<stack>
#include<unordered_map>

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

int searchPartition(int in[],int val,int size);
TreeNode* constructTreeFromInAndPost(int post[], int in[], int n);                          // passing modified arrays & size of those arrays

int searchPartition2(int in[],int val,int start, int end);
TreeNode* constructTreeFromInAndPost2(int post[], int in[], int start, int end);            // passing exact indexes of subarrays

TreeNode* constructTreeFromInAndPost3(int post[], int in[], int start, int end, std::unordered_map<int,int> mp);       // optimization using unordered-map for searching root


int main()
{
    int post[] = {8,4,5,2,6,7,3,1};
    int in[] = {4,8,2,5,1,6,3,7};

    //int post[] = {2,4,5,3,1};
    //int in[] = {2,1,4,3,5};

    //int post[] = {7,6,5,4,3,2,1};
    //int in[] = {7,6,5,4,3,2,1};

    //int post[] = {7,6,5,4,3,2,1};
    //int in[] = {1,2,3,4,5,6,7};

    int n = sizeof(in)/sizeof(in[0]);
    TreeNode *root = constructTreeFromInAndPost(post,in,n);

    std::cout<<"Level-order traversal of tree using method-1:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of tree using method-1:\n";
    inorder(root);


    root = constructTreeFromInAndPost2(post,in,0,n-1);

    std::cout<<"\n\nLevel-order traversal of tree using method-2:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of tree using method-2:\n";
    inorder(root);


    std::unordered_map<int,int> mp;

    for(int i=0; i<n; i++)
        mp[in[i]] = i;

    root = constructTreeFromInAndPost3(post,in,0,n-1,mp);

    std::cout<<"\n\nLevel-order traversal of tree using method-3:\n";
    levelorder(root);

    std::cout<<"\nInorder traversal of tree using method-3:\n";
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




//------------Method-1--------------


int searchPartition(int in[],int val,int size)
{
    for(int i=0;i<size;i++)
    {
        if(in[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructTreeFromInAndPost(int post[], int in[], int n)
{
    TreeNode *root = createNode(post[n-1]);                                                // since the array is modified. last element of post ==> root

    int index = searchPartition(in,post[n-1],n);                                           // find root in inorder traversal to get LST & RST


    if(index != 0)                                                                          // index = 0 ==> it has no left child
        root->left = constructTreeFromInAndPost(post, in, index);

    if(index != n-1)                                                                        // index = n-1 ==> it has no right child
        root->right = constructTreeFromInAndPost(post+index, in+index+1, n-index-1);

    return root;
}



//-------------Method-2--------------



int searchPartition2(int in[],int val,int start, int end)
{
    for(int i=start; i<=end;i++)
    {
        if(in[i] == val)
            return i;
    }
    return -1;
}



TreeNode* constructTreeFromInAndPost2(int post[], int in[], int start, int end)
{
    if(start>end)                               // case when root has only 1 child (subtree)
        return NULL;

    static int counter = end-start;                     // counter is used to keep track of root node for every subtree.
    int x = post[counter--];

    TreeNode *root = createNode(x);             // cannot use post[end] here because end value can be same for many calls. So suitable root value cannot be fetched

    if(start==end)
        return root;                                                            // if the root is the only element in subtree (leaf)

    int index = searchPartition2(in,x,start,end);

    // RST is traversed first because in postorder root is fetched from the end & order is LEFT-RIGHT-ROOT

    root->right = constructTreeFromInAndPost2(post,in,index+1,end);             // create RST from index index+1 to end

    root->left = constructTreeFromInAndPost2(post,in,start,index-1);            // create LST from index start to index-1

    return root;
}



//----------------Method-3------------------


// passes unordered-map as parameter to optimize the time to search root in inorder traversal everytime.

TreeNode* constructTreeFromInAndPost3(int post[], int in[], int start, int end, std::unordered_map<int,int> mp)
{
    if(start>end)                               // case when root has only 1 child (subtree)
        return NULL;

    static int counter = end-start;                     // counter is used to keep track of root node for every subtree.
    int x = post[counter--];

    TreeNode *root = createNode(x);             // cannot use post[end] here because start value can be same for many calls. So suitable root value cannot be fetched

    if(start == end)
        return root;                                                            // if the root is the only element in subtree (leaf)

    int index = mp[root->val];

    root->right = constructTreeFromInAndPost3(post,in,index+1,end,mp);               // create RST from index index+1 to end

    root->left = constructTreeFromInAndPost3(post,in,start,index-1,mp);              // create LST from index start to index-1

    return root;
}
