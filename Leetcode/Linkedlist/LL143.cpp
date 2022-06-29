// You are given the head of a singly linked-list. The list can be represented as:

// L0 → L1 → … → Ln - 1 → Ln

// Reorder the list to be on the following form:
// L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …

// NOTE: You may not modify the values in the list's nodes. Only nodes themselves may be changed.


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

ListNode* solution1(ListNode* head);            // 3*O(n) time - 1st loop to calculate length. 2nd loop to reverse list.
                                                // 3rd loop - to merge two n/2 sublists into required order.

ListNode* solution2(ListNode* head);            // 2*O(n) time - 1st loop to get sublists & reverse
                                                // 2nd loop - to merge two n/2 sublists.

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,9);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,5);
    insertListNode(&head1,4);
    insertListNode(&head1,3);
    insertListNode(&head1,2);
    insertListNode(&head1,1);

    insertListNode(&head2,300);
    insertListNode(&head2,200);
    insertListNode(&head2,100);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    head1 = solution1(head1);

    std::cout<<"\n\nReordered Linked List: ";
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



ListNode* reverseList(ListNode *head)                                   // iteration method without modifying head pointer
{
    if(head == NULL)
    {
        return NULL;
    }

    ListNode *cur,*prev,*temp;

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


ListNode* solution1(ListNode* head)
{
    if(!head->next)
        return head;

    int len=0;
    ListNode *temp = head, *first = head, *prev, *p, *q;

    while(temp)
    {
        len++;
        temp = temp->next;
    }

    temp = head;
    len = (len+1)/2;                                // for both even & odd number of nodes

    while(len>0)
    {
        prev = temp;
        temp = temp->next;
        len--;
    }

    prev->next = NULL;                          // 1st sublist contains (n/2 + 1) OR n/2 nodes. 2nd sublist contains n/2 nodes.
    temp = reverseList(temp);                   // prev holds last node in 1st sublist & makes it point to NULL.


    while(temp)
    {
        p = first->next;
        q = temp->next;

        first->next = temp;
        temp->next = p;

        first = p;
        temp = q;
    }

    return head;
}



ListNode* solution2(ListNode* head)
{
    ListNode *temp = head, *first = head, *p, *q;

    while(temp->next && temp->next->next)       // even nodes - temp points to last second node
    {                                           // odd nodes - temp points to last node
        first = first->next;
        temp = temp->next->next;
    }

    if(temp->next)                              // case of even nodes, to point to last node of linked list
        temp = temp->next;

    temp = reverseList(first->next);            // 1st sublist contains (n/2 + 1) OR n/2 nodes. 2nd sublist contains n/2 nodes.
    first->next = NULL;                         // first holds last node in 1st sublist & makes it point to NULL.

    first = head;                               // resetting first node to merge both sublist in given order


    while(temp)
    {
        p = first->next;
        q = temp->next;

        first->next = temp;
        temp->next = p;

        first = p;
        temp = q;
    }

    return head;
}


