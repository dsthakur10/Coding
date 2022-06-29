// Bitonic point in Bitonic array

/*

Bitonic array is an array which first increases strictly & then decreases(not necessarily)
after reaching a maximum value.

Bitonic array does NOT start with maximum value (reverse sorted array cannot be bitonic array)

This maximum value in bitonic array --> bitonic point

*/


int findBitonicPoint(vector<int> arr)
{
    int n = arr.size();
    if(n==1)
        return arr[0];

    if(arr[n-2] < arr[n-1])     // bitonic array is sorted array --> bitonic point is at the rightmost end
        return arr[n-1];

    int low = 1, high = n-2;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(arr[mid-1] < arr[mid] && arr[mid] > arr[mid+1])
            return arr[mid];

        else if(arr[mid-1] < arr[mid])
            low = mid+1;

        else
            high = mid-1;
    }

    return -1;
}
