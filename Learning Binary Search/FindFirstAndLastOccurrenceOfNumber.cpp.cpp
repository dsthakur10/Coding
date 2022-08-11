// Find first & last occurrence of an element

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<unordered_map>
#include<climits>

using namespace std;

vector<int> searchRange(vector<int>& nums, int target);
int searchFirstOccurrence(vector<int>& nums, int target, int low, int high);
int searchLastOccurrence(vector<int>& nums, int target, int low, int high);

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

    vector<int> range = searchRange(nums, key);

    cout << "\n\n";
    for(int x: nums)
        cout << x << " ";
    cout << "\nRange of occurrences of key " << key << " = [" << range[0] << " ," << range[1] << "]" ;
}


vector<int> searchRange(vector<int>& nums, int target)
{
    int first = searchFirstOccurrence(nums, target, 0, nums.size()-1);

    if(first == -1)
        return {-1,-1};

    int last = searchLastOccurrence(nums, target, 0, nums.size()-1);

    return {first, last};
}


int searchFirstOccurrence(vector<int>& nums, int target, int low, int high)
{
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target && (mid == 0 || nums[mid-1] < target))
            return mid;

        else if(nums[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }
    return -1;
}


int searchLastOccurrence(vector<int>& nums, int target, int low, int high)
{
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target && (mid == nums.size()-1 || nums[mid+1] > target))
            return mid;

        else if(nums[mid] <= target)
            low = mid+1;

        else
            high = mid-1;
    }
    return -1;
}



vector<int> searchRange2(vector<int>& nums, int target) {

    int first = searchFirstOccurrence(nums, target, 0, nums.size()-1);

    if(first == -1)
        return {-1,-1};

    int last = searchLastOccurrence(nums, target, 0, nums.size()-1);

    return {first, last};

}


int searchFirstOccurrence2(vector<int>& nums, int target,
                          int low, int high)
{
    int firstIndex = -1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target)
        {
            firstIndex = mid;
            high = mid - 1;
        }

        else if(nums[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return firstIndex;
}


int searchLastOccurrence2(vector<int>& nums, int target,
                          int low, int high)
{
    int lastIndex = -1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target)
        {
            lastIndex = mid;
            low = mid+1;
        }

        else if(nums[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return lastIndex;
}
