// Given the head of a SORTED LINKED LIST,
// delete all nodes that have duplicate numbers, leaving ONLY DISTINCT NUMBERS from the original list.
// Return the linked list sorted as well.


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

ListNode* solution1(ListNode *head);

ListNode* solution2(ListNode *head);                        // sentinel node concept

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,15);
    insertListNode(&head1,10);
    insertListNode(&head1,10);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,2);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,1);


/*
    insertListNode(&head1,10);
    insertListNode(&head1,10);
    insertListNode(&head1,7);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,4);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,0);
    //insertListNode(&head1,0);
*/
    insertListNode(&head2,200);
    insertListNode(&head2,200);
    insertListNode(&head2,100);
    insertListNode(&head2,100);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    head1 = solution2(head1);

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


ListNode* solution1(ListNode *head)
{
    if(!head)
        return NULL;

    ListNode *ptr, *last, *temp;                            // last pointer is used to track the predecessor of duplicate sublist
    ptr = head;                                             // i.e., the last node before the sublist of duplicates
    last = head;

    while(ptr && ptr->next)
    {
        temp = ptr->next;

        while(temp && (temp->val == ptr->val))                   // temp maybe equal to NULL
            temp = temp->next;

        if(temp != ptr->next)
        {
            if(ptr == head)
            {
                head = temp;
                last = head;
            }

            else
                last->next = temp;
        }

        else
            last = ptr;

        ptr = temp;
    }

    return head;
}



ListNode* solution2(ListNode *head)
{
    // Sentinel node is used for the most challenging task, i.e. deleting head node in case it is duplicate.

    // Sentinel node works as pseudo-head with zero value to ensure that the situation "delete the list head"
    // could never happen, and all nodes to delete are "inside" the list.

    if(!head)
        return NULL;

    ListNode *sentinel = new ListNode();
    sentinel->next = head;

    ListNode *last, *ptr;
    last = sentinel;                            // last node is used to keep track of predecessor of unique nodes.

    while(head && head->next)
    {
        if(head->val == head->next->val)        // Here head->next is not checked because already the check is done in outer loop
        {
            while(head->next && (head->val == head->next->val))         // head->next is checked because while traveling till end
                head = head->next;                                      // we may end up at last node in LL.

            last->next = head->next;
        }

        else
            last = head;

        head = head->next;
    }

    return sentinel->next;
}
