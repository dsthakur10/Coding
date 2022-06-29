// There is an integer array nums sorted in ascending order (with DISTINCT values).

// Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array
// is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).

// For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

// Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

// NOTE: You must write an algorithm with O(logn) runtime complexity.


#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

int binarySearch(std::vector<int> arr,int low,int high,int target)
{
    int mid;

    while(low<=high)
    {
        mid = (low+high)/2;

        if(arr[mid] == target)
            return mid;

        else if(arr[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;

}


int solution1(std::vector<int>& nums, int target);                      // 2*O(logn) time - finding pivot & then searching target according to pivot value

int solution2(std::vector<int>& nums, int target);                      // O(logn) time -

int main()
{
    int target;
    //std::vector<int> myvec = {10,12,14,-4,-3,-2,0,1,2,4,6};
    //std::vector<int> myvec = {4,5,6,7,0,1,2};
    //std::vector<int> myvec = {1};
    //std::vector<int> myvec = {6,9};
    //std::vector<int> myvec = {3,1};
    std::vector<int> myvec = {3,4,5,1,2};

    for(int x:myvec)
        std::cout<<x<<" ";

    std::cout<<"\n\nEnter target:";
    std::cin>>target;

    std::cout<<"\n\nTarget "<<target<<" found at index = "<<solution2(myvec,target);

}


int solution1(std::vector<int>& nums, int target)
{
    if(nums.size() == 1)
        return (target==nums[0]?0:-1);

    if(nums[0]<nums[nums.size()-1])                             // if the array is already sorted & not rotated
        return binarySearch(nums,0,nums.size()-1,target);


    int pivot;

    int low = 0, high = nums.size() - 1;
    int mid;

    while(low <= high)                                           // locating pivot element where rotation occurred
    {
        mid = (low + high)/2;

        if(low == high && nums[low] < nums[low-1])
        {
            pivot = low;
            break;
        }

        else if(mid != nums.size()-1 && mid != 0 && nums[mid]<nums[mid-1] && nums[mid]<nums[mid+1])     // considering boundary cases as well
        {
            pivot = mid;
            break;
        }


        if(nums[mid]<nums[0])
            high = mid-1;

        else
            low = mid+1;
    }

    std::cout<<"\nPIVOT = "<<pivot;

    if(target < nums[pivot] || target > nums[pivot-1])
        return -1;


    if(target >= nums[0])
        return binarySearch(nums,0,pivot-1,target);

    else
        return binarySearch(nums,pivot,nums.size()-1,target);

}



int solution2(std::vector<int>& nums, int target)
{
/*  Let's say nums : [12, 13, 14, 15, 16, 17, 18, 19, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

    Because it's not fully sorted, we can't do normal binary search. But here comes the trick:

    If target is let's say 14, then we adjust nums to this, where "inf" means infinity:
    [12, 13, 14, 15, 16, 17, 18, 19, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf]

    If target is let's say 7, then we adjust nums to this:
    [-inf, -inf, -inf, -inf, -inf, -inf, -inf, -inf, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

    And then we can simply do ordinary binary search.

    Of course we don't actually adjust the whole array but instead adjust only on the fly only the elements we look at.
    And the ADJUSTMENT IS DONE BY COMPARING BOTH target AND actual element AGAINST nums[0].

*/

    if(nums.size() == 1)
        return (target==nums[0]?0:-1);

    int lo = 0, hi = nums.size()-1;

    while (lo <= hi)
    {
        int mid = (lo + hi) / 2;

        int x = (nums[mid] < nums[0]) == (target < nums[0])             // If nums[mid] and target are "ON THE SAME SIDE" of nums[0], we just take nums[mid].
                   ? nums[mid]                                          // Otherwise we use -infinity or +infinity as needed.
                   : (target < nums[0] ? INT_MIN : INT_MAX);

        if (x < target)
            lo = mid + 1;

        else if (x > target)
            hi = mid-1;

        else
            return mid;
    }

    return -1;

}
