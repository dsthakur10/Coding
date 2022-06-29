// Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

// If target is not found in the array, return [-1, -1].

// NOTE: You must write an algorithm with O(logn) runtime complexity.


#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>


std::vector<int> solution1(std::vector<int>& nums, int target);             // 2*O(logn) - finding first & last occurrence separately.

std::vector<int> solution2(std::vector<int>& nums, int target);             // O(logn) + O(n) - finding first & then incrementing until nums[i] != target

std::vector<int> solution3(std::vector<int>& nums, int target);

int main()
{
    //std::vector<int> myvec = {-4,-2,-2,0,1,1,4,8,8,8,8,20,50,88,88};
    std::vector<int> myvec = {3,3,3,3,3,3,3,3};
    //std::vector<int> myvec = {1,2,3};
    //std::vector<int> myvec = {6,9,9};
    //std::vector<int> myvec = {1};

    std::vector<int> FL;
    int target;

    for(int x:myvec)
        std::cout<<x<<" ";

    std::cout<<"\n\nEnter target value: ";
    std::cin>>target;

    FL = solution2(myvec,target);

    std::cout<<"\n\nFIRST occurrence of "<<target<<" = "<<FL[0];
    std::cout<<"\n\nLAST occurrence of "<<target<<" = "<<FL[1];

}


std::vector<int> solution1(std::vector<int>& nums, int target)
{
    int low,high,mid,first=-1,last=-1;

    low = 0, high = nums.size()-1;
    while(low<=high)                                    // first occurrence
    {
        mid = (low+high)/2;

        if(nums[mid]==target)
        {
            if(mid == 0 || (mid != 0 && nums[mid-1]<nums[mid]))
            {
                first = mid;
                break;
            }

            else if(nums[mid-1] == nums[mid])
                high = mid-1;

        }

        else if(nums[mid] < target)
            low = mid+1;

        else if(nums[mid] > target)
            high = mid-1;
    }

    if(first == -1)
        return {-1,-1};

    low = 0, high = nums.size()-1;
    while(low<=high)                                    // last occurrence
    {
        mid = (low+high)/2;

        if(nums[mid]==target)
        {
            if(mid == nums.size()-1 || (mid != nums.size()-1 && nums[mid+1]>nums[mid]))
            {
                last = mid;
                break;
            }

            else if(nums[mid+1] == nums[mid])
                low = mid+1;

        }

        else if(nums[mid] < target)
            low = mid+1;

        else if(nums[mid] > target)
            high = mid-1;
    }

    return {first,last};
}


std::vector<int> solution2(std::vector<int>& nums, int target)
{
    int low,high,mid,first=-1,last=-1;

    low = 0, high = nums.size()-1;
    while(low<=high)                                    // first occurrence
    {
        mid = (low+high)/2;

        if(nums[mid]==target)
        {
            if(mid == 0 || (mid != 0 && nums[mid-1]<nums[mid]))
            {
                first = mid;
                break;
            }

            else if(nums[mid-1] == nums[mid])
                high = mid-1;

        }

        else if(nums[mid] < target)
            low = mid+1;

        else if(nums[mid] > target)
            high = mid-1;
    }

    if(first == -1)
        return {-1,-1};

    last=first;
    while(last < nums.size()-1 && nums[last+1] == target)
        last++;

    return {first,last};
}
