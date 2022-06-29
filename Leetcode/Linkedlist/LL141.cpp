// Given head, the head of a linked list, determine if the linked list has a cycle in it.

// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
// Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

// Return true if there is a cycle in the linked list. Otherwise, return false.


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
void displayCicularList(ListNode *head);

bool solution1(ListNode *head);         //

bool solution2(ListNode *head);         //

int main()
{
    int x;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head2,2);
    insertListNode(&head2,5);
    insertListNode(&head2,2);
    insertListNode(&head2,3);
    insertListNode(&head2,4);
    insertListNode(&head2,1);

    ListNode *ptr = new ListNode(100);

    ListNode *temp = head2;
    while(temp->next)
        temp = temp->next;

    temp->next = ptr;
    ptr->next = head2;

    bool flag = solution1(head2);
    std::cout<<"Cycle detected = "<<std::boolalpha<<flag;

    if(flag)
    {
        std::cout<<"\n\nCircular Linked List: ";
        displayCicularList(head2);
    }

    else
    {
        std::cout<<"\n\nLinked List: ";
        displayList(head2);
    }
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


void displayCicularList(ListNode *head)
{
    if(!head)
    {
        std::cout<<"\nList Empty";
        return;
    }

    ListNode *temp = head->next;

    std::cout<<head->val;
    while(temp->next!=head)
    {
        std::cout<<" -> "<<temp->val;
        temp = temp->next;
    }
    std::cout<<"\n";
}



bool solution1(ListNode *head)
{
    ListNode *slow, *fast;
    slow = head;
    fast = head;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            return true;
    }

    return false;

}

