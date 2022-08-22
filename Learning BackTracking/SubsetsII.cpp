
// Unique subsets

/*
Given an array arr[] of integers of size N that might contain duplicates, the task is to find all possible unique subsets.

NOTE: Each SUBSET should be SORTED.


EXAMPLE-1:
Input: N = 3, arr[] = {2,1,2}
Output:(),(1),(1 2),(1 2 2),(2),(2 2)
Explanation:
All possible subsets = (),(2),(1),(1,2),(2),(2,2),(2,1),(2,1,2)
After Sorting each subset = (),(2),(1),(1,2),(2),(2,2),(1,2),(1,2,2)
Unique Susbsets in Lexicographical order = (),(1),(1,2),(1,2,2),(2),(2,2)

EXAMPLE-2:
Input: N = 4, arr[] = {1,2,3,3}
Output: (),(1),(1 2),(1 2 3),(1 2 3 3),(1 3),(1 3 3),(2),(2 3),(2 3 3),(3),(3 3)

*/

#include<iostream>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

void addSubset(vector<int> input, vector<int> output, set<vector<int>>& result)
{
    if(input.empty())
    {
        sort(output.begin(), output.end());
        result.insert(output);
        return;
    }

    int x = input[0];
    input.erase(input.begin());

    addSubset(input, output, result);
    output.push_back(x);
    addSubset(input, output, result);
}


//Function to find all possible unique subsets.
vector<vector<int> > AllSubsets(vector<int> arr, int n)
{
     set<vector<int>> result;
     vector<vector<int>> myvec;
     vector<int> output;

     addSubset(arr, output, result);

     for(auto it = result.begin(); it!=result.end(); it++)
     {
         myvec.push_back(*it);
     }

     return myvec;
}


int main()
{
    //vector<int> arr = {2,1,2};
    vector<int> arr = {3,2,1,3};
    vector<vector<int>> result = AllSubsets(arr,arr.size());

    cout << "Unique elements subsets:\n";

    for(int i=0; i<result.size(); i++)
    {
        for(int j=0; j<result[i].size(); j++)
            cout << result[i][j] << " ";

        cout << "\n";
    }

}



