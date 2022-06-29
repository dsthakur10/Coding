// Search in Bitonic array

/*

Given a bitonic array, search the given element in array

*/


#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int findMaximum(vector<int> arr);
int binarySearch(vector<int>& nums, int key, int low, int high);
int reverseBinarySearch(vector<int>& nums, int key, int low, int high);
int searchInBitonic(vector<int> nums, int target);


int main()
{
    int n, x, target;
    vector<int> nums;

    cout << "\nEnter array length: ";
    cin >> n;

    cout << "\nEnter array elements:\n";
    for(int i=0; i<n; i++)
    {
        cin >> x;
        nums.push_back(x);
    }

    cout << "\nEnter target: ";
    cin >> target;

    cout << "\n\n Target found at index = " << searchInBitonic(nums, target);

    return 0;
}


int searchInBitonic(vector<int> nums, int target)
{
    int n = nums.size(), index=-1;

    if(n==1)
        return target == nums[0] ? 0 : -1;

    int bitonicPoint = findMaximum(nums);

    if(target > nums[bitonicPoint])
        return -1;

    if(target >= nums[0])
        index = binarySearch(nums, target, 0, bitonicPoint);

    if(index != -1)
        return index;

    if(target >= nums[n-1])
        index = reverseBinarySearch(nums, target, bitonicPoint+1, n-1);

    return index;
}



int findMaximum(vector<int> arr)
{
    int n = arr.size();
    if(n==1)
        return 0;

    if(arr[n-2] < arr[n-1])     // bitonic array is sorted array --> bitonic point is at the rightmost end
        return n-1;

    if(arr[0] > arr[1])         // bitonic array is reverse-sorted array --> bitonic point is at the leftmost end
        return 0;

    int low = 1, high = n-2;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(arr[mid-1] < arr[mid] && arr[mid] > arr[mid+1])
            return mid;

        else if(arr[mid-1] < arr[mid])
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}



int binarySearch(vector<int>& nums, int key, int low, int high)
{
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == key)
            return mid;

        else if(nums[mid] < key)
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}


int reverseBinarySearch(vector<int>& nums, int key, int low, int high)
{
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == key)
            return mid;

        else if(nums[mid] < key)
            high = mid-1;

        else
            low = mid+1;
    }

    return -1;
}
