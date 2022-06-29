// Given the head of a linked list, return the node where the cycle begins. If there is no cycle, return null.

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
ListNode* detectCycle(ListNode *head);


int main()
{
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

    std::cout <<"\n---------------Linked List 2---------------\n";
    insertListNode(&head2,11);
    insertListNode(&head2,22);
    insertListNode(&head2,33);
    insertListNode(&head2,44);
    insertListNode(&head2,55);
    insertListNode(&head2,66);


    temp1 = head1;
    while(temp1->next != NULL)
        temp1 = temp1->next;

    temp2 = head1;
    while(temp2->val != 30)
        temp2 = temp2->next;

    temp1->next = temp2;

    start = detectCycle(head1);

    if(start)
        std::cout<<"\nStarting Node = " << start->val;
    else
        std::cout<<"\nLinked list DO NOT HAVE cycle";


    start = detectCycle(head2);

    if(start)
        std::cout<<"\nStarting Node = " << start->val;
    else
        std::cout<<"\nLinked list DO NOT HAVE cycle";

    return 0;
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


ListNode* detectCycle(ListNode *head)
{
    ListNode* temp, *slow, *fast;
    temp = head;
    slow = head;
    fast = head;

    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;

        if(slow == fast)
            break;
    }

    if(slow != fast)
        return NULL;

    while(slow != temp)
    {
        slow = slow->next;
        temp = temp->next;
    }

    return temp;
}
