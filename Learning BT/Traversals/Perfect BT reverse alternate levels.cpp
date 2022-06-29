// Given perfect binary tree: 1  2,3  4,5,6,7  8,9,10,11,12,13,14,15

// Reverse alternate level nodes in perfect BT : 1  3,2  4,5,6,7  15,14,13,12,11,10,9,8

#include<iostream>
#include<queue>
#include<stack>
#include<deque>
#include<vector>
#include<algorithm>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode()
    {
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x)
    {
        val = x;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(int x, TreeNode *lptr, TreeNode *rptr)
    {
        val = x;
        left = lptr;
        right = rptr;
    }
};


TreeNode* createNode(int x);
void insertNode(TreeNode **root,int x);                         // iterative way (using queue)
void levelorder(TreeNode *root);

void perfectBTreverseAlternateLevel(TreeNode *root);                             // queue + vector - O(n) time & O(n) space
void perfectBTreverseAlternateLevel2(TreeNode *root);                            // inorder recursive twice + vector - 2*O(n) time & O(n) space
void perfectBTreverseAlternateLevel3(TreeNode *root);                            // preorder recursive - O(n) time & O(n) space

void getInorder(TreeNode *root, std::vector<int>& vec, bool flag);
void putInorder(TreeNode *root, std::vector<int>& vec, bool flag);
void usePreorder(TreeNode *root1, TreeNode *root2, bool flag);

int main()
{
    TreeNode *root = NULL;

    for(int i=1; i<=63; i++)
        insertNode(&root,i);

    levelorder(root);

    //std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    //perfectBTreverseAlternateLevel(root);

    //std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    //perfectBTreverseAlternateLevel2(root);

    std::cout<<"\nPerfect BT specific Level order traversal from bottom: \n";
    perfectBTreverseAlternateLevel3(root);

    levelorder(root);
}


TreeNode* createNode(int x)
{
    TreeNode *ptr = new TreeNode(x);
    return ptr;
}


void insertNode(TreeNode **root,int x)
{
    if(!(*root))
    {
        *root = createNode(x);
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode *ptr , *temp;
    ptr = createNode(x);

    q.push(*root);

    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        if(!temp->left)
        {
            temp->left = ptr;
            return;
        }

        if(!temp->right)
        {
            temp->right = ptr;
            return;
        }

        q.push(temp->left);
        q.push(temp->right);
    }
}



void levelorder(TreeNode *root)
{
    if(root == NULL)
    {
        std::cout<<"\n\nTree empty";
        return;
    }

    std::queue<TreeNode*> q;
    TreeNode* temp;

    q.push(root);

    while(!q.empty())
    {
        int n = q.size();

        while(n>0)
        {
            temp = q.front();
            q.pop();

            std::cout<<temp->val<<' ';

            if(temp->left)
                q.push(temp->left);

            if(temp->right)
                q.push(temp->right);

            n--;
        }

        std::cout<<"\n";
    }
}




//-----------Method-1------------

// Traverse the tree normally with queue. Just in case of alternate level (even levels), store the nodes in vector.
// At the end of level, reverse the vector by swapping first & last elements only IF the level is even.


void perfectBTreverseAlternateLevel(TreeNode *root)
{
    if(!root)
        return;

    std::queue<TreeNode*> q;
    TreeNode *temp;
    bool flag = true;

    if(root->left)
    {
        q.push(root->left);
        q.push(root->right);
    }

    while(!q.empty())
    {
        int n = q.size();

        if(flag)
        {
            std::vector<TreeNode*> nodes;

            while(n>0)
            {
                temp = q.front();
                q.pop();

                if(temp->left)
                {
                    q.push(temp->left);
                    q.push(temp->right);
                }
                nodes.push_back(temp);
                n--;
            }

            for(int i=0,j=nodes.size()-1;i<j;i++,j--)
                std::swap(nodes[i]->val,nodes[j]->val);
        }

        else
        {
            while(n>0)
            {
                temp = q.front();
                q.pop();

                if(temp->left)
                {
                    q.push(temp->left);
                    q.push(temp->right);
                }
                n--;
            }
        }

        flag = !flag;
    }
}




//------------Method-2-------------


// 2 inorder traversals.
// Traverse the given tree in inorder fashion and store all even level nodes in an auxiliary array.
// Reverse the array.
// Traverse the tree again inorder fashion. While traversing the tree, one by one take elements from array and store elements from an array to every even level traversed node.


void getInorder(TreeNode *root, std::vector<int>& vec, bool flag)
{
    if(!root)
        return;

    getInorder(root->left, vec, !flag);

    if(flag)
        vec.push_back(root->val);

    getInorder(root->right, vec, !flag);

}


void putInorder(TreeNode *root, std::vector<int>& vec, bool flag)
{
    if(!root)
        return;

    putInorder(root->left, vec, !flag);

    if(flag)
    {
        root->val = vec[0];
        vec.erase(vec.begin());
    }

    putInorder(root->right, vec, !flag);
}



void perfectBTreverseAlternateLevel2(TreeNode *root)
{
    if(!root)
        return;

    std::vector<int> myvec;

    getInorder(root, myvec, false);
    std::reverse(myvec.begin(), myvec.end());
    putInorder(root, myvec, false);

}



//-------------Method-3-------------

// Use preorder recursively with swapping values of children nodes from both sides.


void usePreorder(TreeNode *root1, TreeNode *root2, bool flag)
{
    if(!root1 || !root2)
        return;

    if(flag)
        std::swap(root1->val, root2->val);

    usePreorder(root1->left, root2->right, !flag);

    usePreorder(root1->right, root2->left, !flag);
}


void perfectBTreverseAlternateLevel3(TreeNode *root)
{
    if(!root)
        return;

    usePreorder(root->left, root->right, true);
}
