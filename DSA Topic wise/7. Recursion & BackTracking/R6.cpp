
// K-th symbol in grammar

/*
We build a table of n rows (1-indexed). We start by writing 0 in the 1st row.
Now in every subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each occurrence of 1 with 10.

For example, for n = 3,
the 1st row is 0,
the 2nd row is 01,
the 3rd row is 0110.

Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.

*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

int kthGrammar(int n, int k);

int main()
{
    int n = 30, k=434991989 ;

    int x = kthGrammar(n,k);

    cout << "Value = " << x;
}



// Method-1 --> Iterative --> Storing every ith iteration value in a string until nth iteration. --> OLE (OUTPUT LIMIT EXCEEDED)

int kthGrammar(int n, int k)
{
    string str;
    string temp="0";

    for(int i=1; i<n; i++)
    {
        //string str(2*temp.size(), '0');

        for(int j=0; j<temp.size(); j++)
            str += temp[j];

        for(int j=0; j<temp.size(); j++)
        {
            if(temp[j] == '0')
                str += '1';
            else
                str += '0';
        }

        temp = str;
        cout << temp << "\n";
        str.clear();
    }

    if(temp[k-1] == '0')
        return 0;

    else
        return 1;
}



// Method-2 --> Recursive solution

int kthGrammar2(int n, int k)
{
    if(n == 1)
        return 0;

    if(k%2 == 0)
        return (kthGrammar(n-1, k/2) == 0) ? 1 : 0;

    else
        return (kthGrammar(n-1, (k+1)/2) == 0) ? 0 : 1;
}



// Method-3 --> Recursive solution --> complement of first half

int kthGrammar3(int n, int k)
{
    if(n == 1)
        return 0;

    int mid = (int)pow(2,(n-2));

    if(k <= mid)
        return kthGrammar(n-1, k);

    else
        return !kthGrammar(n-1, k-mid);

}
