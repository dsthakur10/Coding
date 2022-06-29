// Given a linked list, swap every two adjacent nodes and return its head.
// You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)


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

ListNode* swapPairs(ListNode *head);
ListNode* swapPairs2(ListNode *head);

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
    for(int i=11; i>0; i--)
        insertListNode(&head2,i);

    displayList(head2);

    head2 = swapPairs2(head2);

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



ListNode* swapPairs(ListNode *head)
{
    ListNode *prev, *cur, *temp1, *temp2;

    if(!head || !head->next)
        return head;

    prev = head;
    cur = head->next;
    temp1 = NULL;
    temp2 = NULL;

    while(cur)
    {
        temp2 = cur->next;
        cur->next = prev;
        prev->next = temp2;

        if(temp1)
            temp1->next = cur;

        if(prev == head)
            head = cur;
/*
        temp1 = prev;                           // runtime error in leetcode
        prev = temp2;
        cur = temp2->next;
*/


        if(temp2)
        {
            temp1 = prev;
            prev = temp2;
            cur = temp2->next;
        }

        else
            cur = NULL;
    }

    return head;
}



ListNode* swapPairs2(ListNode *head)
{
    if(!head || !head->next)
        return head;

    ListNode *temp;
    temp = head->next;
    head->next = swapPairs2(head->next->next);
    temp->next = head;

    return temp;
}
