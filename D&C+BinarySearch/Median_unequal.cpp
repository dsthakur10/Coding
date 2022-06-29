#include<iostream>
using namespace std;

float medianOfFour(int a,int b,int c,int d);
int getMedian(int arr[],int n);
float median(int A[],int B[],int m,int n);


int main()
{
    int m,n;
    cout<<"Enter Size1 (Smaller array):"<<endl;
    cin>>m;
    cout<<"Enter Size2: (Bigger array):"<<endl;
    cin>>n;

    if(m>n)
    {
        int k=m;
        m=n;
        n=k;
    }

    int A[m],B[n];

    cout<<endl<<"Enter ARRAY1: ";
    for(int i=0;i<m;i++)
        cin>>A[i];

    cout<<endl<<"Enter ARRAY2: ";
    for(int i=0;i<n;i++)
        cin>>B[i];


    float med = median(A,B,m,n);            // m < n

    cout<<endl<<"MEDIAN = "<<med;
    return 0;
}


float medianOfFour(int a,int b,int c,int d)
{
    float k;

    if(a<b)                                     // Level-1
    {
        if(b<c)                                     // Level-2
        {
            if(c<d)                                     // Level-3
                k = (b+c)/2.0;

            else                                        // Level-3
                k = (b + (a>d?a:d))/2.0;
        }

        else                                        // Level-2
        {
            if(c<d)                                     // Level-3
            {
                if(d<b)                                     // Level-4
                    k = (d + (a>c?a:c))/2.0;

                else                                        // Level-4
                    k = (b + (a>c?a:c))/2.0;
            }

            else                                        // Level-3
                k = (c + (a>d?a:d))/2.0;
        }
    }

    else                                        // Level-1
    {
        if(b<c)                                     // Level-2
        {
            if(c<d)                                     // Level-3
                k = (c + (a>d?d:a))/2.0;

            else                                        // Level-3
            {
                if(d<b)                                     // Level-4
                    k = (b + (a>c?c:a))/2.0;

                else                                        // Level-4
                    k = (d + (a>c?c:a))/2.0;
            }
        }

        else                                        // Level-2
        {
            if(c<d)                                     // Level-3
                k = (b + (a>d?d:a))/2.0;

            else                                        // Level-3
                k = (b+c)/2.0;
        }
    }

    return k;
}


int getMedian(int arr[],int n)
{
    int k = n/2;
    if(n%2==0)
        return ((arr[k-1] + arr[k])/2);

    else
        return arr[k];

}


float median(int A[],int B[],int m,int n)
{
    if(m==0)                                        // Smaller array size = 0
        return getMedian(B,n);


    else if(m==1)                                   // Smaller array size = 1
    {

        if(n==1)                                                // Bigger array size = 1
            return ((A[0] + B[0])/2.0);

        if(n%2==0)                                              // Bigger array size = even
        {
            int k;

            k = (A[0]<B[n/2 - 1])?B[n/2 - 1]:-1;

            if(k==-1)
                k = (A[0]<B[n/2])?A[0]:B[n/2];

            return k;
        }

        else                                                    // Bigger array size = odd
        {
            return medianOfFour(B[n/2 - 1],B[n/2],B[n/2 + 1],A[0]);
        }
    }


    else if(m==2)                                   // Smaller array size = 2
    {

        if(n==2)                                                // Bigger array size = 2
        {
            return medianOfFour(A[0],A[1],B[0],B[1]);
        }

        if(n%2==0)                                              // Bigger array size = even
        {
            int k;
            if(A[0]<A[1] && A[1]<B[n/2 - 1] && B[n/2 - 1]<B[n/2])
            {

                k = (A[1]>B[n/2 - 2])?A[1]:B[n/2 - 2];

                return (k + B[n/2 - 1])/2.0;
            }

            else if (B[n/2 - 1]<B[n/2] && B[n/2]<A[0] && A[0]<A[1])
            {

                k = (A[0]>B[n/2 + 1])?B[n/2 + 1]:A[0];

                return (k + B[n/2])/2.0;

            }

            else
            {
                return medianOfFour(B[n/2 - 1],B[n/2],A[0],A[1]);
            }

        }

        else                                                    // Bigger array size = odd
        {
            int k;

            if(A[1]<B[n/2])
                k = (A[1]>B[n/2 - 1])?A[1]:B[n/2 - 1];

            else if(A[0]>B[n/2])
                k = (A[0]>B[n/2 + 1])?B[n/2 + 1]:A[0];

            else
                k = B[n/2];

            return k;
        }
    }

    else
    {
        int m1,m2;
        m1 = (m-1)/2;
        m2 = (n-1)/2;

        if(A[m1]<=B[m2])
            return median(A+m1,B,m/2+1,n-m1);

        else
            return median(A,B+m2,m/2+1,n-m1);
    }

}
