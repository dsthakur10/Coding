#include<iostream>
using namespace std;

int getMedian(int arr[],int n);
float median(int A[],int B[],int n);

int main()
{
    int n;
    cout<<"Enter Size:"<<endl;
    cin>>n;
    int A[n],B[n];

    cout<<endl<<"Enter ARRAY1: ";
    for(int i=0;i<n;i++)
        cin>>A[i];

    cout<<endl<<"Enter ARRAY2: ";
    for(int i=0;i<n;i++)
        cin>>B[i];


    float med = median(A,B,n);

    cout<<endl<<"MEDIAN = "<<med;
    return 0;
}


int getMedian(int arr[],int n)
{
    int k = n/2;
    if(n%2==0)
        return ((arr[k-1] + arr[k])/2);

    else
        return arr[k];

}



float median(int A[],int B[],int n)
{
    if(n==1)
        return ((A[0]+B[0])/2.0);

    else if(n==2)
    {
        int k1,k2;
        k1 = A[0]>B[0]?A[0]:B[0];

        k2 = A[1]>B[1]?B[1]:A[1];

        return ((k1+k2)/2.0);
    }

    else
    {
        int m1,m2;

        m1 = getMedian(A,n);
        m2 = getMedian(B,n);

        if(m1 == m2)
            return m1;

        else if(m1 < m2)
        {
            if(n%2!=0)
                return median(A + n/2,B,n/2+1);             //odd sized array
            else
                return median(A + n/2 - 1,B,n/2+1);         //even sized array

        }


        else
        {
            if(n%2!=0)
                return median(A,B + n/2,n/2+1);
            else
                return median(A,B + n/2 - 1,n/2+1);

        }

    }
}
