// Search in an almost sorted array

/*
Given an array which is sorted, but after sorting some elements are moved to either of the adjacent positions,
i.e., "arr[i] may be present at arr[i+1] or arr[i-1]". Search an element in this array.
Basically the element arr[i] can only be swapped with either arr[i+1] or arr[i-1].

For example consider the array {2, 3, 10, 4, 40}, 4 is moved to next position and 10 is moved to previous position.

Example :
Input: arr[] =  {10, 3, 40, 20, 50, 80, 70}, key = 40
Output: 2

Input: arr[] =  {10, 3, 40, 20, 50, 80, 70}, key = 90
Output: -1

*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<climits>

using namespace std;

int searchInAlmostSorted(vector<int>& nums, int target);
int searchInAlmostSorted2(vector<int>& nums, int target);

int main()
{
    vector<int> nums;
    int n, x, key;

    cout << "Enter size of array: ";
    cin >> n;

    cout << "\n Enter elements in almost sorted order:\n";
    for(int i=0; i<n; i++)
    {
        cin >> x;
        nums.push_back(x);
    }

    cout << "\n\nEnter key to search : ";
    cin >> key;

    int index = searchInAlmostSorted2(nums, key);

    cout << "\nIndex of given key " << key << " = " << index;
    return 0;
}



int searchInAlmostSorted(vector<int>& nums, int target)
{
    int low = 0, high = nums.size()-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        cout << mid << " ";
        if(nums[mid] == target)
            return mid;

        else if(mid != 0 && nums[mid-1] > nums[mid])
        {
            if(nums[mid-1] == target)
                return mid-1;

            else if(nums[mid-1] < target)
                low = mid+1;

            else
                high = mid-1;
        }

        else if(mid != nums.size()-1 && nums[mid] > nums[mid+1])
        {
            if(nums[mid+1] == target)
                return mid+1;

            else if(nums[mid+1] < target)
                low = mid+1;

            else
                high = mid-1;
        }

        else if(nums[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}


// Method-2

int searchInAlmostSorted(vector<int>& nums, int target)
{
    int low = 0, high = nums.size()-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        cout << mid << " ";
        if(nums[mid] == target)
            return mid;

        else if(mid != 0 && nums[mid-1] == target)
            return mid-1;

        else if(mid != nums.size()-1 && nums[mid+1] == target)
            return mid+1;

        else if(nums[mid] < target)
            low = mid+2;

        else
            high = mid-2;
    }
    return -1;
}
