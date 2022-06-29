// Given the head of a singly linked list and an integer k, split the linked list into k consecutive linked list parts.

// The length of each part should be as equal as possible: NO TWO PARTS SHOULD HAVE A SIZE DIFFERING BY MORE THAN ONE.
// THIS MAY LEAD TO SOME PARTS BEING NULL.

// The parts should be in the order of occurrence in the input list & PARTS OCCURRING EARLIER SHOULD ALWAYS HAVE A SIZE
// GREATER THAN OR EQUAL TO PARTS OCCURRING LATER.

// Return an array of the k parts.

#include<iostream>
#include<vector>

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

std::vector<ListNode*> solution1(ListNode *head, int k);

int main()
{
    std::vector<ListNode*> parts;
    int k;
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insertListNode(&head1,20);
    insertListNode(&head1,19);
    insertListNode(&head1,18);
    insertListNode(&head1,17);
    insertListNode(&head1,16);
    insertListNode(&head1,15);
    insertListNode(&head1,14);
    insertListNode(&head1,13);
    insertListNode(&head1,12);
    insertListNode(&head1,11);
    insertListNode(&head1,10);
    insertListNode(&head1,9);
    insertListNode(&head1,8);
    insertListNode(&head1,7);
    insertListNode(&head1,6);
    insertListNode(&head1,5);
    insertListNode(&head1,4);
    insertListNode(&head1,3);
    insertListNode(&head1,2);
    insertListNode(&head1,1);

    insertListNode(&head2,100);
    insertListNode(&head2,200);

    std::cout<<"\n\nLinked List: ";
    displayList(head1);

    std::cout<<"\nEnter number of partitions:";
    std::cin>>k;
    parts = solution1(head1,k);

    for(int i=0;i<parts.size();i++)
    {
        ListNode *ptr = parts[i];

        std::cout<<"\nList ["<<i<<"] = ";
        while(ptr)
        {
            std::cout<<ptr->val<<" ";
            ptr = ptr->next;
        }
    }

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


std::vector<ListNode*> solution1(ListNode *head, int k)
{
    if(k==1)
        return {head};

    std::vector<ListNode*> parts;
    int div, rem, length=0;
    ListNode *temp, *last;

    temp = head;
    while(temp)
    {
        temp = temp->next;
        length++;
    }

    div = length/k;                 // div shows min size of each partition
    rem = length%k;                 // rem shows extra elements to be distributed among initial partitions.
    k = k - length;                 // case when #partitions > length of LL. Many parts will be NULL.

    // eg. length = 20 , k = 8 ==> each partition of size=2 & 4 elements remaining to be distributed

/*
    while(rem>0)
    {
        int counter = div+1;
        temp = head;

        while(counter>0)
        {
            last = head;
            head = head->next;
            counter--;
        }

        last->next = NULL;
        parts.push_back(temp);
        rem--;
    }

    while(head)
    {
        int counter = div;
        temp = head;

        while(counter>0)
        {
            last = head;
            head = head->next;
            counter--;
        }

        last->next = NULL;
        parts.push_back(temp);
    }
*/

    while(head)
    {
        int counter = (rem > 0)?div+1:div;
        temp = head;

        while(counter>0)
        {
            last = head;
            head = head->next;
            counter--;
        }

        last->next = NULL;
        parts.push_back(temp);
        rem--;
    }

    while(k>0)                                      // to input NULL lists for #partitions > length
    {
        parts.push_back(NULL);
        k--;
    }

    return parts;
}
