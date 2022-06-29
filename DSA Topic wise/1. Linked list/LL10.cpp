// Given the head of a singly linked list, return true if it is a palindrome.

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

bool isPalindrome(ListNode* head);
bool isPalindrome2(ListNode* head);
//bool check(ListNode* root);


int main()
{

    bool flag;
    ListNode *head1,*head2;

    head1 = NULL;
    head2 = NULL;


    std::cout <<"\n---------------Linked List 1---------------\n";
    insertListNode(&head1,1);
    insertListNode(&head1,2);
    insertListNode(&head1,3);
    insertListNode(&head1,4);
    //insertListNode(&head1,5);
    insertListNode(&head1,4);
    insertListNode(&head1,3);
    insertListNode(&head1,2);
    insertListNode(&head1,1);

/*
    std::cout <<"\n---------------Linked List 2---------------\n";
    for(int i=10; i>0; i--)
        insertListNode(&head2,i);
*/

    displayList(head1);
    flag = isPalindrome2(head1);

    std::cout<<"\n\nLinked list is palindrome = "<< std::boolalpha << flag;


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



ListNode* reverseList(ListNode *head)
{
    ListNode *cur, *prev, *temp;

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



bool isPalindrome(ListNode* head)
{
    ListNode *slow, *fast;

    slow = head;
    fast = head;

    while(fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    fast = slow->next;
    slow->next = NULL;
    slow = head;

    fast = reverseList(fast);

    displayList(fast);

    while(slow && fast)
    {
        std::cout<<"\nslow = "<<slow->val<<"fast = "<< fast->val;
        if(slow->val != fast->val)
            return false;

        slow = slow->next;
        fast = fast->next;
    }

    return true;
}



bool isPalindrome2(ListNode* head)
{
    static ListNode *temp = head;

    if(!head)
        return true;

    bool ans, isEqual;

    ans = isPalindrome2(head->next);                            // to store results from all the previous comparisons up till now

    isEqual = (temp->val == head->val)?true:false;      // to compare current result

    temp = temp->next;                                  // temp pointer is increased & our function's pointer is decreased

    return (ans && isEqual);                            // return true only if all the previous comparisons are TRUE along with current comparison

}
