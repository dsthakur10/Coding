// A sorted array is rotated at some unknown point. Find the minimum element in it.

#include<iostream>
using namespace std;

int minimumRotatedArray(int arr[],int low,int high);

int main()
{
    int n;
    cout<<"Enter size: ";
    cin>>n;

    int arr[n];
    cout<<"Enter Array elements: "<<endl;
    for(int i=0;i<n;i++)
        cin>>arr[i];

    cout<<endl<<"Your array: "<<endl;

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    cout<<endl<<"Minimum element in Rotated array = "<<minimumRotatedArray(arr,0,n-1);
    return 0;

}


int minimumRotatedArray(int arr[],int low,int high)
{
    if(arr[low]<=arr[high])                                        // this condition is touched when array is already sorted
        return arr[low];

    int mid = (low + high)/2;

    if(mid<high && arr[mid]>arr[mid+1])                 //mid<high is messiah for boundary cases that helps to not get array out of bounds
        return arr[mid+1];

    if(low<mid && arr[mid-1]>arr[mid])                  //low<mid same as above
        return arr[mid];

    if(arr[low]<arr[mid])
        return minimumRotatedArray(arr,mid+1,high);
    else
        return minimumRotatedArray(arr,low,mid-1);
}
