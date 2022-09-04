
ListNode* middleNode(ListNode* head) {

    ListNode *fast, *slow;

    fast = head;
    slow = head;

    while(fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}


