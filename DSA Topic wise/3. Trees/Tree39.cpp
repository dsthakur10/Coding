// Populating Next Right Pointers in Each Node II

/*

Given a binary tree

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}

Populate each next pointer to point to its next right node. If there is no next right node,
the next pointer should be set to NULL.

Initially, all next pointers are set to NULL

*/




// Method-1 --> Recursion

// NOTE: Always populate in TOP-DOWN & RIGHT-LEFT manner
// Because to populate current nodes's next pointer, you want 2 things:
//      1. parent --> to get link to next node
//      2. parent's neighbor in the right --> to get a link to next node's children


Node* connect(Node* root)
{
    if(!root || (!root->left && !root->right))
        return root;

    Node *lc , *rc;

    lc = root->left;
    rc = root->right;

    if(lc)
    {
        Node* temp = root->next;
        if(rc)
            lc->next = rc;

        else
        {
            while(temp)
            {
                if(temp->left)
                {
                    lc->next = temp->left;
                    break;
                }

                else if(temp->right)
                {
                    lc->next = temp->right;
                    break;
                }

                temp = temp->next;
            }
        }
    }

    if(rc)
    {
        Node* temp = root->next;
        while(temp)
        {
            if(temp->left)
            {
                rc->next = temp->left;
                break;
            }

            else if(temp->right)
            {
                rc->next = temp->right;
                break;
            }

            temp = temp->next;
        }
    }

    root->right = connect(root->right);         // right before left
    root->left = connect(root->left);

    return root;
}




Node* connect(Node* root)
{
    Node* head = NULL;                               //head of the next level
    Node* prev = NULL;                               //the leading node on the next level
    Node* cur = root;                                //current node of current level

    while(cur)
    {
        while(cur)
        {                                                                   //iterate on the current level
                                                    //left child
            if(cur->left)
            {
                if(prev)
                    prev->next = cur->left;

                else
                    head = cur->left;

                prev = cur->left;
            }
                                                    //right child
            if(cur->right)
            {
                if(prev)
                    prev->next = cur->right;

                else
                    head = cur->right;

                prev = cur->right;
            }
                                                                    //move to next node
            cur = cur->next;
        }

                                                                    //move to next level
        cur = head;
        head = NULL;
        prev = NULL;
    }

    return root;

}
