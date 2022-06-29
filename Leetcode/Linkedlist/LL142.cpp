// Given a linked list, return the node where the cycle begins. If there is no cycle, return null.

// There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the next pointer.
// Internally, pos is used to denote the index of the node that tail's next pointer is connected to. Note that pos is not passed as a parameter.

// NOTE: You should not modify the linked list.


#include<iostream>
#include<set>

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

ListNode* solution1(ListNode *head);            // O(n) time + O(n) space - use set to store addresses of nodes

ListNode* solution2(ListNode *head);            // O(n) time - use triple pointers

int main()
{
    int x;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head2,8);
    insertListNode(&head2,7);
    insertListNode(&head2,6);
    insertListNode(&head2,5);
    insertListNode(&head2,4);
    insertListNode(&head2,3);
    insertListNode(&head2,2);
    insertListNode(&head2,1);

    ListNode *ptr = head2->next->next;
    ListNode *temp = head2;

    std::cout<<"\n\nptr = "<<ptr->val;
    while(temp->next)
        temp = temp->next;

    temp->next = ptr;
    std::cout<<"\n\ntemp = "<<temp->val;
    std::cout<<"\n\ntemp->next = "<<temp->next->val;
    std::cout<<"\n\nhead = "<<head2->val;

    ptr = solution2(head2);

    if(ptr)
        std::cout<<"\n\nStart of cycle = "<<ptr->val;

    else
        std::cout<<"\n\nNO CYCLE";

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



ListNode* solution1(ListNode *head)
{
    std::set<ListNode *> mynode;                                            // storing user defined data-type in set
    std::pair<std::set<ListNode *>::iterator, bool> ret;

    while(head)
    {
        ret = mynode.insert(head);

        if(ret.second == false)
            return head;

        head = head->next;
    }

    return NULL;

}


ListNode* solution2(ListNode *head)
{
    ListNode *fast,*slow;

    fast = head; slow = head;

    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            break;
    }

    std::cout<<"\n\nfast = "<<fast->val<<" slow = "<<slow->val;

    if(!fast || !fast->next)
        return NULL;

    while(head!=slow)
    {
        head = head->next;
        slow = slow->next;
    }

    return slow;

}
