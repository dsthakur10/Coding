// DIVIDE AND CONQUER

#include<iostream>
#include<string>
using namespace std;

string longestCommonPrefix(string str[],int low,int high);
string findPrefix(string str1,string str2);

int main()
{
    int n;
    cout<<"Enter number of strings: "<<endl;
    cin>>n;

    string str[n];

    cout<<"Enter strings:"<<endl;
    for(int i=0;i<n;i++)
        cin>>str[i];

    cout<<endl<<"THE STRINGS: ";
    for(int i=0;i<n;i++)
        cout<<str[i]<<" ";

    string lcp = longestCommonPrefix(str,0,n-1);

    cout<<endl<<"LONGEST COMMMON PREFIX: ";
    if(lcp.empty())
        cout<<"NULL";
    else
        cout<<lcp;

    return 0;
}


string longestCommonPrefix(string str[],int low,int high)
{
    if(low == high)
        return str[low];

    int mid = (low + high)/2;

    string s1 = longestCommonPrefix(str,low,mid);
    string s2 = longestCommonPrefix(str,mid+1,high);

    string prefix = findPrefix(s1,s2);
    return prefix;
}


string findPrefix(string str1,string str2)
{
    int k = (str1.length()<=str2.length())?str1.length():str2.length();
    int counter=0;

    for(int i=0;i<k;i++)
    {
        if(str1[i]!=str2[i])
            break;
        counter++;
    }

    string prefixOfTwo = str1.substr(0,counter);
    return prefixOfTwo;
}
