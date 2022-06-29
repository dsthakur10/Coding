// Given the head of a singly linked list and two integers left and right where left <= right,
// reverse the nodes of the list FROM POSITION left TO POSITION right, and return the reversed list.


#include<iostream>

 int flag = 0;
    //ListNode* rightmost;                          // produces error. must be defined after class definition
    //ListNode* leftmost;

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


ListNode* rightmost;                                            // for recursive solution to handle corners of reversed LL
ListNode* leftmost;

void insertListNode(ListNode **head, int val);
void displayList(ListNode *head);
ListNode* reverseList(ListNode *head);

ListNode* solution1(ListNode *head, int left, int right);       // 3*O(n) in worst case. 1st loop - finding sublist
                                                                // 2nd loop - reverse sublist. 3rd loop - connect sublist to right

ListNode* solution2(ListNode *head, int left, int right);       // O(n) - single pass (no node is repeated)

ListNode* solution3(ListNode *prev,ListNode *cur, int left, int right);     // O(n) - recursive solution


int main()
{
    int left,right;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,10);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,6);
    insertListNode(&head1,4);
    insertListNode(&head1,2);
    insertListNode(&head1,1);

    insertListNode(&head2,200);
    insertListNode(&head2,100);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    std::cout<<"Enter range numbers LEFT & RIGHT: ";
    std::cin>>left>>right;

    head1 = solution3(head1,head1->next,left,right);

    std::cout<<"\n\nReversed Linked List in given interval: ";
    displayList(head1);
 /*
    displayList(head2);

    std::cout<<"Enter range numbers LEFT & RIGHT: ";
    std::cin>>left>>right;

    head2 = solution3(head2,head2->next,left,right);

    std::cout<<"\n\nReversed Linked List in given interval: ";
    displayList(head2);
*/
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


ListNode* solution1(ListNode *head, int left, int right)
{
    if(!head->next)
        return head;

    int counter=1;                                              // afterRight to keep track of right sublist
    ListNode *temp = head, *beforeLeft = NULL, *afterRight;     // beforeLeft to keep track of left sublist

    if(left != 1)
    {
        while(counter<left)                             // Finding first position to apply reverse (head of sublist to reverse)
        {
            counter++;
            beforeLeft = temp;
            temp = temp->next;
        }
    }

    while(counter<right)                                // Finding last position (end of sublist)
    {
        counter++;
        temp = temp->next;
    }

    afterRight = temp->next;
    temp->next = NULL;


    if(left != 1)                                       // if left != head
    {
        beforeLeft->next = reverseList(beforeLeft->next);
        temp = beforeLeft;
    }

    else                                                // if head itself is left
    {
        head = reverseList(head);
        temp = head;
    }

    while(temp->next)
        temp = temp->next;

    temp->next = afterRight;

    return head;
}


ListNode* solution2(ListNode *head, int left, int right)
{
    if(!head || !head->next)
        return head;

    int counter = 1;
    ListNode *beforeLeft, *cur, *prev, *temp, *first;       // first pointer is used to avoid extra loop to connect sublist

    cur = head;
    prev = NULL;
    beforeLeft = NULL;

    while(counter < left)
    {
        beforeLeft = cur;
        cur = cur->next;
        counter++;
    }

    first = cur;                                    // hold first element of sublist to be reversed

    while(counter<=right)
    {
        temp = cur->next;
        cur->next = prev;

        prev = cur;
        cur = temp;
        counter++;
    }

                                                    // first holds last node in newly reversed sublist
    if(beforeLeft)                                  // prev holds first node in newly reversed sublist
        beforeLeft->next = prev;                    // cur holds right sublist

    else                                            // left = 1 (head itself should be reversed)
        head = prev;

    first->next = cur;

    return head;
}



ListNode* solution3(ListNode *prev,ListNode *cur, int left, int right)
{
    //static ListNode* rightmost = NULL;
    if(right == 1)
    {
        rightmost = cur;                            // cannot use static here as all other recursive calls will not recognize it
        return prev;
    }

    if(left == 1)
    {
        //static ListNode* leftmost = prev;           // first time when left=1, store address of prev node. Successive calls
                                                    // should not update leftmost. So static is used.(One time initialization)

        if(flag == 0)
        {
            leftmost = prev;
            flag = 1;
        }

        ListNode *ptr = solution3(cur,cur->next,left,right-1);

        leftmost->next = rightmost;
        cur->next = prev;
        return ptr;                                 // ptr contains address of last node in sublist to be reversed in all left=1 cases
    }


    ListNode *ptr = solution3(cur,cur->next,left-1,right-1);

    prev->next = ptr;
    return prev;                                    // prev contains address of current node for normal linking as it was before.

}
