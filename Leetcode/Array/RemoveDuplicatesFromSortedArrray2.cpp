
int removeDuplicates(vector<int>& nums)
{
    if(nums.empty())
        return 0;

    int n = nums.size();                                // k --> number of elements allowed (atmost 2 duplicates for each element)
    int k=1, temp = 0;                                  // temp --> index that stores last allowed element in new array

    for(int i=1; i<n; i++)
    {
        if(nums[i] == nums[temp])                       // allow first duplicate if any
        {
            temp++;
            nums[temp] = nums[i];
            k++;
            i++;
        }

        while((i < n) && (nums[i] == nums[temp]))       // check for #duplicates > 2
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




int removeDuplicates2(vector<int>& nums) {

    int n = nums.size();
    int counter = 0;

    for(int i=1; i<n; i++)
    {
        if(nums[i] == nums[i-1])
        {
            nums[i - counter] = nums[i];
            i++;
        }

        while((i<n) && (nums[i] == nums[i-1]))
        {
            counter++;
            i++;
        }

        if(i<n)
            nums[i - counter] = nums[i];

    }

    return n-counter;
}



int removeDuplicates3(vector<int>& nums)
{
    int i = 0;
    for (int x : nums)
    {
        if (i < 2 || x > nums[i-2])
            nums[i++] = x;
    }

    return i;
}
