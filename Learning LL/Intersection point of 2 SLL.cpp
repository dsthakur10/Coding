#include<iostream>

class FNode
{
public:
    int data;
    bool flag;
    FNode *next;

    FNode()
    {
        data = 0;
        flag = false;
        next = NULL;
    }

    FNode(int key)
    {
        data = key;
        flag = false;
        next = NULL;
    }
} ;

void insertNode(FNode **head, int val);
void appendNode(FNode *head,FNode *ptr);
void displayList(FNode *head);

FNode* findIntersection(FNode *head1, FNode *head2);


int main()
{
    FNode *head1 = NULL;
    FNode *head2 = NULL;

    FNode *ptr = new FNode(7777);                   // ptr -> p -> q
    FNode *p = new FNode(8888);
    FNode *q = new FNode(9999);

    ptr->next = p;
    p->next = q;

    insertNode(&head1,5);
    insertNode(&head1,8);
    insertNode(&head1,12);
    insertNode(&head1,20);
    insertNode(&head1,50);
    insertNode(&head1,77);

    insertNode(&head2,100);
    insertNode(&head2,400);
    insertNode(&head2,600);

    appendNode(head1,ptr);
    appendNode(head2,ptr);

    std::cout<<"\n\nLinked list 1: ";
    displayList(head1);
    std::cout<<"\n\nLinked list 2: ";
    displayList(head2);

    ptr = findIntersection(head1,head2);

    std::cout<<"\n\nIntersection point between 2 list = "<<((ptr!=NULL)?ptr->data:NULL);

    return 0;
}


void insertNode(FNode **head, int val)
{
    FNode *ptr = new FNode(val);
    ptr->next = *head;
    *head = ptr;
    std::cout<<"Node "<<val<< " inserted\n";
}


void appendNode(FNode *head,FNode *ptr)
{
    FNode *temp = head;

    while(temp->next)
        temp = temp->next;

    temp->next = ptr;
}


void displayList(FNode *head)
{
    if(!head)
    {
        std::cout<<"\nList Empty";
        return;
    }

    FNode *temp = head->next;

    std::cout<<head->data;
    while(temp)
    {
        std::cout<<" -> "<<temp->data;
        temp = temp->next;
    }
    std::cout<<"\n";
}


FNode* findIntersection(FNode *head1, FNode *head2)
{
    FNode *temp;

    temp = head1;
    while(temp)
    {
        temp->flag = true;
        temp = temp->next;
    }

    temp = head2;

    while(temp)
    {
        if(temp->flag)
            return temp;

        temp = temp->next;
    }

    std::cout<<"No intersection point";
    return NULL;
}
