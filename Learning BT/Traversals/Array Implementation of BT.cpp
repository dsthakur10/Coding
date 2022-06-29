// Given an array that represents a tree in such a way that array indexes are values in tree nodes and array values give the parent node of that
// particular index (or node). The value of the root node index would always be -1 as there is no parent for root.
// Construct the standard linked representation of given Binary Tree from this given representation


// tree[0] ==> data is yet empty
// tree[-1] ==> forbidden index. Should be kept empty

/*

        Case 1: 0 — n-1

        if (say)parent = p;
        then left_child = (2*p)+1;
        and right_child = (2*p)+2;

        Case 2: 1 — n

        if (say)parent = p;
        then left_child = (2*p);
        and right_child = (2*p)+1;

*/

#include<iostream>

void setRoot(int tree[], int key);
void setLeftChild(int tree[], int key, int pIndex);
void setRightChild(int tree[], int key, int pIndex);
void display(int tree[], int size);

int main()
{
    int tree[15] = {0,0,0,-1,-1,0,0,-1,-1,-1,-1,-1,-1,-1,0};
/*
    setRoot(tree,55);
    setLeftChild(tree,77,2);
    setRightChild(tree,11,2);

    setLeftChild(tree,12,0);
    setRightChild(tree,99,0);
    setLeftChild(tree,24,1);
    setRightChild(tree,36,1);
    setLeftChild(tree,77,2);
    setRightChild(tree,11,2);

    display(tree,sizeof(tree)/sizeof(tree[0]));
*/

    setRoot(tree,100);
    setLeftChild(tree,200,0);
    setRightChild(tree,300,0);
    setLeftChild(tree,400,1);
    setRightChild(tree,500,1);
    setLeftChild(tree,600,2);
    setRightChild(tree,700,2);
    setLeftChild(tree,800,3);
    setRightChild(tree,900,3);
    setLeftChild(tree,1000,4);
    setRightChild(tree,1100,4);
    setLeftChild(tree,1200,5);
    setRightChild(tree,1300,5);
    setLeftChild(tree,1400,6);
    setRightChild(tree,1500,6);

    display(tree,sizeof(tree)/sizeof(tree[0]));

}


void setRoot(int tree[], int key)
{
    if(tree[0] == 0)
    {
        std::cout<<"\nRoot inserted";
        tree[0] = key;
    }

    else
        std::cout<<"\nRoot of tree already exist";
}


void setLeftChild(int tree[], int key, int pIndex)
{
    int l = 2*pIndex+1;
    if(tree[pIndex] == 0 || tree[pIndex] == -1)
        std::cout<<"\n\nParent not found. Cannot set left child at index "<<l<<" for parent index "<<pIndex;

    else
    {
        if(tree[l] == -1)
            std::cout<<"\n\nInserting node at this index "<<l<<" is forbidden";
        else
        {
            tree[l] = key;
            std::cout<<"\n\nLeft child at index "<<l<<" for parent index "<<pIndex<<" inserted";
        }
    }
}


void setRightChild(int tree[], int key, int pIndex)
{
    int r = 2*pIndex+2;
    if(tree[pIndex] == 0 || tree[pIndex] == -1)
        std::cout<<"\n\nParent not found. Cannot set right child at index "<<r<<" for parent index "<<pIndex;

    else
    {
        if(tree[r] == -1)
            std::cout<<"\n\nInserting node at this index "<<r<<" is forbidden";
        else
        {
            tree[r] = key;
            std::cout<<"\n\nRight child at index "<<r<<" for parent index "<<pIndex<<" inserted";
        }
    }
}


void display(int tree[],int size)
{
    std::cout<<"\n\nTree: ";
    for(int i=0; i<size; i++)
        std::cout<<tree[i]<<" ";
}
