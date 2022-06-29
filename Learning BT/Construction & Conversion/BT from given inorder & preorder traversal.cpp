// Construct a tree from given inorder & preorder traversal

#include<iostream>
#include<queue>
#include<stack>
#include<unordered_map>

struct TreeNode
{
    char val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        val = '\0';
        left = nullptr;
        right = nullptr;
    }

    TreeNode(char x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(char x, TreeNode *lptr, TreeNode *rptr)
    {
        val = x;
        left = lptr;
        right = rptr;
    }
};

TreeNode* createNode(char x);
void insertNode(TreeNode **root,char x);                 // iterative way (using queue)
void levelorder(TreeNode *root);

int searchPartition(char in[],char val,int size);
TreeNode* constructTreeFromInAndPre(char pre[], char in[], int n);                          // passing modified arrays & size of those arrays

int searchPartition2(char in[],char val,int start, int end);
TreeNode* constructTreeFromInAndPre2(char pre[], char in[], int start, int end);            // passing exact indexes of subarrays

TreeNode* constructTreeFromInAndPre3(char pre[], char in[], int start, int end, std::unordered_map<char,int> mp);       // optimization using unordered-map for searching root


int main()
{
    char pre[] = {'A','B','D','E','C','F','G','H','I'};
    char in[] = {'D','B','E','A','F','C','H','G','I'};

    int n = sizeof(in)/sizeof(in[0]);
    TreeNode *root = constructTreeFromInAndPre(pre,in,n);

    std::cout<<"Level-order traversal of tree using method-1:\n";
    levelorder(root);

    root = constructTreeFromInAndPre2(pre,in,0,n-1);

    std::cout<<"\n\nLevel-order traversal of tree using method-2:\n";
    levelorder(root);

    std::unordered_map<char,int> mp;

    for(int i=0; i<n; i++)
        mp[in[i]] = i;

    root = constructTreeFromInAndPre3(pre,in,0,n-1,mp);

    std::cout<<"\n\nLevel-order traversal of tree using method-3:\n";
    levelorder(root);

}


TreeNode* createNode(char x)
{
    TreeNode *ptr = new TreeNode(x);
    return ptr;
}


void insertNode(TreeNode **root,char x)
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



//------------Method-1--------------


int searchPartition(char in[],char val,int size)
{
    for(int i=0;i<size;i++)
    {
        if(in[i] == val)
            return i;
    }

    return -1;
}



TreeNode* constructTreeFromInAndPre(char pre[], char in[], int n)
{
    TreeNode *root = createNode(pre[0]);                                                // since the array is modified. 1st element of pre ==> root

    int index = searchPartition(in,pre[0],n);                                           // find root in inorder traversal to get LST & RST


    if(index != 0)                                                                          // index = 0 ==> it has no left child
        root->left = constructTreeFromInAndPre(pre+1, in, index);

    if(index != n-1)                                                                        // index = n-1 ==> it has no right child
        root->right = constructTreeFromInAndPre(pre+index+1, in+index+1, n-index-1);

    return root;
}



//-------------Method-2--------------



int searchPartition2(char in[],char val,int start, int end)
{
    for(int i=start; i<=end;i++)
    {
        if(in[i] == val)
            return i;
    }
    return -1;
}



TreeNode* constructTreeFromInAndPre2(char pre[], char in[], int start, int end)
{
    if(start>end)                               // case when root has only 1 child (subtree)
        return NULL;

    static int counter = 0;                     // counter is used to keep track of root node for every subtree.
    int x = pre[counter++];

    TreeNode *root = createNode(x);             // cannot use pre[start] here because start value can be same for many calls. So suitable root value cannot be fetched

    if(start==end)
        return root;                                                            // if the root is the only element in subtree (leaf)

    int index = searchPartition2(in,x,start,end);

    root->left = constructTreeFromInAndPre2(pre,in,start,index-1);              // create LST from index start to index-1

    root->right = constructTreeFromInAndPre2(pre,in,index+1,end);               // create RST from index index+1 to end

    return root;
}



//----------------Method-3------------------


// passes unordered-map as parameter to optimize the time to search root in inorder traversal everytime.

TreeNode* constructTreeFromInAndPre3(char pre[], char in[], int start, int end, std::unordered_map<char,int> mp)
{
    if(start>end)                               // case when root has only 1 child (subtree)
        return NULL;

    static int counter = 0;                     // counter is used to keep track of root node for every subtree.
    int x = pre[counter++];

    TreeNode *root = createNode(x);             // cannot use pre[start] here because start value can be same for many calls. So suitable root value cannot be fetched

    if(start == end)
        return root;                                                            // if the root is the only element in subtree (leaf)

    int index = mp[root->val];

    root->left = constructTreeFromInAndPre3(pre,in,start,index-1,mp);              // create LST from index start to index-1

    root->right = constructTreeFromInAndPre3(pre,in,index+1,end,mp);               // create RST from index index+1 to end

    return root;
}
