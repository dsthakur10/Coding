//To find if a given integer x appears more than n/2 times in a sorted array of n integers.


#include<iostream>
using namespace std;

int firstOccurence(int arr[],int low,int high,int x);

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

    cout<<"Enter key to check majority: "<<endl;
    cin>>x;

    int i = firstOccurence(arr,0,n-1,x);

    int j = i+n/2;
    if(arr[j]==x)
        cout<<endl<<x<<" is MAJOR ELEMENT";

    else
        cout<<endl<<"FUCK OFFFFF";

    return 0;
}


int firstOccurence(int arr[],int low,int high,int x)
{
    if(low == high)
        return (arr[low]==x)?low:-1;

    int mid=(low+high)/2;

    if(arr[mid]==x)
    {
        if(mid==0 || arr[mid-1]!=x)                 //mid=0 is to check boundary case of index=0 so that arr[mid-1] does not go out of index bounds
            return mid;
        else
            return firstOccurence(arr,low,mid-1,x);
    }


    else if(arr[mid]<x)
        return firstOccurence(arr,mid+1,high,x);

    else
        return firstOccurence(arr,low,mid-1,x);

}
