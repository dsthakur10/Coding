// Number of rotations in rotated sorted array.


int findRotations(vector<int>& nums)
{
    int n = nums.size();
    int low = 0, high = n-1;

    if(nums[0] <= nums[n-1])
        return 0;

    while(low <= high)
    {
        int mid = low + (high - low)/2;

        // Ordering of checks is important
        // consider case of [3, 1]  --> mid-1 = -1 & function will cause ArrayIndexOutOfBound error.
        // We will perform check 1. before check 2. to ensure proper working as mid+1 never goes out of bounds
        // This is because of the working of division operator in C++ --> truncation always occur as floor.

        if(nums[mid] > nums[mid+1]) // 1.
            return mid+1;

        if(nums[mid-1] > nums[mid]) // 2.
            return mid;

        if(nums[low] < nums[mid])
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}



int findRotations2(vector<int>& nums)
{
    int n = nums.size();
    int low = 0, high = n-1;

    if(nums[0] <= nums[n-1])
        return 0;

    while(low <= high)
    {
        int mid = low + (high - low)/2;

        // No ordering required as we have added another condition to perform check for out of bounds errors.

        if(mid != 0 && nums[mid-1] > nums[mid])
            return mid;

        if(mid != n-1 && nums[mid] > nums[mid+1])
            return mid+1;

        if(nums[low] < nums[mid])
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}



int findRotations3(vector<int>& nums)
{
    int n = nums.size();
    int low = 0, high = n-1;

    if(nums[0] <= nums[n-1])
        return 0;

    while(low <= high)
    {
        int mid = low + (high - low)/2;
        int prev = (mid + n - 1) % n;
        int next = (mid + 1) % n;

        if(nums[mid] <= nums[prev] && nums[mid] <= nums[next])
            return mid;

        else if(nums[mid] <= nums[high])
            high = mid - 1;

        else if(nums[low] <= nums[mid])
            low = mid + 1;
    }

    return -1;
}
