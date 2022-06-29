// Given preorder of a Full binary tree, calculate its depth(height) [STARTING FROM DEPTH 0]. The preorder is given as a string with two possible characters.
// ‘l’ denotes the leaf, ‘n’ denotes internal node

// The given tree can be seen as a full binary tree where every node has 0 or two children. The two children of a node can be ‘n’ or ‘l’ or mix of both.

// Examples :
// Input : nlnll    Output : 2
// Input : nlnnlll  Output : 3

#include<iostream>

int heightOfFullTree(char pre[],int n, int& index);

int main()
{
    char pre[] = {'n','n','l','l','n','n','l','l','l'};
    int n = sizeof(pre)/sizeof(pre[0]);
    int index = 0;

    int height = heightOfFullTree(pre,n,index);

    std::cout<<"Height of tree = "<<height;
}


// Since preorder numbering starts from root itself, the nodes traversed in array follows the sequence of Root-Left-Right


int heightOfFullTree(char pre[],int n, int& index)
{
    if(index>=n || pre[index] == 'l')                       // for leaf no matter where always return 0. index is from 0--n-1
        return 0;

    index++;

    int left = heightOfFullTree(pre,n,index);               // Calculate height of LST. Traverse left subtree first. (Index++ before traversing will take care for proper node)

    index++;

    int right = heightOfFullTree(pre,n,index);              // Calculate height of RST. Traverse right subtree

    return 1 + std::max(left,right);
}
