// Given the head of a linked list, return the list after sorting it in ascending order.

// Time = O(nlogn) Space = O(1) --> merge sort on LL



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

ListNode* mergeSort(ListNode *head);
ListNode* mergeList(ListNode *first, ListNode *second);


int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;
    ListNode *head3 = NULL;

    insertListNode(&head3,-5);
    insertListNode(&head3,0);
    insertListNode(&head3,12);
    insertListNode(&head3,100);

    insertListNode(&head1,20);
    insertListNode(&head1,0);
    insertListNode(&head1,4);
    insertListNode(&head1,3);
    insertListNode(&head1,88);
    insertListNode(&head1,-1);
    insertListNode(&head1,5);
    insertListNode(&head1,-1);
    insertListNode(&head1,-14);
    insertListNode(&head1,-18);


    insertListNode(&head2,-5);
    insertListNode(&head2,0);
    insertListNode(&head2,3);
/*    insertListNode(&head2,2);
    insertListNode(&head2,100);
*/

    std::cout<<"\n\nLinked List: ";
    displayList(head2);

    head2 = mergeSort(head2);

    std::cout << "\n\n Sorted list: ";
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




ListNode* mergeSort(ListNode *head)
{
    if(!head->next)
        return head;

    ListNode *slow, *fast, *pre;

    slow = head;
    fast = head;

    while(fast && fast->next)
    {
        pre = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    pre->next = NULL;                               // disconnecting 2 lists.

    ListNode* first = mergeSort(head);
    ListNode* second = mergeSort(slow);

    head = mergeList(first, second);
    return head;

}


ListNode* mergeList(ListNode *first, ListNode *second)
{
    ListNode *head, *temp;

    if(!first)
        return second;

    if(!second)
        return first;

    if(first->val <= second->val)
    {
        head = first;
        first = first->next;
        head->next = NULL;
    }

    else
    {
        head = second;
        second = second->next;
        head->next = NULL;
    }

    temp = head;

    while(first && second)
    {
        if(first->val <= second->val)
        {
            temp->next = first;
            first = first->next;
            temp = temp->next;
            temp->next = NULL;
        }

        else
        {
            temp->next = second;
            second = second->next;
            temp = temp->next;
            temp->next = NULL;
        }
    }

    if(first)
        temp->next = first;

    if(second)
        temp->next = second;

    return head;
}


