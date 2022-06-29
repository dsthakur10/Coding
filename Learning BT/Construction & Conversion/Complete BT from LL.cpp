// Given Linked List Representation of Complete Binary Tree, construct the complete Binary tree.

// A complete binary tree can be represented in an array in the following approach.
// If root node is stored at index i, its left, and right children are stored at indices 2*i+1, 2*i+2 respectively.

// Suppose tree is represented by a linked list in same way, how do we convert this into normal linked representation of binary tree where every node has data,
// left and right pointers? In the linked list representation, we cannot directly access the children of the current node unless we traverse the list.



// LL ==> 10->12->15->25->30->36

// Complete BT ==>
//                    10
//             12           15
//          25    30    36


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


class ListNode
{
public:
    int val;
    ListNode *next;

    ListNode()
    {
        val = 0;
        next = NULL;
    }

    ListNode(int key)
    {
        val = key;
        next = NULL;
    }
};



void insertListNode(ListNode **head, int val);
void displayList(ListNode *head);

TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);
void inorder(TreeNode *root);

TreeNode* convertListToBT(ListNode* head);


int main()
{
    ListNode *head = NULL;
/*
    insertListNode(&head,100);
    insertListNode(&head,88);
    insertListNode(&head,67);
    insertListNode(&head,44);
    insertListNode(&head,36);
    insertListNode(&head,30);
    insertListNode(&head,25);
    insertListNode(&head,15);
    insertListNode(&head,12);
    insertListNode(&head,10);
*/

    for(int i=18;i>=1;i--)
        insertListNode(&head,i);

    std::cout<<"\n\nLinked List: \n";
    displayList(head);

    TreeNode *root;
    root = convertListToBT(head);

    std::cout<<"\n\nComplete Binary Tree from given linked list: \n";
    levelorder(root);

    std::cout<<"\n\nInorder traversal: ";
    inorder(root);

}



void insertListNode(ListNode **head, int val)
{
    ListNode *ptr = new ListNode(val);
    ptr->next = *head;
    *head = ptr;
    std::cout<<"ListNode "<<val<< " inserted\n";
}


void displayList(ListNode *head)
{
    if(!head)
    {
        std::cout<<"\nList Empty";
        return;
    }

    ListNode *temp = head->next;

    std::cout<<head->val;
    while(temp)
    {
        std::cout<<" -> "<<temp->val;
        temp = temp->next;
    }
    std::cout<<"\n";
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




TreeNode* convertListToBT(ListNode* head)
{
    if(!head)
        return NULL;

    std::queue<TreeNode*> q;
    TreeNode *temp;

    TreeNode *root = createNode(head->val);
    head = head->next;

    q.push(root);

    while(head)
    {
        temp = q.front();
        q.pop();

        if(head)
        {
            temp->left = createNode(head->val);
            head = head->next;
            q.push(temp->left);
        }

        if(head)
        {
            temp->right = createNode(head->val);
            head = head->next;
            q.push(temp->right);
        }
    }

    return root;
}
