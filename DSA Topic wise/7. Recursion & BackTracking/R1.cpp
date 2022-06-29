
// Sort an array (recursively)

#include<iostream>
#include<vector>
using namespace std;

vector<int> sortArray(vector<int> arr);
vector<int> insertArray(vector<int> arr, int x);


int main()
{
    //vector<int> vec = {2,3,7,6,4,5,9};
    //vector<int> vec = {100, 70, 60, 20, 1};
    //vector<int> vec = {1, 5, 7, 9, 24};
    //vector<int> vec = {1};
    //vector<int> vec = {};
    vector<int> vec = {20, 40, 10, 77, 33, 88, 66};
    //vector<int> vec = {2,2,2,3,2,2};

    cout << "Sorted array = ";

    vec = sortArray(vec);

    for(int i=0; i<vec.size(); i++)
        cout << vec[i] << " ";

    return 0;
}



vector<int> sortArray(vector<int> arr)
{
    if(arr.size() == 0 || arr.size() == 1)             // base condition
        return arr;

    int x = arr.back();
    arr.pop_back();

    arr = sortArray(arr);           // hypothesis

    arr = insertArray(arr, x);      // induction

    return arr;
}


vector<int> insertArray(vector<int> arr, int x)
{
    if(arr.size() == 0 || arr[arr.size()-1] <= x)             // base condition
        arr.push_back(x);

    else                                   // induction
    {
        int y = arr.back();
        arr.pop_back();

        arr = insertArray(arr, x);          // hypothesis

        arr.push_back(y);
    }

    return arr;
}
