#include<iostream>

class Node
{
public:
    int data;
    Node *next;

    Node()
    {
        data = 0;
        next = NULL;
    }

    Node(int key)
    {
        data = key;
        next = NULL;
    }
};


void insertNode(Node **head, int val);                      // single pointer will work as pass by value. double pointer must be
void deleteNode(Node **head, int val);                      // used to locate the changes in head pointer with every operation.
void displayList(Node *head);                               // this is because we are using operations globally & not for a
void reverseList(Node **head);                              // particular SLL. Also if changes should have to be reflected in
Node* recReverseList(Node *prev,Node *cur);                 // parameter passed, we must use pass by reference

Node* reverseList(Node *head);

Node* recReverseList(Node *root);

int main()
{
    Node *head = NULL;

    insertNode(&head,5);
    insertNode(&head,8);
    insertNode(&head,12);
    insertNode(&head,20);
    insertNode(&head,50);
    insertNode(&head,77);
    insertNode(&head,100);
    insertNode(&head,100);

    displayList(head);

    deleteNode(&head,20);
    deleteNode(&head,100);

    displayList(head);

    std::cout<<"\nReversed Linked list....\n";
    //reverseList(&head);
    //head = recReverseList(NULL,head);
    head = recReverseList(head);

    displayList(head);
    return 0;
}


void insertNode(Node **head, int val)
{
    Node *ptr = new Node(val);
    ptr->next = *head;
    *head = ptr;
    std::cout<<"Node "<<val<< " inserted\n";
}


void deleteNode(Node **head, int val)
{
    if(*head == NULL)
    {
        std::cout<<"\nEmpty list";
        return;
    }

    Node *cur,*prev;

    if((*head)->data == val)
    {
        cur = *head;
        *head = (*head)->next;
        delete cur;
        std::cout<<"\nNode "<<val<<" deleted";
        return;
    }

    prev = *head;
    cur = (*head)->next;

    while(cur)
    {
        if(cur->data == val)
        {
            prev->next = cur->next;
            delete cur;
            std::cout<<"\nNode "<<val<<" deleted";
            return;
        }

        prev = cur;
        cur = cur->next;
    }

    std::cout<<"\n\nNode DOEST NOT EXIST";
}


void displayList(Node *head)
{
    if(!head)
    {
        std::cout<<"\nList Empty";
        return;
    }

    Node *temp = head->next;

    std::cout<<"\n\nLinked list: "<<head->data;
    while(temp)
    {
        std::cout<<" -> "<<temp->data;
        temp = temp->next;
    }
    std::cout<<"\n";
}


void reverseList(Node **head)                                   // iteration method that modifies head pointer inside function
{
    if(*head == NULL)
    {
        std::cout<<"\nEmpty list";
        return;
    }

    Node *cur,*prev,*temp;

    prev = NULL;
    cur = *head;

    while(cur)
    {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    *head = prev;

    //std::cout<<"\n\nLinked list reversed......";
}


Node* reverseList(Node *head)                                   // iteration method without modifying head pointer
{
    if(head == NULL)
    {
        std::cout<<"\nEmpty list";
        return NULL;
    }

    Node *cur,*prev,*temp;

    prev = NULL;
    cur = head;

    while(cur)
    {
        temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    return prev;

    //std::cout<<"\n\nLinked list reversed......";
}



Node* recReverseList(Node *prev,Node *cur)                  // recursive method
{
    Node *root;

    if(cur==NULL)
    {
        return prev;
    }

    root = recReverseList(cur,cur->next);

    cur->next = prev;
    return root;
}



Node* recReverseList(Node *root)
{
    if(!root || !root->next)
        return root;

    Node *ptr = recReverseList(root->next);

    root->next->next = root;
    root->next = NULL;

    return ptr;
}
