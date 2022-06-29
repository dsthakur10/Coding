// Find postorder traversal from given inorder & preorder traversals.

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
void insertNode(TreeNode **root,int x);                                         // iterative way (using queue)

int searchPartition(int in[],int val,int size);                                 // find index of root to identify partition of LST & RST & recurse accordingly
void findPostorder(int pre[],int in[],int n);                                   // recursively traverse left & right subtrees & print first element of preorder in the end.

std::vector<int> getPostorder(int pre[],int in[],int n);

int main()
{
    int pre[] = {1,2,4,5,3,6};
    int in[] = {4,2,5,1,3,6};
    int size = sizeof(pre)/sizeof(pre[0]);
    std::vector<int> post;

    std::cout<<"\n\nGiven Pre-order = ";
    for(int nums:pre)
        std::cout<<nums<<' ';

    std::cout<<"\n\nGiven In-order = ";
    for(int nums:in)
        std::cout<<nums<<' ';

    std::cout<<"\n\nPost-order for the given tree = ";
    findPostorder(pre,in,size);


    post = getPostorder(pre,in,size);
    std::cout<<"\n\nPost-order for the given tree second way = ";
    for(int nums:post)
        std::cout<<nums<<' ';

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



int searchPartition(int in[],int val,int size)
{
    for(int i=0;i<size;i++)
    {
        if(in[i] == val)
            return i;
    }

    return -1;
}


void findPostorder(int pre[],int in[],int n)
{
    // PreOrder : ROOT Left Right
    // Inorder : Left ROOT Right
    // Postorder : ROOT Left Right

    // HINT : Root is always first item in preorder & last item in postorder. First process recursively LST, then recursively RST & print the root in the end.

    // To find boundaries of left and right subtrees in pre[] and in[], we search root INDEX in in[]
    // In[] : All elements before INDEX in in[] are elements of LST, and all elements after INDEX are elements of RST.
    // Pre[] : All elements after INDEX in in[] are elements of RST, elements before INDEX (including the element at INDEX and excluding the first element) are elements LST.


    int x = pre[0];

    int index = searchPartition(in , x , n);

    if(index != 0)                                                              // traverse left subtree recursively
        findPostorder(pre+1 , in , index);

    if(index != n-1)                                                            // traverse right subtree recursively
        findPostorder(pre+index+1 , in+index+1, n-index-1);

    std::cout<<pre[0]<<' ';                                                     // print root
}



std::vector<int> getPostorder(int pre[],int in[],int n)
{
    std::vector<int> post,left,right;
    int x = pre[0];

    int index = searchPartition(in , x , n);

    if(index != 0)                                                              // traverse left subtree recursively
        left = getPostorder(pre+1 , in , index);

    if(index != n-1)                                                            // traverse right subtree recursively
        right = getPostorder(pre+index+1 , in+index+1, n-index-1);


    if(!left.empty())                                                           // add LST first
        post.insert(post.begin(),left.begin(),left.end());

    if(!right.empty())                                                          // add RST next
        post.insert(post.end(),right.begin(),right.end());

    post.push_back(pre[0]);                                                     // finally add root

    return post;
}
