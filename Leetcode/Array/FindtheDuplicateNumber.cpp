/*
Given an array of integers nums containing n + 1 integers where each integer is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem:
    1. without modifying the array nums
    2. using only CONSTANT extra space.

*/

// Methods-1,3,4 modifies the array. Method-2 uses extra space.


// METHOD-1 --> Sort the array --> check if nums[i] == nums[i+1] --> return it


// METHOD-2 --> Use Hashset --> check if nums[i] is already in the set


// METHOD-3 --> make nums[index] = index
        // map each number to its equivalent index in the array. For instance, map (and store) the number 5 to index 5
        // (i.e. nums[5] = 5). Since there are (n + 1)(n+1) positions/indexes in the input array, and the numbers range from 1 to n,
        // at least one index will have more than one number (due to the pigeonhole principle). Return this index.


// METHOD-4 --> Negative marking --> Negate the element at index nums[i] while traversing the array. In case if duplicate # comes,
//                                   element at index nums[i] has already been negated. Return this 'nums[i]'


// Method-5 --> Binary Search -->


// Method-6 --> Sum of set Bits -->


// METHOD-7 --> Hair & tortoise problem --> Create a cycle-like condition to implement 2-pointer approach (slow-fast pointers).

        // Return the start node where the cycle begins. First of all, where does the cycle come from?
        // Let's use the function f(x) = nums[x] to construct the sequence: x, nums[x], nums[nums[x]], nums[nums[nums[x]]], ....
        // Each new element in the sequence is an element in nums at the index of the previous element.
        // If one starts from x = nums[0], such a sequence will produce a linked list with a cycle.
        // The CYCLE APPEARS BECAUSE NUMS CONTAINS DUPLICATES. The duplicate node is a cycle entrance.


int findDuplicate3(vector<int>& nums)
{
    int temp;
    int index = nums[0];

    while(nums[index] != index)
    {
        temp = nums[index];
        nums[index] = index;
        index = temp;
    }

    return index;
}



int findDuplicate4(vector<int>& nums)
{
    int N = nums.size();

    int ans;
    for(int i=0; i<N; i++)
    {
        int index = abs(nums[i]);

        if(nums[index] < 0)
        {
            ans = index;
            break;
        }

        nums[index] *= -1;
    }

    for(int i=0; i<N; i++)
    {
        if(nums[i] < 0)
            nums[i] *= -1;
    }

    return ans;
}



int findDuplicate7(vector<int>& nums)
{
    int N = nums.size();
    int slow = nums[0];
    int fast = nums[nums[0]];

    while(slow != fast)
    {
        slow = nums[slow];
        fast = nums[nums[fast]];
    }

    int temp = 0;

    while(temp != slow)
    {
        slow = nums[slow];
        temp = nums[temp];
    }

    return temp;
}
