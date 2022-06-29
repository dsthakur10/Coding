
// No duplicates here

// Comparison must not be made with target & mid initially because here sorted array is rotated.
// Either of left or right half of array will always be in sorted form.

// If LEFT half is in sorted form (arr[low] <= arr[mid])
//      (1) check if target lies in the range of [low, mid) --> YES --> high = mid-1 --> search in left half
//      (2) --> NO --> low = mid+1 --> search in right half

// If RIGHT half is in sorted form (arr[low] > arr[mid])
//      (1) check if target lies in the range of (mid, mid] --> YES --> low = mid+1 --> search in right half
//      (2) --> NO --> high = mid-1 --> search in left half



int search(vector<int>& nums, int target) {

    int low = 0, high = nums.size()-1;
    int mid;

    while(low <= high)
    {
        mid = (low + high)/2;

        if(nums[mid] == target)
            return mid;

        else if(nums[low] <= nums[mid])                         // left half is sorted
        {
            if(nums[low] <= target && nums[mid] > target)               // target lies in left half
                high = mid-1;

            else                                                        // target greater than mid
                low = mid+1;
        }

        else                                                    // right half is sorted
        {
            if(nums[mid] < target && nums[high] >=target)               // target lies in right half
                low = mid+1;

            else                                                        // target smaller than mid
                high = mid-1;
        }

    }

    return -1;
}
