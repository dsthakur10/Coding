// Given the head of a linked list, rotate the list to the right by K places.

// NOTE: If K > length of linked list, use modulo arithmatic


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

ListNode* solution1(ListNode *head, int k);         // Count length. Find modulo of K. Use it to rotate.
                                                    // Cannot use double pointer method as K<=10^9 & we need to count length of
                                                    // linked list anyway.
int main()
{
    int k;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,160);
    insertListNode(&head1,84);
    insertListNode(&head1,9);
    insertListNode(&head1,55);
    insertListNode(&head1,70);
    insertListNode(&head1,47);
    insertListNode(&head1,800);
    insertListNode(&head1,9999);

    insertListNode(&head2,100);
    insertListNode(&head2,200);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    std::cout<<"\nEnter number to rotate the linked list:";
    std::cin>>k;
    head1 = solution1(head1,k);

    std::cout<<"\n\nRotated Linked List: ";
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


ListNode* solution1(ListNode *head, int k)
{
    if(!head)
        return NULL;

    if(k == 0)
        return head;

    int len = 0;
    ListNode *ptr = head, *temp;

    while(ptr)
    {
        ptr = ptr->next;
        len++;
    }

    //std::cout<<"length = "<<len;

    ptr = head;
    k = k%len;                              // modulo arithmatic
    len = len - k;

    while(len>1)
    {
        ptr = ptr->next;
        len--;
    }

    temp = ptr;

    while(temp->next)
        temp = temp->next;

    temp->next = head;
    head = ptr->next;
    ptr->next = NULL;

    return head;
}

