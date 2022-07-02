// Given the head of a SORTED linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.


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
ListNode* deleteDuplicates(ListNode* head);

int main()
{
    ListNode *temp1,*temp2, *start;
    ListNode *head1,*head2;

    head1 = NULL;
    head2 = NULL;


    std::cout <<"\n---------------Linked List 1---------------\n";
    insertListNode(&head1,10);
    insertListNode(&head1,10);
    insertListNode(&head1,30);
    insertListNode(&head1,40);
    insertListNode(&head1,40);
    insertListNode(&head1,40);
    insertListNode(&head1,70);
    insertListNode(&head1,70);

    head1 = deleteDuplicates(head1);

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



ListNode* deleteDuplicates(ListNode* head)
{
    if(!head || !head->next)
        return head;

    ListNode *temp = head;
    ListNode *cur = head->next;

    while(cur)
    {
        if(temp->val == cur->val)
        {
            temp->next = cur->next;
            //free(cur->next);
            //free(cur);
            cur->next = NULL;
            cur = temp->next;
        }

        else
        {
            temp = temp->next;
            cur = cur->next;
        }
    }

    return head;
}




ListNode* deleteDuplicates(ListNode* head) {

    if(!head || !head->next)
        return head;

    ListNode *temp = head, *cur = head, *last;


    while(temp)
    {
        while(temp && temp->next && temp->val == temp->next->val)
            temp = temp->next;

        cur->next = temp->next;
        temp = cur->next;
        cur = temp;
    }

    return head;
}
