// Find the Smallest Divisor Given a Threshold

/*
Given an array of integers nums and an integer threshold, we will choose a positive integer divisor,
divide all the array by it, and sum the division's result.
Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element.
(For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.

Example 1:
Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation:
We can get a sum to 17 (1+2+5+9) if the divisor is 1.
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2).

Example 2:
Input: nums = [44,22,33,11,1], threshold = 5
Output: 44

*/



// nums[] = pages[]
// threshold = #students
// divisor = books
// Get the divisor = Distribute books in consecutive manner
// smallest divisor(sum of all divisions <= threshold) = minimum(maximum #pages for a student)

    // Parameter for Binary search --> divisor
    // low = 1 (When threshold is high enough to accommodate  ) | high = max(all numbers)


int smallestDivisor(vector<int>& nums, int threshold) {

    int low = 1, high = INT_MIN;

    for(int x : nums)
        high = max(x, high);

    int result = -1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(validDivisor(nums, threshold, mid))
        {
            result = mid;
            high = mid-1;
        }

        else
            low = mid+1;
    }

    return result;
}

bool validDivisor(vector<int>& nums, int threshold, int divisor)
{
    int sum = 0;

    for(int x : nums)
    {
        sum += ceil((float)x/divisor);

        if(sum > threshold)
            return false;
    }

    return true;
}
