// Given a linked list, swap every two adjacent nodes and return its head.
// You must solve the problem WITHOUT MODIFYING THE VALUES in the list's nodes (i.e., only nodes themselves may be changed.)


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

ListNode* solution1(ListNode *head);                    // Iterative method
ListNode* solution2(ListNode *root);                    // Recursive method


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
    //insertListNode(&head1,9999);

    insertListNode(&head2,100);
    //insertListNode(&head2,200);

    std::cout<<"\n\nLinked List: ";
    displayList(head2);

    head2 = solution2(head2);

    std::cout<<"\n\nSwapped Linked List: ";
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


ListNode* solution1(ListNode *head)
{
    ListNode *ptr = head;
    ListNode *temp,*prev,*last;

    while(ptr && ptr->next)
    {
        prev = ptr;
        temp = ptr->next;
        ptr = ptr->next->next;

        temp->next = prev;
        prev->next = ptr;

        if(prev == head)
            head = temp;

        else
            last->next = temp;

        last = prev;

    }

    return head;
}



ListNode* solution2(ListNode *root)
{
    if(!root)
        return NULL;

    if(!root->next)
        return root;

    ListNode *ptr = root->next;

    root->next = solution2(root->next->next);

    ptr->next = root;

    return ptr;
}
