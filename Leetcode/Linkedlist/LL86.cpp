// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.

// You should preserve the original relative order of the nodes in each of the two partitions.


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

ListNode* solution1(ListNode *head, int x);         // traverse LL & append the node to the last node, if node->val >= x

ListNode* solution2(ListNode *head, int x);         // create 2 sentinel nodes before & after to keep track of ">= x" & < x nodes & join them

int main()
{
    int x;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,1);
    insertListNode(&head1,1);
    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,2);
    insertListNode(&head1,6);
    insertListNode(&head1,10);
/*
    insertListNode(&head2,2);
    insertListNode(&head2,5);
    insertListNode(&head2,2);
    insertListNode(&head2,3);
    insertListNode(&head2,4);
    insertListNode(&head2,1);
*/

    insertListNode(&head2,2);
    insertListNode(&head2,1);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    std::cout<<"\nEnter number for partition: ";
    std::cin>>x;

    head1 = solution2(head1,x);

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



ListNode* solution1(ListNode *head, int x)
{
    if(!head)
        return NULL;

    if(!head->next)
        return head;

    ListNode *temp, *prev, *ptr, *last;
    ptr = head;

    while(ptr->next)
        ptr = ptr->next;

    last = ptr;                                     // last pointer - to track last ">= x node" appended. ptr pointer - to limit the search to end of list
    temp = head;                                    // temp & prev pointers - to traverse & link - unlink nodes

    while(temp!=ptr)
    {
        if(temp->val >= x)
        {
            if(temp == head)
            {
                head = head->next;
                last->next = temp;
                temp->next = NULL;
                last = temp;
                temp = head;
            }

            else
            {
                prev->next = temp->next;
                last->next = temp;
                temp->next = NULL;
                last = temp;
                temp = prev->next;
            }
        }

        else
        {
            prev = temp;
            temp = temp->next;
        }
    }

    if(temp->val >= x)
    {
        if(temp == head)
        {
            head = head->next;
            last->next = temp;
            temp->next = NULL;
            last = temp;
        }

        else
        {
            prev->next = ((temp->next)?temp->next:temp);            // what if ptr == last ?
            last->next = temp;
            temp->next = NULL;
            last = temp;
        }
    }

    return head;
}


ListNode* solution2(ListNode *head, int x)
{
    if(!head)
        return NULL;

    if(!head->next)
        return head;

    ListNode *sentinelBefore = new ListNode();
    ListNode *sentinelAfter = new ListNode();

    ListNode *temp,*before = sentinelBefore,*after = sentinelAfter;
    temp = head;

    while(temp)
    {
        if(temp->val < x)
        {
            before->next = temp;
            before = before->next;
            temp = temp->next;
            before->next = NULL;
        }

        else
        {
            after->next = temp;
            after = after->next;
            temp = temp->next;
            after->next = NULL;
        }

    }

    before->next = sentinelAfter->next;

    return sentinelBefore->next;
}
