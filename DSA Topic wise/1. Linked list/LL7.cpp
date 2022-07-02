/*
    Given a linked list, REVERSE the nodes of a linked list 'k' AT A TIME and return its modified list.

    k is a positive integer and is less than or equal to the length of the linked list.
    If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is.

    You may not alter the values in the list's nodes, only nodes themselves may be changed.
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

ListNode* recReverseList(ListNode *head);
ListNode* reverseList(ListNode *head);
ListNode* reverseKGroup(ListNode *head, int k);


int main()
{
    int k;
    ListNode *temp1,*temp2, *start;
    ListNode *head1,*head2;

    head1 = NULL;
    head2 = NULL;

/*
    std::cout <<"\n---------------Linked List 1---------------\n";
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,5);
    insertListNode(&head1,4);
    insertListNode(&head1,3);
    insertListNode(&head1,2);
    insertListNode(&head1,1);
*/

    std::cout <<"\n---------------Linked List 2---------------\n";
    for(int i=20; i>0; i--)
        insertListNode(&head2,i);

    displayList(head2);

    std::cout<<"Enter size of group:\n";
    std::cin >> k;
    head2 = reverseKGroup(head2,k);

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



ListNode* recReverseList(ListNode *head)
{
    if(!head || !head->next)
        return head;

    ListNode *cur;
    cur = recReverseList(head->next);

    head->next->next = head;
    head->next = NULL;

    return cur;
}


ListNode* reverseList(ListNode *head)
{
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




ListNode* reverseKGroup(ListNode *head, int k)
{
    ListNode *last, *start, *temp, *prev;
    start = head;
    last = head;
    prev = NULL;

    int counter;

    while(last)
    {
        counter = 1;
        while(counter < k && last)
        {
            last = last->next;
            counter++;
        }

        if(counter<k || !last)
            break;

        temp = last->next;                      // to hold 1st element of next sublist
        last->next = NULL;

        last = start;
        start = recReverseList(start);

        displayList(start);

        std::cout<<"\nlast = "<<last->val;
        std::cout<<"\nfirst = "<<start->val;
        last->next = temp;

        if(last == head)
            head = start;

        std::cout<<"\nHead = "<<head->val<<"\n";

        if(prev)
            prev->next = start;

        prev = last;
        start = temp;
        last = temp;

        std::cout<<"\n\n";
    }

    std::cout<<"\nHead = "<<head->val<<"\n";

    return head;
}



// Recursive solution

ListNode* reverseKGroup(ListNode* head, int k) {

    ListNode *temp = head, *first, *last;
    int counter;

    last = NULL;
    first = temp;
    counter = 0;

    while(temp && counter < k)
    {
        last = temp;
        temp = temp->next;
        counter++;
    }

    if(counter == k)
    {
        last->next = NULL;
        last = first;
        first = reverse(first);
        last->next = reverseKGroup(temp, k);
    }

    return first;

}


ListNode* reverse(ListNode* head)
{
    if(!head || !head->next)
        return head;

    ListNode *temp, *cur = NULL, *prev = NULL;
    temp = head;

    while(temp)
    {
        cur = temp;
        temp = temp->next;

        cur->next = prev;
        prev = cur;
    }

    head = cur;
    return head;
}

