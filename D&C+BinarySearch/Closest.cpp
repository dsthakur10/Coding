#include<iostream>
#include <cstdlib>
using namespace std;

int closest(int arr[],int low,int high,int target);

int main()
{
    int n,target,result;
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

    cout<<endl<<"Enter Target value to find CLOSEST(Target): "<<endl;
    cin>>target;

    if(target <= arr[0])
        result = arr[0];
    else if(target >= arr[n-1])
        result = arr[n-1];

    else
        result = closest(arr,0,n-1,target);

    cout<<endl<<"Closest to target "<<target<<" = "<<result;

    return 0;
}


int closest(int arr[],int low,int high,int target)
{
    int mid = (low+high)/2;

    if(arr[mid]==target)                                    // return mid if target = mid
        return arr[mid];

    if(target<arr[mid] && target>=arr[mid-1])               //checking if mid & left(mid) are candidates for target
    {
        int d1 = abs(target - arr[mid]);
        int d2 = abs(target - arr[mid-1]);

        return (d1<d2)?arr[mid]:arr[mid-1];
    }

    if(target<arr[mid+1] && target>=arr[mid])               //checking if mid & right(mid) are candidates for target
    {
        int d1 = abs(target - arr[mid+1]);
        int d2 = abs(target - arr[mid]);

        return (d1<d2)?arr[mid+1]:arr[mid];
    }

    if(target<arr[mid])
        return closest(arr,low,mid-1,target);

    else
        return closest(arr,mid+1,high,target);
}
