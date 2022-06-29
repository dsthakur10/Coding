// Search in Rotated Sorted Array

// Method-1 :
// Find the pivot from where the rotation is done. pivot --> index of minimum element in rotated array.
// If target <= nums[pivot] --> search target in right half
// Else, search in left half

int search(vector<int>& nums, int target)
{
    int pivot = findRotation(nums);

    if(target < nums[pivot])
        return -1;

    if(target <= nums[nums.size()-1])
        return binarySearch(nums, target, pivot, nums.size()-1);

    else
        return binarySearch(nums, target, 0, pivot-1);
}


int findRotation(vector<int>& nums)
{
    int low = 0, high = nums.size()-1;

    if(nums[low] <= nums[high])
        return low;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(mid != 0 && nums[mid-1] > nums[mid])
            return mid;

        if(mid != nums.size()-1 && nums[mid] > nums[mid+1])
            return mid+1;

        if(nums[low] < nums[mid])
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}


int binarySearch(vector<int>& nums, int target)
{
    int low = 0, high = nums.size()-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target)
            return mid;

        else if(nums[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}



// Method-2 --> Direct search without finding pivot

int search(vector<int>& nums, int target)
{
    int low = 0, high = nums.size()-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(nums[mid] == target)
            return mid;

        if(nums[low] <= nums[mid])      // Answer came FALSE if '=' sign is not placed. --> [3, 1]
        {
            if(nums[mid] < target)
                low = mid+1;

            else
            {
                if(nums[low] <= target)
                    high = mid-1;
                else
                    low = mid+1;
            }
        }

        else
        {
            if(nums[mid] > target)
                high = mid-1;

            else
            {
                if(nums[high] >= target)
                    low = mid+1;
                else
                    high = mid-1;
            }
        }

    }

    return -1;
}
