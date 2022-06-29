#include<iostream>
using namespace std;

int fixedPoint(int arr[],int low,int high);

int main()
{
    int n,result;
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

    result = fixedPoint(arr,0,n-1);

    cout<<"Fixed Point at index = "<<result;

    return 0;
}


int fixedPoint(int arr[],int low,int high)
{
    if(low==high)
        return (arr[low]==low)?low:-1;


    int mid = (low+high)/2;

    if(arr[mid]==mid)
        return mid;

    else if(arr[mid]<mid)
        return fixedPoint(arr,mid+1,high);

    else
        return fixedPoint(arr,low,mid-1);


}
