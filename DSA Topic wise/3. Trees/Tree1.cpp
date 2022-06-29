// Traversals - iterative

#include<iostream>
#include<queue>
#include<stack>
#include<vector>

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
void insertNode(TreeNode **root,int x);                     // iterative way (using queue)
void inorder(TreeNode *root);
void inorder2(TreeNode *root);
void preorder2(TreeNode *root);
void postorder2(TreeNode *root);                            // 2 stacks
void postorder3(TreeNode *root);                            // 1 stack

int main()
{
    TreeNode *root=NULL;
/*
    insertNode(&root,5);
    insertNode(&root,7);
    insertNode(&root,69);
    insertNode(&root,11);
    insertNode(&root,100);
    insertNode(&root,12);
    insertNode(&root,8);
*/
    for(int i=1;i<=5;i++)
        insertNode(&root,i);

    TreeNode *temp = root;
    while(temp->right)
        temp = temp->right;

    temp->right = createNode(6);
    temp = temp->right;
    temp->left = createNode(7);
    temp->right = createNode(8);

    inorder2(root);
    std::cout << "\n Preorder = ";
    preorder2(root);
    std::cout << "\n Postorder = ";
    postorder2(root);
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


void inorder(TreeNode *root)
{
    if(!root)
        return;

    inorder(root->left);

    std::cout<<root->val<<" ";

    inorder(root->right);
}



void inorder2(TreeNode *root)
{
    if(!root)
        return;

    std::stack<TreeNode*> st;
    TreeNode *cur, *temp;

    st.push(root);
    cur = root->left;

    while(!st.empty() || cur)
    {
        while(cur)
        {
            st.push(cur);
            cur = cur->left;
        }

        cur = st.top();
        st.pop();

        std::cout << cur->val << " ";
        cur = cur->right;
    }
}


void preorder2(TreeNode *root)
{
    if(!root)
        return;

    std::stack<TreeNode*> st;
    TreeNode *cur, *temp;

    st.push(root);

    while(!st.empty())
    {
        cur = st.top();
        st.pop();

        std::cout << cur->val<<" ";

        if(cur->right)
            st.push(cur->right);
        if(cur->left)
            st.push(cur->left);
    }
}



void postorder2(TreeNode *root)
{
    if(!root)
        return;

    std::stack<TreeNode*> s1,s2;
    TreeNode *cur, *temp;

    s1.push(root);

    while(!s1.empty())
    {
        cur = s1.top();
        s1.pop();
        s2.push(cur);

        if(cur->left)
            s1.push(cur->left);
        if(cur->right)
            s1.push(cur->right);

    }

    while(!s2.empty())
    {
        std::cout << s2.top()->val << " ";
        s2.pop();
    }

}



void postorder3(TreeNode *root)
{
    std::stack<TreeNode*> st;
    TreeNode *temp, *cur;

    st.push(root);

    while()
}
