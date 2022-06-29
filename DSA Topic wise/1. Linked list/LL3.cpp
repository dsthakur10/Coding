/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.

*/


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
ListNode *recReverseList(ListNode *head);
void reorderList(ListNode* head);


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

    std::cout<<"\n\nBEFORE reordering: ";
    displayList(head1);

    reorderList(head1);

    std::cout<<"\n\nAFTER reordering: ";
    displayList(head1);

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



ListNode *recReverseList(ListNode *head)
{
    if(!head || !head->next)
        return head;

    ListNode *cur;

    cur = recReverseList(head->next);
    head->next->next = head;
    head->next = NULL;

    return cur;
}



void reorderList(ListNode* head)
{
    ListNode *fast, *slow;
    fast = head;
    slow = head;

    while(fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    //std::cout<<"fast = "<<fast->val << "\tslow = "<< slow->val;

    fast = slow->next;
    slow->next = NULL;

    fast = recReverseList(fast);

    ListNode *temp, *suc1, *suc2;
    temp = head;

    while(fast != NULL)
    {
        suc1 = temp->next;
        suc2 = fast->next;

        temp->next = fast;
        fast->next = suc1;

        temp = suc1;
        fast = suc2;
    }
}

