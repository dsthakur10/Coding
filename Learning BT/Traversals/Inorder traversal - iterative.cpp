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
void insertNode(TreeNode **root,int x);                 // iterative (using queue)

void inorderStack(TreeNode *root);                      // iterative

int main()
{
    TreeNode *root = NULL;

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

    std::cout<<"\nInorder traversal without recursion: ";
    inorderStack(root);
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


void inorderStack(TreeNode *root)
{
    // ---------------- Left ROOT Right ----------------

    // 1. Create a stack to store tree node addresses.
    // 2. Initialize current pointer with root node.
    // 3. Traverse as left as possible storing all the nodes in route in the stack until NULL is hit. (current = NULL)
    // 4. If current = NULL & stack is NOT empty, Pop the top element of stack. PRINT it & make current = popped_element->right. GO to step 3.
    // 5. If current = NULL & stack EMPTY , return


    if(!root)
    {
        std::cout<<"\n\nTree Empty";
        return;
    }

    std::stack<TreeNode*> s;

    TreeNode *cur = root;

    while(cur || !s.empty())                // either of them must satisfy to continue. There may exist the case when stack will be empty
    {                                       // but cur pointer will point to right node of some node (root of tree or any other right subtree)
        while(cur)
        {
            s.push(cur);
            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        std::cout<<cur->val<<' ';
        cur = cur->right;
    }
}
