#include<iostream>
using namespace std;

void peak(int arr[],int low,int high);

int main()
{
    int n;
    cout<<"Enter size of array: "<<endl;
    cin >> n;
    int arr[n];
    cout<<"Enter Array value: "<<endl;

    for(int i=0;i<n;i++)
        cin>>arr[i];

    peak(arr,0,n-1);
}


void peak(int arr[],int low,int high)
{
    if(low==high)
        return 0;

    int mid=(low+high)/2;

    if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1])
    {
        cout<<arr[mid]<<" ";
        peak()
    }

}
