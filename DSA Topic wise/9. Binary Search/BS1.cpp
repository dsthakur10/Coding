
// Median of 2 sorted array with equal size

#include<iostream>
#include<vector>
using namespace std;

int getMedian(vector<int> arr,int low, int high);
float median(vector<int> A,vector<int> B,int lowA, int highA, int lowB, int highB);

int main()
{
    vector<int> A = {1, 12, 15, 26, 38};
    vector<int> B = {2, 13, 17, 30, 45};

    int n = A.size();
    float med = median(A, B, 0, n-1, 0, n-1);

    cout<<endl<<"MEDIAN = "<<med;
    return 0;
}


int getMedian(vector<int> arr,int low, int high)
{
    int n = high-low+1;
    int k = n/2;
    if(n%2==0)
        return ((arr[low+k-1] + arr[low+k])/2);

    else
        return arr[low+k];
}



float median(vector<int> A,vector<int> B,int lowA, int highA, int lowB, int highB)
{
    cout << "\nA --> " << lowA << " " << highA;
    cout << "\nB --> " << lowB << " " << highB;

    int n = highA - lowA + 1;
    int m = highB - lowB + 1;

    if(n==1)
        return ((A[lowA]+B[lowB])/2.0);

    else if(n==2)
    {
        cout << "\n\n Base condition";
        int k1,k2;
        k1 = A[lowA]>B[lowB]?A[lowA]:B[lowB];

        k2 = A[highA]>B[highB]?B[highB]:A[highA];

        cout << "\nk1 = " << k1;
        cout << "\nk2 = " << k2;
        return ((k1+k2)/2.0);
    }

    else
    {
        int m1,m2;

        m1 = getMedian(A, lowA, highA);
        m2 = getMedian(B, lowB, highB);

        cout << "\nm1 = " << m1;
        cout << "\nm2 = " << m2;
        if(m1 == m2)
            return m1;

        else if(m1 < m2)
        {
            if(n%2!=0)
                return median(A, B, lowA + n/2, highA, lowB, lowB + n/2);             //odd sized array
            else
                return median(A, B, lowA + n/2 - 1, highA, lowB, lowB + n/2);         //even sized array
        }

        else
        {
            if(n%2!=0)
                return median(A, B, lowA, lowA + n/2, lowB + n/2, highB);             //odd sized array
            else
                return median(A, B, lowA, lowA + n/2, lowB + n/2 - 1, highB);         //even sized array
        }
    }
}
