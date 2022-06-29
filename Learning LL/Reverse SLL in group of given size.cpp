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


void insertNode(Node **head, int val);
void displayList(Node *head);
Node* reverseList(Node *head);

void reverseInGroup(Node **head, int k);
Node* recReverseInGroup(Node *head, int k);


int main()
{
    int k;
    Node *head = NULL;

    insertNode(&head,5);
    insertNode(&head,8);
    insertNode(&head,12);
    insertNode(&head,20);
    insertNode(&head,50);
    insertNode(&head,77);
    insertNode(&head,100);
    insertNode(&head,200);

    displayList(head);

    std::cout<<"\n\nEnter size of group:\n";
    std::cin>>k;
    std::cout<<"\n\n--------Reversed linked list in size "<<k<<"--------\n\n";

    //reverseInGroup(&head,k);

    head = recReverseInGroup(head,k);
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
}


void reverseInGroup(Node **head, int k)
{
    int counter;
    Node *temp,*last,*first,*prev;

    last = *head;
    prev = NULL;

    while(last)
    {
        first = last;
        counter = 1;

        while(counter < k && last->next)
        {
            last = last->next;
            counter++;
        }

        temp = last->next;
        last->next = NULL;

        last = reverseList(first);

        first->next = temp;
        if(prev)
            prev->next = last;

        if(first == *head)
            *head = last;

        last = temp;
        prev = first;
    }
}



Node* recReverseInGroup(Node *head, int k)
{
    Node *temp,*p,*q;
    temp = head;
    p = NULL;
    q = NULL;

    int counter = 0;

    while(counter<k && temp)
    {
        q = temp->next;
        temp->next = p;
        p = temp;
        temp = q;
        counter++;
    }

    if(q)
        head->next = recReverseInGroup(q,k);

    return p;
}
