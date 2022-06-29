// Given the head of a singly linked list, group all the nodes with odd indexes together followed by the nodes with even indexes,
// and return the reordered list.

// FIRST NODE IS CONSIDERED ODD, AND THE SECOND NODE IS EVEN, AND SO ON.

// NOTE: relative order inside both the even and odd groups should remain as it was in the input.

// You must solve the problem in O(1) extra space complexity and O(n) time complexity


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

ListNode* solution1(ListNode* head);
ListNode* solution2(ListNode* head);
ListNode* solution3(ListNode* head);

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
/*
    insertListNode(&head2,2);
    insertListNode(&head2,5);
    insertListNode(&head2,2);
    insertListNode(&head2,3);
    insertListNode(&head2,4);
    insertListNode(&head2,1);
*/

    insertListNode(&head2,2);
    insertListNode(&head2,1);

    std::cout<<"\n\nLinked List: ";
    displayList(head2);

    head2 = solution3(head2);

    displayList(head2);

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



ListNode* solution1(ListNode* head)
{
    if(!head || !head->next)
        return head;

    int counter = 1;
    ListNode *temp, *prev, *cur, *even;
    prev = NULL;
    cur = head;
    temp = head;

    while(temp->next)
        temp = temp->next;

    even = temp;

    while(cur!=temp)
    {
        if(counter%2 == 0)
        {
            prev->next = cur->next;
            even->next = cur;
            cur->next = NULL;
            even = cur;
            cur = prev->next;
        }

        else
        {
            prev = cur;
            cur = cur->next;
        }

        counter++;
    }

    if(counter%2 == 0)
    {
        prev->next = cur->next?cur->next:cur;
        even->next = cur;
        cur->next = NULL;
    }

    return head;
}


ListNode* solution2(ListNode* head)
{
    if(!head || !head->next)
        return head;


    ListNode *even = head->next, *odd = head;
    ListNode *track = even;

    while(even && even->next)
    {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = track;
    return head;
}


ListNode* solution3(ListNode* head)
{
    if(!head || !head->next)
        return head;

    ListNode *evenSentinel = new ListNode();
    ListNode *oddSentinel = new ListNode();

    ListNode *even = evenSentinel, *odd = oddSentinel;

    while(head)
    {
        odd->next = head;
        even->next = head->next;

        odd = odd->next;
        even = even->next;

        head = even?even->next:NULL;                        // in case of odd #nodes. even->next = NULL->next which may cause error.

        //odd->next = NULL;
        //even->next = NULL;
    }

    odd->next = evenSentinel->next;
    return oddSentinel->next;

}
