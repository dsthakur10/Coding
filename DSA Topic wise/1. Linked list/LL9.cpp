// Given a list, rotate the list to the right by k places, where k is non-negative

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

ListNode* rotateRight(ListNode* head, int k);



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
    for(int i=1; i>0; i--)
        insertListNode(&head2,i);

    displayList(head2);

    std::cout<< "Enter the rotating point:\n";
    std::cin >> k;
    head2 = rotateRight(head2,k);

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



ListNode* rotateRight(ListNode* head, int k)
{
    if(k == 0)
        return head;

    int len = 0, counter;

    ListNode *temp, *first;

    temp = head;
    while(temp)
    {
        temp = temp->next;
        len++;
    }

    //std::cout<<"Length of list = "<< len << "\n";
    k = k % len;
    counter = len - k;

    if(k == 0)
        return head;

    temp = head;
    while(counter > 1)
    {
        temp = temp->next;
        counter--;
    }

    first = temp->next;
    temp->next = NULL;

    temp = first;
    while(temp->next)
        temp = temp->next;

    temp->next = head;

    head = first;
    return head;
}
