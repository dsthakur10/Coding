// Given the head of a linked list, remove the nth node from the end of the list and return its head.


#include<iostream>


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
ListNode* removeNthFromEnd(ListNode* head, int n);


int main()
{
    int n;
    ListNode *temp1,*temp2, *start;
    ListNode *head1,*head2;

    head1 = NULL;
    head2 = NULL;


    std::cout <<"\n---------------Linked List 1---------------\n";
    insertListNode(&head1,10);
    insertListNode(&head1,20);
    insertListNode(&head1,30);
    insertListNode(&head1,40);
    insertListNode(&head1,50);
    insertListNode(&head1,60);
    insertListNode(&head1,70);
    insertListNode(&head1,80);

    displayList(head1);

    std::cout<<"\nEnter the node from the end you want to delete:\n";
    std::cin >> n;

    std::cout<<"\nAfter removing " << n << "th node from END:\n";
    head1 = removeNthFromEnd(head1,n);
    displayList(head1);

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



ListNode* removeNthFromEnd(ListNode* head, int n)
{

    ListNode *start, *end, *temp;
    start = NULL;
    end = head;
    temp = NULL;

    int counter = 1;

    while(counter < n)
    {
        end = end->next;
        counter++;
    }

    while(end->next)
    {
        if(!start)
            start = head;
        else
            start = start->next;
        end = end->next;
    }

    if(!start)
    {
        temp = head;
        head = head->next;
    }

    else
    {
        temp = start->next;
        start->next = temp->next;
    }

    free(temp);
    //temp->next = NULL;
    return head;
}

