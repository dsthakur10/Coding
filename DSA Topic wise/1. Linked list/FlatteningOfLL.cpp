
/*

Given a Linked List of size N, where every node represents a sub-linked-list and contains two pointers:
(i) a next pointer to the next node,
(ii) a bottom pointer to a linked list where this node is head.
Each of the sub-linked-list is in sorted order.
Flatten the Link List such that all the nodes appear in a single level while maintaining the sorted order.

Note: The flattened list will be printed using the bottom pointer instead of next pointer.


*/

Node *flatten(Node *root)
{
    // starting node of sublist , current pointer to starting node

    priority_queue<pin, vector<pin>, greater<pin>> pq;

    Node *temp = root;

    while(temp)
    {
        pq.push({temp->data, temp});
        temp = temp->next;
    }

    root = NULL;
    temp = NULL;
    while(!pq.empty())
    {
        Node* cur = pq.top().second;
        pq.pop();

        if(!temp)
        {
            root = cur;
            temp = cur;
        }

        else
        {
            temp->next = cur;
            temp = temp->next;
        }

        if(cur->bottom)
            pq.push({cur->bottom->data, cur->bottom});
    }

    temp = root;
    while(temp)
    {
        temp->bottom = temp->next;
        temp = temp->next;
    }

    return root;
}
