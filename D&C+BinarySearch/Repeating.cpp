//Given a sorted array of n elements containing elements in range from 1 to n-1 i.e. one element occurs twice, the task is to find the repeating element in an array.


#include<iostream>
using namespace std;


int repeating(int arr[],int low,int high);

int main()
{
    int n;
    cout<<"Enter size:"<<endl;
    cin>>
    n;

    int arr[n];

    cout<<"Enter array elements (1-"<<n-1<<") range:"<<endl;

    for(int i=0;i<n;i++)
    {
        cin>>arr[i];

        if(arr[i]>=n)
        {
            cout<<"Invalid array!!!";
            return 0;
        }
    }

    cout<<"Your array: "<<endl;

    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";

    cout<<"Repeated element = "<<repeating(arr,0,n-1);

    return 0;
}


int repeating(int arr[],int low,int high)
{
    int mid=(low+high)/2;

    if(arr[mid]==arr[mid-1] || arr[mid]==arr[mid+1])
        return arr[mid];

    if(arr[mid]==mid)
        return repeating(arr,low,mid-1);
    else
        return repeating(arr,mid+1,high);
}
