// You are given two non-empty linked lists representing two non-negative integers.
// The DIGITS ARE STORED IN REVERSE ORDER, and each of their ListNodes contains a single digit.
// Add the two numbers and return the sum as a linked list.

// NOTE: You may assume the two numbers do not contain any leading zero, except the number 0 itself.


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

ListNode* solution1(ListNode *head1, ListNode *head2);
ListNode* solution2(ListNode *head1, ListNode *head2);


int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,9);
    insertListNode(&head1,5);
    insertListNode(&head1,7);

    insertListNode(&head2,4);
    insertListNode(&head2,8);
    insertListNode(&head2,9);

    std::cout<<"\n\nLinked List-1: ";
    displayList(head1);
    std::cout<<"\n\nLinked List-2: ";
    displayList(head2);

    ListNode *temp = solution1(head1,head2);

    std::cout<<"\n\nADDED Linked List: ";
    displayList(temp);

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


ListNode* solution1(ListNode *head1, ListNode *head2)
{
    ListNode *p1, *p2, *cur, *res;
    int sum, carry = 0;

    p1 = head1;
    p2 = head2;
    res = NULL;

    while(p1 || p2)
    {
        sum = carry + (p1?p1->val:0) + (p2?p2->val:0);

        carry = (sum>=10)?1:0;
        sum = sum%10;

        if(res == NULL)
        {
            cur = new ListNode(sum);
            res = cur;
        }

        else
        {
            cur->next = new ListNode(sum);
            cur = cur->next;
        }

        if(p1)
            p1 = p1->next;

        if(p2)
            p2 = p2->next;
    }

    if(carry > 0)
        cur->next = new ListNode(carry);

    return res;
}


ListNode* solution2(ListNode *head1, ListNode *head2)
{
    ListNode *p1, *p2, *temp, *cur, *res;
    int sum, carry = 0;

    p1 = head1;
    p2 = head2;
    res = NULL;

    while(p1 && p2)
    {
        sum = carry + p1->val + p2->val;

        carry = (sum>=10)?1:0;
        sum = sum%10;

        //temp = new ListNode(sum);

        if(res == NULL)
        {
            res = temp;
            cur = res;
        }

        else
        {
            cur->next = temp;
            cur = cur->next;
        }

        p1 = p1->next;
        p2 = p2->next;
    }

    while(p1)
    {
        sum = carry + p1->val;
        carry = (sum>=10)?1:0;
        sum = sum%10;

        temp = new ListNode(sum);

        cur->next = temp;
        cur = cur->next;

        p1 = p1->next;
    }

    while(p2)
    {
        sum = carry + p2->val;
        carry = (sum>=10)?1:0;
        sum = sum%10;

        temp = new ListNode(sum);

        cur->next = temp;
        cur = cur->next;

        p2 = p2->next;
    }

    if(carry > 0)
        cur->next = new ListNode(carry);

    return res;
}
