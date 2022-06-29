// Given a ternary tree, create a doubly linked list out of it. A ternary tree is just like binary tree but instead of having two nodes, it has three nodes i.e. left, middle, right.

// The doubly linked list should holds following properties –

// Left pointer of ternary tree should act as prev pointer of doubly linked list.
// Middle pointer of ternary tree should not point to anything.
// Right pointer of ternary tree should act as next pointer of doubly linked list.
// Each node of ternary tree is inserted into doubly linked list before its subtrees and for any node, its left child will be inserted first, followed by mid and right child (if any).


/*
                    30

    5               11              63

1   4   8       6   7   15     31  55  65


Doubly LL ==>   NULL <- 30 <-> 5 <-> 1 <-> 4 <-> 8 <-> 11 <-> 6 <-> 7 <-> 15 <-> 63 <-> 31 <-> 55 <-> 65 -> NULL

*/


#include<iostream>
#include<queue>
#include<stack>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *middle;
    TreeNode *right;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        middle = nullptr;
        right = nullptr;
    }

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        middle = nullptr;
        right = nullptr;
    }

    TreeNode(int x, TreeNode *lptr, TreeNode *mptr, TreeNode *rptr)
    {
        val = x;
        left = lptr;
        middle = mptr;
        right = rptr;
    }
};


class ListNode
{
public:
    int val;
    ListNode *prev;
    ListNode *next;

    ListNode()
    {
        val = 0;
        prev = NULL;
        next = NULL;
    }

    ListNode(int key)
    {
        val = key;
        prev = NULL;
        next = NULL;
    }
};



TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);
void inorder(TreeNode *root);
void convertTernaryToDoublyList(TreeNode *root, ListNode **head);
void convertTernaryToDoublyList2(TreeNode *root, ListNode **head);


void displayListTail(ListNode *head);
void displayList(ListNode *head);


int main()
{
    ListNode *head = NULL;
    ListNode *head2 = NULL;
    TreeNode *root = NULL;

    insertNode(&root,30);
    insertNode(&root,5);
    insertNode(&root,11);
    insertNode(&root,63);
    insertNode(&root,1);
    insertNode(&root,4);
    insertNode(&root,8);
    insertNode(&root,6);
    insertNode(&root,7);
    insertNode(&root,15);
    insertNode(&root,31);
    insertNode(&root,55);
    insertNode(&root,65);

    std::cout<<"Ternary Tree: \n";
    levelorder(root);

    convertTernaryToDoublyList(root,&head);

    std::cout<<"\n\nDoubly LL from ternary tree: \n";
    displayListTail(head);

    convertTernaryToDoublyList2(root,&head2);

    std::cout<<"\n\nDoubly LL from ternary tree-2: \n";
    displayList(head2);

}


void displayListTail(ListNode *head)
{
    if(!head)
    {
        std::cout<<"\nList Empty";
        return;
    }

    while(head->prev)
        head = head->prev;

    std::cout<<head->val;
    ListNode *temp = head->next;

    while(temp)
    {
        std::cout<<" -> "<<temp->val;
        temp = temp->next;
    }
    std::cout<<"\n";
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

        if(!temp->middle)
        {
            temp->middle = ptr;
            return;
        }

        if(!temp->right)
        {
            temp->right = ptr;
            return;
        }

        q.push(temp->left);
        q.push(temp->middle);
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

            if(temp->middle)
                q.push(temp->middle);

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

    inorder(root->middle);

    inorder(root->right);
}



void convertTernaryToDoublyList(TreeNode *root, ListNode **head)
{
    if(!root)
        return;

    ListNode *temp = new ListNode(root->val);

    if(*head)
        (*head)->next = temp;
    temp->prev = *head;
    *head = temp;

    convertTernaryToDoublyList(root->left, head);

    convertTernaryToDoublyList(root->middle, head);

    convertTernaryToDoublyList(root->right, head);

}




void convertTernaryToDoublyList2(TreeNode *root, ListNode **head)
{
    std::queue<TreeNode*> q;
    TreeNode *temp;
    ListNode *ptr,*cur = *head;

    q.push(root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(temp->right)
            q.push(temp->right);

        if(temp->middle)
            q.push(temp->middle);

        if(temp->left)
            q.push(temp->left);

        ptr = new ListNode(temp->val);
        if(cur)
            cur->next = ptr;
        ptr->prev = cur;

        cur = ptr;
    }
}
