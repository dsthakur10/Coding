/*
Convert given decimal number to binary
*/

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int decimal= 585;
    string binary;

    int rem;
    while(decimal > 0)
    {
        rem = decimal%2;
        decimal /= 2;
        binary += to_string(rem);
    }

    cout << binary;
}
