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

void inorderStack(TreeNode *root);                                      // iterative
void preorderStack(TreeNode *root);                                     // iterative
void preorderStack2(TreeNode *root);                                    // iterative
void preorderStack3(TreeNode *root);                                    // iterative
void postorderStack(TreeNode *root);                                    // iterative - using 2 stacks
void postorderStack2(TreeNode *root);                                   // iterative - using 1 stack

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

    std::cout<<"\nPreorder traversal without recursion: ";
    preorderStack(root);

    std::cout<<"\nPreorder traversal-2 without recursion: ";
    preorderStack2(root);

    std::cout<<"\nPreorder traversal-3 without recursion: ";
    preorderStack3(root);

    std::cout<<"\nPostorder traversal without recursion: ";
    postorderStack(root);

    std::cout<<"\nPostorder traversal-2 without recursion: ";
    postorderStack2(root);
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



void preorderStack(TreeNode *root)
{
    // ---------------- ROOT Left Right ----------------

    // 1. Create a stack to store tree node addresses.
    // 2. Initialize current pointer with root node.
    // 3. Print current & traverse as left as possible storing all the nodes in route in the stack until NULL is hit. (current = NULL)
    // 4. If current = NULL & stack is NOT empty, Pop the top element of stack. Make current = popped_element->right. GO to step 3.
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
            std::cout<<cur->val<<' ';

            cur = cur->left;
        }

        cur = s.top();
        s.pop();

        cur = cur->right;
    }
}



void preorderStack2(TreeNode *root)
{
    // ---------------- ROOT Left Right ----------------

    // 1. Create an empty stack and push root to it.
    // 2. While stack is NOT empty - Pop all the items one by one & do the following: (a) Print it (b) push right child (c) push left child
    // (right child is pushed first so that left child is processed first)


    if(!root)
    {
        std::cout<<"\nTree Empty";
        return;
    }

    std::stack<TreeNode*> s;
    s.push(root);

    TreeNode *cur;

    while(!s.empty())
    {
        cur = s.top();
        std::cout<<cur->val<<' ';

        s.pop();

        if(cur->right)
            s.push(cur->right);

        if(cur->left)
            s.push(cur->left);
    }
}



void preorderStack3(TreeNode *root)
{
    // ---------------- ROOT Left Right ----------------

    // 1. Create a stack to store tree node addresses.
    // 2. Initialize current pointer with root node.
    // 3. Traverse as left as possible along side printing node & pushing current node's right child in the stack until NULL is hit. (current = NULL)
    // 4. If current = NULL & stack is NOT empty, Pop the top element of stack. Make current = popped_element (Processing right subtree as main tree). GO to step 3.
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
            std::cout<<cur->val<<' ';

            if(cur->right)
                s.push(cur->right);
            cur = cur->left;
        }

        if(!s.empty())                      // to handle last node when stack is already empty. Leaving current pointing to empty stack's top may cause unexpected behavior.
        {
            cur = s.top();
            s.pop();
        }
    }

}



void postorderStack(TreeNode *root)
{
    // ---------------- Left Right ROOT ----------------

    // HINT: The idea is to push REVERSE postorder traversal to a stack. Once we have the reversed postorder traversal in a stack, we can just pop all items one by one from
    // this stack and print them; this order of printing will be in postorder because of the LIFO property of stacks.
    // REVERSE postorder - ROOT Right Left (similar to preorder traversal except right is visited before left)

    // 1. Create 2 empty stacks to store tree node addresses.
    // 2. Push root to stack s1.
    // 3. If the stack s1 is not empty, perform following: (a) Push s1's top into s2 (b) Pop from s1 (c) push left child of popped element (d) Push right child of popped element
    //    (left child is pushed first so that right child is processed first for reverse post-order traversal)
    // 4. If the stack s1 is empty - start popping & printing every element from s2.


    if(!root)
    {
        std::cout<<"\n\nTree Empty";
        return;
    }

    std::stack<TreeNode*> s1,s2;
    TreeNode *cur = root;

    s1.push(cur);

    while(!s1.empty())
    {
        cur = s1.top();
        s2.push(cur);
        s1.pop();

        if(cur->left)
            s1.push(cur->left);

        if(cur->right)
            s1.push(cur->right);
    }

    while(!s2.empty())
    {
        std::cout<<(s2.top())->val<<' ';
        s2.pop();
    }
}



void postorderStack2(TreeNode *root)
{
    // ---------------- Left Right ROOT ----------------

    // HINT : The idea is to move down to leftmost node using left pointer. While moving down, push root�s right child && root to stack.
    // Once we reach leftmost node, print it if it doesn�t have a right child. If it has a right child, then change root so that the right child is processed before root itself

    // 1. Create empty stack
    // 2. Push root's right child & root in stack.
    // 3. If the stack is NOT empty, perform following:
    // 4. Perform following while root is NOT NULL: (a) Push right child of root, if it exists (b) push root itself (c) traverse left subtree by setting root = root->left
    // 5. POP from stack:
    //   (a) If the popped item has right child & right child is at top of stack, then remove the right child from stack, push the root back and set root = root->right.
    //   (b) Else, print root & set root = NULL
    // Repeat steps 4-5 until stack is empty



    if(!root)
    {
        std::cout<<"\n\nTree Empty";
        return;
    }

    std::stack<TreeNode*> s;

    if(root->right)
        s.push(root->right);
    s.push(root);

    root = root->left;

    while(!s.empty())
    {
        while(root)                                 // traverse the left subtree until root is NULL
        {
            if(root->right)
                s.push(root->right);                                        // push right subtree before root itself so that root is executed first which can later be exchanged
            s.push(root);                                                   // with right child to process right subtree before root itself.

            root = root->left;
        }

        root = s.top();                                                     // POP leftmost node
        s.pop();

        if(!s.empty() && root->right && root->right == s.top())     // 1st condition is for empty stack(root node deleted) as for empty stack calling top() may create unexpected results
                                                                    // 2nd condition is for traversing right subtree before printing root value
        {                                                           // 3rd condition takes care of root node to be printed after right subtree is done traversing

            s.pop();                                                        // POP right child of root & reenter root node as our priority is to traverse right subtree of root
            s.push(root);                                                   // before root itself.

            root = root->right;                                             // setting root to its right node to traverse right subtree like the main tree & process continues
        }


        else                                                    // print root if either it is leftmost child of its subtree or it is rightmost child or root when its right
        {                                                       // subtree is done traversing
            std::cout<<root->val<<' ';
            root = NULL;                                                    // set root to NULL to pop parent of recently printed node.
        }
    }

}
