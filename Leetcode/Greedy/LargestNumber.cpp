#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

string largestNumber(vector<int>& nums);


bool mycomp(string a, string b){

    return (a+b > b+a);

}


int main()
{
    vector<int> myvec;
    int x,n;

    cout << "Enter vector length: ";
    cin >> n;

    cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        cin >> x;
        myvec.push_back(x);
    }

    string result = largestNumber(myvec);

    cout << "\n\nLargest Number = " << result;
}



string largestNumber(vector<int>& nums)
{
    vector<string> str;
    string temp;

    for(int x : nums)
    {
        temp = to_string(x);
        str.push_back(temp);
        temp.clear();
    }

    sort(str.begin(), str.end(), mycomp);

    if(str[0] == "0")
        return "0";

    for(int i=0; i<str.size(); i++)
    {
        cout << str[i] << " ";
        temp += str[i];
    }

    return temp;
}
