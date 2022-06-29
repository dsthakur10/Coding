// You are given two non-empty linked lists representing two non-negative integers.
// The most significant digit comes first and each of their nodes contains a single digit. Add the two numbers and return the sum as a linked list.

// You may assume the two numbers do not contain any leading zero, except the number 0 itself.


#include<iostream>
#include <cstdlib>
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
int getLength(ListNode *head);
ListNode *sumLL(ListNode *l1, ListNode *l2, int offset);

ListNode* solution1(ListNode* head1, ListNode* head2);                      // 3*O(n) - recursive solution - 2 loops for length & 3rd loop in recursion
ListNode* solution2(ListNode* head1, ListNode* head2);                      // O(n) - stack solution
ListNode* solution3(ListNode* head1, ListNode* head2);                      // reverse both linked list & then add starting from head node

int main()
{
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,3);
    insertListNode(&head1,4);
    insertListNode(&head1,2);
    insertListNode(&head1,7);
    insertListNode(&head1,8);

/*
    insertListNode(&head2,2);
    insertListNode(&head2,5);
    insertListNode(&head2,2);
    insertListNode(&head2,3);
    insertListNode(&head2,4);
    insertListNode(&head2,1);
*/

    insertListNode(&head2,4);
    insertListNode(&head2,6);
    insertListNode(&head2,5);

    ListNode *sum = solution2(head1,head2);

    displayList(head1);
    displayList(head2);

    std::cout<<"\nSum of Linked List: ";

    displayList(sum);
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


int getLength(ListNode *head)
{
    int counter=0;
    while(head)
    {
        head = head->next;
        counter++;
    }

    return counter;
}



ListNode *sumLL(ListNode *p1, ListNode *p2, int offset)                     // p1 >= p2 always
{
    // 2 cases:
    // Case - 1: if p1.length > p2.length ==> create new node with p1 value
    // case - 2: if p1.length = p2.length ==> create new node with value = sum of values of both nodes

    // result stores this newly created node.
    // post stores the next node to be connected to this node.
    // return result

    // stopping condition occurs when p1 = p2 = NULL. post = NULL for this case & result of p1-p2's tail is connected to NULL.

    if(!p1)
        return NULL;

    ListNode *result = (offset == 0) ? new ListNode(p1->val + p2->val) : new ListNode(p1->val);     // check whether p1 becomes same length as p2

    ListNode *post = (offset == 0) ? sumLL(p1->next,p2->next,0) : sumLL(p1->next,p2,offset-1);      // keep p2 as it is if p1 has greater length than p2


    if (post != NULL && post->val > 9)                                      // adjust carry in result & modify post if summation exceeds 9
    {
        result->val += 1;
        post->val = post->val % 10;
    }

                                                                            // combine nodes
    result->next = post;
    return result;

}



ListNode* solution1(ListNode* l1, ListNode* l2)
{
    int len1=0, len2=0, diff;

    diff = getLength(l1) - getLength(l2);

    ListNode *head = new ListNode(1);

    head->next = (diff >= 0) ? sumLL(l1,l2,diff) : sumLL(l2,l1,abs(diff));

    if(head->next->val > 9)
    {
        head->next->val %= 10;
        return head;
    }

    return head->next;

}



ListNode* solution2(ListNode* l1, ListNode* l2)
{
    std::stack<int> mystack1, mystack2;

    while(l1)
    {
        mystack1.push(l1->val);
        l1 = l1->next;
    }

    while(l2)
    {
        mystack2.push(l2->val);
        l2 = l2->next;
    }

    int carry = 0;
    int sum;
    ListNode *head = NULL;

    while(!mystack1.empty() && !mystack2.empty())
    {
        ListNode *ptr = new ListNode();

        sum = mystack1.top() + mystack2.top() + carry;

        if(sum > 9)
        {
            carry = 1;
            sum = sum%10;
        }

        else
            carry = 0;

        ptr->val = sum;
        ptr->next = head;
        head = ptr;

        mystack1.pop();
        mystack2.pop();
    }

    while(!mystack1.empty())
    {
        ListNode *ptr = new ListNode();

        sum = mystack1.top() + carry;
        if(sum > 9)
        {
            carry = 1;
            sum = sum%10;
        }

        else
            carry = 0;

        ptr->val = sum;
        ptr->next = head;
        head = ptr;

        mystack1.pop();
    }

    while(!mystack2.empty())
    {
        ListNode *ptr = new ListNode();

        sum = mystack2.top() + carry;
        if(sum > 9)
        {
            carry = 1;
            sum = sum%10;
        }

        else
            carry = 0;

        ptr->val = sum;
        ptr->next = head;
        head = ptr;

        mystack2.pop();
    }

    if(carry == 1)
    {
        ListNode *ptr = new ListNode(1);

        //head->val %= 10;
        ptr->next = head;

        head = ptr;
    }

    return head;
}
