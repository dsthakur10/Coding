/*

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

*/


// size of min-heap = K

typedef pair<int, ListNode*> pil;

ListNode* mergeKLists(vector<ListNode*>& lists) {

    ListNode *head = NULL, *last = NULL;
    priority_queue<pil, vector<pil>, greater<pil>> pq;

    // Initializing min-heap with first node of each lists

    int k = lists.size();
    for(int i=0; i<k; i++)
    {
        if(lists[i])
            pq.push({lists[i]->val, lists[i]});
    }

    while(!pq.empty())
    {
        int value = pq.top().first;
        ListNode* tempNode = pq.top().second;
        pq.pop();

        if(!head)
        {
            head = tempNode;
            last = head;
        }

        else
        {
            last->next = tempNode;
            last = last->next;
        }

        // Pushing next node from the same list whose node is just used to construct final list.
        if(tempNode->next)
            pq.push({tempNode->next->val, tempNode->next});
    }

    return head;
}



