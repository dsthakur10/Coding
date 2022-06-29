// Floor of an element

/*
Given a sorted array arr[] of size N without duplicates, and given a value x.
Floor of x is defined as the largest element K in arr[] such that K is smaller than or equal to x.
Find the index of floor[x].

*/

int findFloor(vector<long long> nums, long long n, long long x)
{
    long long low = 0, high = n-1;

    if(nums[n-1] <= x)
        return n-1;

    if(nums[0] > x)
            return -1;

    while(low <= high)
    {
        long long mid = low + (high-low)/2;

        if(mid != n-1 && nums[mid] <= x && nums[mid+1] > x)
            return mid;

        else if(nums[mid] > x)
            high = mid-1;

        else
            low = mid+1;
    }
}
