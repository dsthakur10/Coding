// Find Peak element

/*

A peak element is an element that is strictly greater than its neighbors.

Given an integer array nums, find a peak element, and return its index. If the array contains multiple peaks,
return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞.

You must write an algorithm that runs in O(log n) time.

-2^31 <= nums[i] <= 2^31 - 1
nums[i] != nums[i + 1] for all valid i.

*/


// Method-1 --> fails since input may contain INT_MAX && INT_MIN

int findPeakElement(vector<int>& nums) {
    int n = nums.size();
    int low = 0, high = n-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;
        int prev = mid == 0 ? INT_MIN : nums[mid-1];
        int next = mid == n-1 ? INT_MIN : nums[mid+1];


        if(prev < nums[mid] && nums[mid] > next)
            return mid;

        else if(prev > nums[mid] && nums[mid] > next)
            high = mid-1;

        else
            low = mid+1;
    }

    return low;
}


// Method-2

int findPeakElement2(vector<int>& nums) {
    int n = nums.size();
    int low = 0, high = n-1;

    if(nums.size() == 1)
        return 0;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        // handles the case of 2-length array
        if(mid == 0)
            return nums[mid] > nums[mid+1] ? 0 : 1;

        else if(mid == n-1)
            return nums[mid-1] > nums[mid] ? mid-1 : mid;

        else if(nums[mid-1] < nums[mid] && nums[mid] > nums[mid+1])     // peak element (local maxima)
            return mid;

        else if(nums[mid-1] > nums[mid] && nums[mid] > nums[mid+1])
            high = mid-1;

        else
            low = mid+1;
    }

    return -1;
}



// Method-3
int findPeakElement3(vector<int>& nums) {
    int n = nums.size();

    if(nums.size() == 1)
        return 0;

    // handles corner cases + 2-length subarray
    if(nums[0] > nums[1])
        return 0;

    if(nums[n-2] < nums[n-1])
        return n-1;

    int low = 1, high = n-2;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid-1] < nums[mid] && nums[mid] > nums[mid+1])
            return mid;

        else if(nums[mid-1] > nums[mid])
            high = mid-1;

        else
            low = mid+1;
    }

    return -1;
}
