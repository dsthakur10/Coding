
// Count of Smaller Numbers After Self

/*
You are given an integer array nums and you have to return a new counts array.
The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].

Example 1:
Input: nums = [5,2,6,1]
Output: [2,1,1,0]
Explanation:
To the right of 5 there are 2 smaller elements (2 and 1).
To the right of 2 there is only 1 smaller element (1).
To the right of 6 there is 1 smaller element (1).
To the right of 1 there is 0 smaller element.

Example 2:
Input: nums = [-1]
Output: [0]

Example 3:
Input: nums = [-1,-1]
Output: [0,0]

*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> countSmaller(vector<int>& nums);
void mergeSort(vector<pair<int, int>>& arr, int low, int high);
void mergeArrays(vector<pair<int, int>>& arr, int low, int mid, int high);


vector<int> counter;
int main()
{
    vector<int> nums = {38, 27, 43, 3, 100, 9, 82, -6};
    //vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
    //vector<int> nums = {38, 27};
    //vector<int> nums = {7};

    vector<int> temp = countSmaller(nums);

    for(int x : nums)
        cout << x << " ";

    cout << "\n";
    for(int x : temp)
        cout << x << " ";

}


// Modified Merge Sort --> Count inversions
// pair(i,j) is an inversion if nums[i] > nums[j] when i<j
// We are using vector of pairs instead of normal vector to keep track of original index of an element in array,
// because we want to return #inversions for each index 'i' in original array's order.


vector<int> countSmaller(vector<int>& nums) {

    counter = vector<int>(nums.size(), 0);    // countSmaller track
    vector<pair<int, int>> arr(nums.size());             // <element, index>

    for(int i=0; i<nums.size(); i++)
    {
        arr[i].first = nums[i];
        arr[i].second = i;
    }

    mergeSort(arr, 0, nums.size()-1);

    return counter;
}


void mergeSort(vector<pair<int, int>>& arr, int low, int high)
{
    if(low == high)
        return;

    int mid = low + (high-low)/2;

    mergeSort(arr, low, mid);
    mergeSort(arr, mid+1, high);

    mergeArrays(arr, low, mid, high);
}


void mergeArrays(vector<pair<int, int>>& arr, int low, int mid, int high)
{
    // mid is counted with left array

    int m = mid-low+1;
    int n = high-mid;

    vector<pair<int, int>> left(m);
    vector<pair<int, int>> right(n);

    for(int i=0; i<m; i++)
        left[i] = arr[low+i];

    for(int j=0; j<n; j++)
        right[j] = arr[mid+j+1];


    int i=0, j=0, k=low;

    int countLessThan = 0;
    while(i < m && j < n)
    {
        // inversion
        if(left[i].first > right[j].first)
        {
            arr[k] = right[j];
            j++;
            k++;

            countLessThan++;
        }

        else
        {
            counter[left[i].second] += countLessThan;

            arr[k] = left[i];
            i++;
            k++;
        }
    }

    // Elements on right-subarray finished --> Place all the remaining elements from left-subarray
    while(i < m)
    {
        counter[left[i].second] += countLessThan;

        arr[k] = left[i];
        k++;
        i++;
    }

    // Elements on left-subarray finished --> Place all the remaining elements from right-subarray
    while(j < n)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

