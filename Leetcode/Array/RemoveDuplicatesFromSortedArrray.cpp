

int removeDuplicates(vector<int>& nums)
{

    if(nums.empty())
        return 0;

    int n = nums.size();
    int k=1, temp = 0;                          // k = number of unique elements
                                                // temp = index which holds last unique element sequentially in new array.

    for(int i=1; i<n; i++)
    {
        while((i < n) && (nums[i] == nums[temp]))       // i<n check is created to not get overflowed
            i++;

        if(i < n)
        {
            temp++;
            nums[temp] = nums[i];
            k++;
        }
    }

    return k;
}



int removeDuplicates2(vector<int>& nums)
{
    int counter = 0;
    int n = nums.size();

    for(int i = 1; i < n; i++)
    {
        if(nums[i] == nums[i-1])            // counter --> #duplicates in the given array.
            counter++;
        else
            nums[i-counter] = nums[i];
    }

    return n - counter;                     // #unique = total - #duplicates
}

