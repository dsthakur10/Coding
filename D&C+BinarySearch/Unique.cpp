// Given a sorted array in which all elements appear twice (one after one) and one element appears only once.

#include<iostream>
using namespace std;

int uniquee(int arr[],int low,int high);

int main()
{
    int A[] = {1, 1, 3, 3, 4, 4, 5, 5, 7, 7, 8};

    int len = sizeof(A)/sizeof(A[0]);

    int index = uniquee(A,0,len-1);

    cout<<endl<<"A[] =";
    for(int i=0;i<len;i++)
        cout<<" "<<A[i];

    cout<<endl<<endl<<"Unique element at index: "<<index<<endl;
}


int uniquee(int arr[],int low,int high)             // array will always contain odd number of elements
{

    if(low==high)
        return arr[low];

    int mid = (low+high)/2;

    if(mid%2==0)
    {
        if(arr[mid] == arr[mid+1])           //mid is even index && arr[mid]=arr[mid+1] ==> skip 2 elements in next right subarray
            uniquee(arr,mid+2,high);

        else
            uniquee(arr,low,mid);
    }

    else
    {
        if(arr[mid] == arr[mid-1])           //mid is odd index && arr[mid]=arr[mid-1] ==> skip 1 element in next right subarray
            uniquee(arr,mid+1,high);

        else                                 //arr[mid] != arr[mid-1] ==>
            uniquee(arr,low,mid-1);
    }
}
