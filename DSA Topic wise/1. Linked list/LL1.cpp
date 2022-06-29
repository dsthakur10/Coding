// Given head, the head of a linked list, determine if the linked list has a cycle in it

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
void reverseList(ListNode **head);                  // iterative
ListNode *recReverseList(ListNode *head);           // recursive
void reorderList(ListNode* head);


int main()
{
    bool cycle;
    ListNode *temp1,*temp2;
    ListNode *head1,*head2;

    head1 = NULL;
    head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,20);
    insertListNode(&head1,30);
    insertListNode(&head1,40);
    insertListNode(&head1,50);
    insertListNode(&head1,60);
    insertListNode(&head1,70);
    insertListNode(&head1,80);

    insertListNode(&head2,11);
    insertListNode(&head2,22);
    insertListNode(&head2,33);
    insertListNode(&head2,44);
    insertListNode(&head2,55);
    insertListNode(&head2,66);
/*
    std::cout<<"\nList1 BEFORE:\n";
    displayList(head1);
    reverseList(&head1);
    std::cout<<"List1 AFTER:\n";
    displayList(head1);


    std::cout<<"\nList2 BEFORE:\n";
    displayList(head2);
    head2 = recReverseList(head2);
    std::cout<<"List2 AFTER:\n";
    displayList(head2);
*/

    displayList(head1);
    reorderList(head1);

    std::cout <<"\n\n AFTER REORDER:\n";
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



void reverseList(ListNode **head)
{
    if(*head == NULL)
    {
        std::cout<<"\nEmpty list";
        return;
    }

    ListNode *prev, *cur, *suc;

    prev = NULL;
    cur = *head;

    while(cur != NULL)
    {
        suc = cur->next;
        cur->next = prev;

        prev = cur;
        cur = suc;
    }

    *head = prev;
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

    std::cout<<"fast = "<<fast->val << "\tslow = "<< slow->val;

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
