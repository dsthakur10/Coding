//Given two sorted arrays. There is only 1 difference between the arrays. The first array has one element extra added in between. Find the index of the extra element.

#include<iostream>
using namespace std;

int extra(int A[],int B[],int low,int high);


int main()
{
    int A[]={1, 2, 4, 6, 8, 10, 12, 13};
    int B[]={1, 2, 6, 8, 10, 12, 13};

    int len1 = sizeof(A)/sizeof(A[0]);
    int len2 = sizeof(B)/sizeof(B[0]);

    int index = extra(A,B,0,len1-1);

    cout<<endl<<"A[] =";
    for(int i=0;i<len1;i++)
        cout<<" "<<A[i];

    cout<<endl<<"B[] =";
    for(int i=0;i<len2;i++)
        cout<<" "<<B[i];

    cout<<endl<<endl<<"Extra element at index: "<<index<<endl;
}


int extra(int A[],int B[],int low,int high)
{
    if(low == high)
    {
        if((sizeof(B)/sizeof(B[0])) == low || A[low]!=B[low])
            return low;
        else
            return -1;
    }

    int mid=(low+high)/2;

    if(A[mid]!=B[mid])
    {
        if(A[mid-1] == B[mid-1])
            return mid;
        else
            return extra(A,B,low,mid-1);
    }

    else
        return extra(A,B,mid+1,high);

}
