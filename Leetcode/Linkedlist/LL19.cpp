// -------------------Remove Nth Node From End of List------------------------


// Given the head of a linked list, remove the Nth Node from the end of the list and return its head.

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

ListNode* solution1(ListNode *head, int n);             // 2*O(n) solution - calculate length of LL. N from END =
                                                        // length-N+1 from front

ListNode* solution2(ListNode *head, int n);             // O(n) solution - 2 pointers


int main()
{
    int n;
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

    std::cout<<"\nEnter number to delete the node from the end:";
    std::cin>>n;
    head1 = solution2(head1,n);

    std::cout<<"\n\nUpdated Linked List: ";
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


ListNode* solution1(ListNode *head, int n)
{
    int len=0;
    ListNode *prev,*temp = head;

    while(temp)
    {
        len++;
        temp = temp->next;
    }

    std::cout<<"\nSize = "<<len;
    len = len - n;

    if(len<0)
        return NULL;

    else if(len == 0)
    {
        temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    else
    {
        temp = head;
        while(len>0)
        {
            prev = temp;
            temp = temp->next;
            len--;
        }

        prev->next = temp->next;
        delete temp;
        return head;
    }
}


ListNode* solution2(ListNode *head, int n)
{
    if(!head->next)
    {
        delete head;
        return NULL;
    }

    ListNode *first, *last, *prev;
    first = head;
    last = head;

    while(n>0)
    {
        last = last->next;
        n--;
    }

    while(last)
    {
        prev = first;
        first = first->next;
        last = last->next;
    }

    if(first == head)
    {
        head = head->next;
        delete first;
    }

    else
    {
        prev->next = first->next;
        delete first;
    }

    return head;
}
