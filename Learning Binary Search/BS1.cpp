// Binary Search on reverse sorted array (Descending array)

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<climits>

using namespace std;

int searchInReverseSorted(vector<int>& nums, int key, int low, int high);

int main()
{
    vector<int> nums;
    int n, x, key;

    cout << "Enter size of array: ";
    cin >> n;

    cout << "\n Enter elements in reverse sorted order:\n";
    for(int i=0; i<n; i++)
    {
        cin >> x;
        nums.push_back(x);
    }

    cout << "\n\nEnter key to search : ";
    cin >> key;

    int index = searchInReverseSorted(nums, key, 0, n-1);

    cout << "\n\n";
    for(int x: nums)
        cout << x << " ";
    cout << "\nIndex of key " << key << " is found at " << index;
}



int searchInReverseSorted(vector<int>& nums, int key, int low, int high)
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
