// Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.

// k is a positive integer and is less than or equal to the length of the linked list.
// IF THE NUMBER OF NODES IS NOT A MULTIPLE OF K THEN LEFT-OUT NODES, IN THE END, SHOULD REMAIN AS IT IS.

// You may not alter the values in the list's nodes, only nodes themselves may be changed.

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
ListNode* reverseList(ListNode *head);

ListNode* solution1(ListNode* head, int k);                 // iterative solution
ListNode* solution2(ListNode *head, int k);                 // recursive solution - tail recursion
ListNode* solution3(ListNode *head, int k);                 // recursive solution - non-tail recursion

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

    insertListNode(&head2,5);
    insertListNode(&head2,4);
    insertListNode(&head2,3);
    insertListNode(&head2,2);
    insertListNode(&head2,1);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    std::cout<<"Enter number to reverse into group: ";
    std::cin>>k;

    head1 = solution1(head1,k);

    std::cout<<"\n\nRearranged Linked List: ";
    displayList(head1);

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



ListNode* reverseList(ListNode *head)                                   // iteration method without modifying head pointer
{
    if(head == NULL)
    {
        std::cout<<"\nEmpty list";
        return NULL;
    }

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



ListNode* solution1(ListNode* head, int k)
{
    int counter;
    ListNode *temp,*last,*first,*prev;

    temp = head;

    while(temp)
    {
        counter = k;
        first = temp;

        while(counter > 0 && temp)
        {
            prev = temp;
            temp = temp->next;
            counter--;
        }

        if(counter > 0)
        {
            last->next = first;
            break;
        }

        prev->next = NULL;

        prev = reverseList(first);

        if(first == head)
            head = prev;

        else
            last->next = prev;

        last = first;
    }

    return head;
}



ListNode* solution2(ListNode *head, int k)
{
    ListNode *temp,*p,*q;
    temp = head;
    p = NULL;
    q = NULL;

    int counter = 0;

    while(counter<k && temp)
    {
        q = temp->next;
        temp->next = p;
        p = temp;
        temp = q;
        counter++;
    }

    if(counter<k)                                   // for left-out nodes with number < k, keep them unaltered
    {
        temp = p;
        p = NULL;
        q = NULL;

        while(temp)                                 // reverse them all again to get back original order
        {
            q = temp->next;
            temp->next = p;
            p = temp;
            temp = q;
        }
    }


    if(q)                                           // p contains address of first node of REVERSED sublist
        head->next = solution2(q,k);                // q contains address of first node of NEXT sublist
                                                    // head works as mediator to connect 2 sublists
    return p;
}



ListNode* solution3(ListNode *head, int k)
{
    ListNode *cur = head;
    int counter = 0;
    while (cur != nullptr && counter != k)                  // find the k+1 node
    {
        cur = cur->next;
        counter++;
    }

    // if k+1 node is found

    if (counter == k)
    {
        cur = solution3(cur, k);                            // reverse list with k+1 node as head
                                                            // head - head-pointer to direct part,
                                                            // curr - head-pointer to reversed part;

        while (counter-- > 0)                               // reverse current k-group
        {
            ListNode *temp = head->next;
            head->next = cur;
            cur = head;
            head = temp;
        }

        head = cur;
    }

    return head;
}
