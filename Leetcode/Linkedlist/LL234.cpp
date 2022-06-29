// Given the head of a singly linked list, return true if it is a palindrome.

#include<iostream>
#include<stack>


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
bool isPalindrome(ListNode *root);

bool solution1(ListNode* head);                     // reverse the 2nd half of linked-list & then check 2 sublists are equal

bool solution2(ListNode* head);                     // stack - slower than solution1

bool solution3(ListNode* head);                     // recursive solution

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,8);
    insertListNode(&head1,2);
    insertListNode(&head1,1);
    insertListNode(&head1,6);
    insertListNode(&head1,1);
    insertListNode(&head1,2);
    insertListNode(&head1,8);
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

    bool flag = solution3(head1);

    if(flag)
        std::cout<<"\n\nPALINDROME";

    else
        std::cout<<"\nFUCK OFF";

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

    //std::cout<<"\n\nLinked list reversed......";
}


bool solution1(ListNode *head)
{
    if(!head->next)
        return true;

    ListNode *slow = head, *fast = head;

    while(fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    std::cout<<"slow = "<< slow->val << " fast = "<< fast->val;
    slow = slow->next;

    slow = reverseList(slow);

    while(slow)
    {
        if(head->val != slow->val)
            return false;

        head = head->next;
        slow = slow->next;
    }

    return true;
}


bool solution2(ListNode* head)
{
    if(!head->next)
        return true;

    ListNode *slow = head, *fast = head;

    while(fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    std::cout<<"slow = "<< slow->val << " fast = "<< fast->val;
    slow = slow->next;

    std::stack<int> mystack;

    while(slow)
    {
        mystack.push(slow->val);
        slow = slow->next;
    }


    while(!mystack.empty())
    {
        if(head->val != mystack.top())
            return false;

        mystack.pop();
        head = head->next;
    }

    return true;
}



bool solution3(ListNode* head)
{
    //temp = head;
    return isPalindrome(head);
}



bool isPalindrome(ListNode *root)
{
    static ListNode *temp = root;

    if(!root)
        return true;

    bool ans, isEqual;

    ans = isPalindrome(root->next);

    isEqual = (temp->val == root->val)?true:false;

    temp = temp->next;

    return (ans && isEqual);
}
