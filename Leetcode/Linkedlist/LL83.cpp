// Given the head of a SORTED LINKED LIST, delete all duplicates such that each element appears only once.
// Return the linked list sorted as well.

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

ListNode* solution1(ListNode *head);

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,10);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,2);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,1);

    insertListNode(&head2,200);
    insertListNode(&head2,200);
    insertListNode(&head2,200);

    std::cout<<"\n\nLinked List: ";
    displayList(head2);

    head2 = solution1(head2);

    std::cout<<"\n\nUpdated Linked List: ";
    displayList(head2);

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


ListNode* solution1(ListNode *head)
{
    if(!head)
        return NULL;

    ListNode *track = head, *ptr = head->next, *temp;

    while(ptr)
    {
        if(ptr->val != track->val)
        {
            track->next = ptr;
            track = ptr;
            ptr = ptr->next;
        }

        else
        {
            temp = ptr;
            ptr = ptr->next;
            delete temp;
        }
    }

    track->next = NULL;
    return head;
}
