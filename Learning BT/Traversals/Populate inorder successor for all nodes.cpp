// Given a Binary Tree where each node has the following structure, write a function to populate the next pointer for all nodes.
// The next pointer for every node should be set to point to inorder successor.

#include<iostream>
#include<queue>
#include<stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *next;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
        next = nullptr;
    }

    TreeNode(int x, TreeNode *lptr, TreeNode *rptr, TreeNode *nptr)
    {
        val = x;
        left = lptr;
        right = rptr;
        next = nptr;
    }
};

TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                                         // iterative way (using queue)
void levelorder(TreeNode *root);

// Method-1
TreeNode* populateSuccessor(TreeNode *root);                                    // store nodes by Inorder traversal in an array. Then simply traverse array
void getSuccessor(TreeNode *root, std::vector<TreeNode*>& in);                  // arr[i]->next = arr[i+1]
                                                                                // Time = 3*O(n) + O(n) Space = O(n)
// Method-2
void populateSuccessor2(TreeNode *root);                                        // Apply reverse Inorder traversal & store previously visited node. Make current node point to
                                                                                // this stored node as in reverse inorder, previously visited node is successor of current node.
                                                                                // Time = 3*O(n) Space = O(1)
int main()
{
    TreeNode *root = NULL;


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

    //root = populateSuccessor(root);
    populateSuccessor2(root);

    levelorder(root);

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

        std::cout<<"\ncurrent = "<<temp->val<<" next = "<<(temp->next ? temp->next->val : -1);

        if(temp->left)
            q.push(temp->left);

        if(temp->right)
            q.push(temp->right);
    }
}



// -------------Method-1-------------

// Store nodes by Inorder traversal in an array. Then simply traverse array. Make arr[i]->next = arr[i+1] since in inorder traversal (i+1)th node is the successor of ith node

// Time = 3*O(n) + O(n) Space = O(n)


TreeNode* populateSuccessor(TreeNode *root)
{
    std::vector<TreeNode*> arr;
    getSuccessor(root,arr);

    arr.push_back(nullptr);                                        // for rightmost element, successor will be NULL

    for(int i=0;i<arr.size()-1;i++)                                 // since we are storing nodes in inorder array, we can directly manipulate nodes without traversing again
        arr[i]->next = arr[i+1];                                    // recursively by putInorder method

    return root;
}


void getSuccessor(TreeNode *root, std::vector<TreeNode*>& in)
{
    if(!root)
        return;

    getSuccessor(root->left,in);

    in.push_back(root);

    getSuccessor(root->right,in);
}



// -------------Method-2-------------

// Apply reverse Inorder traversal & store previously visited node. Make current node point to this stored node as in reverse inorder,
// previously visited node is successor of current node.

// Time = 3*O(n) Space = O(1)


void populateSuccessor2(TreeNode *root)
{
    static TreeNode *succ = nullptr;

    if(!root)
        return;

    populateSuccessor2(root->right);

    root->next = succ;
    succ = root;

    populateSuccessor2(root->left);

}
