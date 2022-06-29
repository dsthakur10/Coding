// Convert Sorted List to Binary Search Tree

/*

Given the head of a singly linked list where elements are sorted in ascending order, convert it to a
height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees
of every node never differ by more than 1.

*/


// Method-1 --> Convert linked-list -> array. Now solve by finding middle element recursively.
// O(n) time | O(n) space

TreeNode* sortedListToBST(ListNode* head)
{
    vector<int> nums;

    while(head)
    {
        nums.push_back(head->val);
        head = head->next;
    }

    TreeNode* root = buildBST(nums, 0, nums.size()-1);
    return root;
}


TreeNode* buildBST(vector<int>& nums, int low, int high)
{
    if(low > high)
        return NULL;

    int mid = low + (high-low)/2;

    TreeNode* root = new TreeNode(nums[mid]);

    root->left = buildBST(nums, low, mid-1);
    root->right = buildBST(nums, mid+1, high);

    return root;
}




// Method-2 --> Find middle node using slow-fast pointer. Divide the list into 2 equal parts based on middle node
// Solve each part recursively.
// First sublist --> head -> middlePrev
// Second sublist --> middleNext -> tail
// Tree's root node = middle listNode

TreeNode* sortedListToBST2(ListNode* head) {

    TreeNode* root = buildBST(head);
    return root;
}


TreeNode* buildBST2(ListNode* head)
{
    if(!head)
        return NULL;

    if(!head->next)                             // single node in list
        return new TreeNode(head->val);

    if(!head->next->next)                       // 2 nodes in list
    {
        TreeNode* root = new TreeNode(head->val);
        root->right = new TreeNode(head->next->val);

        return root;
    }

    ListNode *middlePrev, *middle, *middleNext;

    middlePrev = findMiddleNode(head);
    middle = middlePrev->next;
    middleNext = middle->next;

    TreeNode* root = new TreeNode(middle->val);

    // Need to cut the middle node which is chosen as root node from entire list.
    // Also need to put an end to first sublist to stop iterating it till the end of original list

    middlePrev->next = NULL;
    middle->next = NULL;

    root->left = buildBST(head);
    root->right = buildBST(middleNext);

    return root;
}


ListNode* findMiddleNode(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* slowPrev = NULL;

    while(fast->next != NULL && fast->next->next != NULL)
    {
        slowPrev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    return slowPrev;
}
