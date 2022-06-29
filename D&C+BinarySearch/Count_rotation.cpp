//The array has been rotated (clockwise) k number of times. Given such an array, find the value of k.

#include<iostream>
using namespace std;


int countRotation(int arr[],int low,int high);

int main()
{
    int n;
    cout<<"Enter size: ";
    cin>>n;

    int arr[n];
    cout<<"Enter Array elements: "<<endl;
    for(int i=0;i<n;i++)
        cin>>arr[i];

    cout<<"Your array: "<<endl;

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    int k = countRotation(arr,0,n-1);
    cout<<endl<<"Array is rotated "<<k<< " times";

    return 0;
}


int countRotation(int arr[],int low,int high)
{
    if(low>high)                                        // this condition is touched when array is already sorted
        return 0;

    if(low == high)
        return low;

    int mid = (low + high)/2;

    //mid<high is messiah for boundary cases that helps to not get array out of bounds

    if(mid<high && arr[mid]>arr[mid+1])
        return mid+1;

    //low<mid same as above

    if(low<mid && arr[mid-1]>arr[mid])
        return mid;

    if(arr[low]<arr[mid])
        return countRotation(arr,mid+1,high);
    else
        return countRotation(arr,low,mid-1);

}
