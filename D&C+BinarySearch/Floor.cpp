#include<iostream>
using namespace std;

int floor(int arr[],int low,int high,int x);

int main()
{
    int n,x;
    cout<<"Enter size of array: "<<endl;
    cin >> n;
    int arr[n];
    cout<<"Enter Array value in sorted order only: ";

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

    cout<<endl<<"Enter X value to find FLOOR(X): "<<endl;
    cin>>x;

    int result = floor(arr,0,n-1,x);

    if(result != -1)
        cout<<endl<<"FLOOR("<<x<<") = "<<result;

    else
        cout<<endl<<"FLOOR("<<x<<") DOES NOT EXIST ";

    return 0;
 }


 int floor(int arr[],int low,int high,int x)
 {
     if(low == high)
     {
         if(arr[low]<=x)
            return arr[low];

         else
            return -1;
     }

     int mid = (low+high)/2;

     if(arr[mid] == x)
        return arr[mid];

     if(arr[mid]<x && arr[mid+1]>x)
        return arr[mid];

     if(x<arr[mid])
        return floor(arr,low,mid-1,x);

     else
        return floor(arr,mid+1,high,x);

 }
