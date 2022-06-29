//Given a sorted array arr[] and a number x, write a function that counts the occurrences of x in arr[]

#include<iostream>
using namespace std;

int firstOccurrence(int arr[],int low,int high,int x);
int lastOccurrence(int arr[],int low,int high,int x);

int main()
{
    int n,x;
    cout<<"Enter size of array: "<<endl;
    cin >> n;
    int arr[n];
    cout<<"Enter Array value in sorted order only: "<<endl;

    cin>>arr[0];
    for(int i=1;i<n;i++)
    {
        cin>>arr[i];

        if(arr[i-1]>arr[i])
        {
            cout<<endl<<"Invalid array!!!";
            return 0;
        }
    }

    cout<<"Enter key to check its frequency: "<<endl;
    cin>>x;

    int last = lastOccurrence(arr,0,n-1,x);
    int first = firstOccurrence(arr,0,n-1,x);
    int freq = last - first + 1;

    cout<<endl<<"First occurrence =  "<<first;
    cout<<endl<<"Last occurrence =  "<<last;
    cout<<endl<<endl<<"Frequency of "<<x<<" = "<<freq;
    return 0;

}


int firstOccurrence(int arr[],int low,int high,int x)
{
    if(low == high)
        return (arr[low]==x)?low:-1;

    int mid=(low+high)/2;

    if(arr[mid]==x)
    {
        if(mid==0 || arr[mid-1]!=x)                 //mid=0 is to check boundary case of index=0 so that arr[mid-1] does not go out of index bounds
            return mid;
        else
            return firstOccurrence(arr,low,mid-1,x);
    }


    else if(arr[mid]<x)
        return firstOccurrence(arr,mid+1,high,x);

    else
        return firstOccurrence(arr,low,mid-1,x);

}


int lastOccurrence(int arr[],int low,int high,int x)
{
    if(low==high)
        return (arr[low]==x)?low:-1;

    int mid=(low+high)/2;

    if(arr[mid]==x)
    {
        if((mid==(sizeof(arr)/sizeof(arr[0])-1)) || arr[mid+1]!=x)
            return mid;

        else
            return lastOccurrence(arr,mid+1,high,x);
    }

    else if(arr[mid]<x)
        return lastOccurrence(arr,mid+1,high,x);

    else
        return lastOccurrence(arr,low,mid-1,x);

}
