// Given the heads of two singly linked-lists headA and headB, return the node at which the two lists intersect.
// If the two linked lists have no intersection at all, return null.

// It is guaranteed that there are no cycles anywhere in the entire linked structure.

// NOTE: linked lists must retain their original structure after the function returns.


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
void appendNode(ListNode *head,ListNode *ptr);

ListNode* solution1(ListNode *headA, ListNode *headB);
ListNode* solution2(ListNode *headA, ListNode *headB);

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    ListNode *ptr = new ListNode(7777);                   // ptr -> p -> q
    ListNode *p = new ListNode(8888);
    ListNode *q = new ListNode(9999);

    ptr->next = p;
    p->next = q;

    insertListNode(&head1,8);
    insertListNode(&head1,12);
    insertListNode(&head1,20);
    insertListNode(&head1,50);
    insertListNode(&head1,77);

    insertListNode(&head2,100);
    insertListNode(&head2,400);
    insertListNode(&head2,600);

    appendNode(head1,ptr);
    appendNode(head2,ptr);

    std::cout<<"\n\nLinked list 1: ";
    displayList(head1);
    std::cout<<"\n\nLinked list 2: ";
    displayList(head2);

    ptr = solution2(head1,head2);

    std::cout<<"\n\nIntersection point between 2 list = "<<((ptr!=NULL)?ptr->val:NULL);

    return 0;
}



void insertListNode(ListNode **head, int val)
{
    ListNode *ptr = new ListNode(val);
    ptr->next = *head;
    *head = ptr;
    std::cout<<"ListNode "<<val<< " inserted\n";
}


void appendNode(ListNode *head,ListNode *ptr)
{
    ListNode *temp = head;

    while(temp->next)
        temp = temp->next;

    temp->next = ptr;
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




ListNode* solution1(ListNode *headA, ListNode *headB)
{
    if(!headA || !headB)
        return NULL;

    int lenA=0, lenB=0, diff;
    ListNode *temp = headA;

    while(temp)
    {
        lenA++;
        temp = temp->next;
    }
    std::cout<<"\nLength of A = "<<lenA;

    temp = headB;
    while(temp)
    {
        lenB++;
        temp = temp->next;
    }
    std::cout<<"\nLength of B = "<<lenB;

    if(lenA > lenB)
    {
        diff = lenA - lenB;

        while(diff>0)
        {
            headA = headA->next;
            diff--;
        }
    }

    else
    {
        diff = lenB - lenA;

        while(diff>0)
        {
            headB = headB->next;
            diff--;
        }
    }

    while(headA)
    {
        if(headA == headB)
            return headA;

        headA = headA->next;
        headB = headB->next;
    }

    return NULL;
}



ListNode* solution2(ListNode *headA, ListNode *headB)
{
    // We can use two iterations to do that. In the first iteration, we will reset the pointer of one linkedlist to the head of another linkedlist after
    // it reaches the tail node. In the second iteration, we will move two pointers until they points to the same node.
    // Our operations in first iteration will help us counteract the difference. So if two linkedlist intersects, the meeting point in second iteration
    // must be the intersection point. If the two linked lists have no intersection at all,
    // then the meeting pointer in second iteration must be the tail node of both lists, which is null

    if(!headA || !headB)
        return NULL;

    ListNode *A = headA;
    ListNode *B = headB;

    while(A!=B)
    {
        A = (A==NULL?headB:A->next);
        B = (B==NULL?headA:B->next);
    }

    return A;
}
