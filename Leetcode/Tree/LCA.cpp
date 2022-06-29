#include<iostream>
#include<queue>
#include<unordered_map>
#include<unordered_set>
#include<stack>

using namespace std;


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
void insertNode(TreeNode **root, int x);                 // iterative way (using queue)
void levelorder(TreeNode *root);

TreeNode* parent = NULL;



bool LCA(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(!root)
        return false;

    int mid = (root == p || root == q) ? 1 : 0;

    int left = LCA(root->left, p, q) ? 1 : 0;

    int right = LCA(root->right, p ,q) ? 1 : 0;

    if(left + mid + right >= 2)
        parent = root;

    return (left + mid + right >= 1);
}


TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    LCA(root, p, q);

    return parent;
}



TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if(root == NULL || root == p || root == q)
        return root;

    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if(left && right)
        return root;

    return (left ? left : right);
}



// Method-3 --> maintain parent pointer

TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q)
{
    unordered_map<TreeNode*, TreeNode*> mp;     // <node, parent>
    stack<TreeNode*> st;
    unordered_set<TreeNode*> myset;

    TreeNode *cur;

    st.push(root);
    mp[root] = NULL;

    while(mp.find(p) == mp.end() || mp.find(q) == mp.end())
    {
        cur = st.top();
        st.pop();

        if(cur->right)
        {
            mp[cur->right] = cur;
            st.push(cur->right);
        }

        if(cur->left)
        {
            mp[cur->left] = cur;
            st.push(cur->left);
        }

    }


    TreeNode *temp = p;

    while(temp != NULL)
    {
        myset.insert(temp);
        temp = mp[temp];
    }

    temp = q;
    pair<unordered_set<TreeNode*>::iterator, bool> mypair;

    mypair = myset.insert(temp);
    while(mypair.second == true)
    {
        temp = mp[temp];
        mypair = myset.insert(temp);
    }

    return temp;
}



int main()
{
    TreeNode *root = NULL;

    insertNode(&root,3);
    insertNode(&root,5);
    insertNode(&root,1);
    insertNode(&root,6);
    insertNode(&root,2);
    insertNode(&root,0);
    insertNode(&root,8);

    TreeNode *temp = root;
    temp = temp->left;
    temp = temp->right;

    temp->left = createNode(7);
    temp->right = createNode(4);

    std::cout<<"Level-order traversal of tree: ";
    levelorder(root);

    TreeNode *p, *q;

    p = root;
    p = p->left;
    q = root;
    q = root->right;

    TreeNode *result = lowestCommonAncestor3(root, p, q);

    if(result)
        cout << endl << result->val;

    else
        cout << "\nNULL";
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

    std::cout << "\n";
    while(!q.empty())
    {
        temp = q.front();
        q.pop();

        std::cout<<temp->val<<' ';

        if(temp->left)
            q.push(temp->left);

        if(temp->right)
            q.push(temp->right);
    }
}

