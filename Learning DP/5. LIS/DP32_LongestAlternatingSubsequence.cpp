
// Longest Alternating subsequence

/*
A sequence {x1, x2, .. xn} is alternating sequence if its elements satisfy one of the following relations :

    x1 < x2 > x3 < x4 > x5.....
            OR
    x1 >x2 < x3 > x4 < x5.....

Your task is to find the longest such sequence.

Example 1:
Input: nums = {1,5,4}
Output: 3
Explanation: The entire sequenece is a alternating sequence.

Example 2:
Input: nums = {1,17,5,10,13,15,10,5,16,8}
Output: 7
Explanation: There are several subsequences that achieve this length. One is {1,17,10,13,10,16,8}.

*/


// LOGIC

/*
We will be using the concept of LIS but with minor changes. Here we will be requiring 2 arrays.

    1. LAS[i][0] --> nums[i] > nums[j]      --> i is the last element. j is previous element from index 0 - i-1
    2. LAS[i][1] --> nums[i] < nums[j]

    las[i][0] = Length of the longest alternating subsequence ending at index i and
                last element is greater than its previous element
    las[i][1] = Length of the longest alternating subsequence ending at index i and
                last element is smaller than its previous element

    Equations:
    las[i][0] = max (las[i][0], las[j][1] + 1);         for all j < i and A[j] < A[i]

    las[i][1] = max (las[i][1], las[j][0] + 1);         for all j < i and A[j] > A[i]

*/

// TLE --> Time = O(n^2) | Space = O(n)

int AlternatingaMaxLength(vector<int>&nums){

    int maxLen = 0;
    int n = nums.size();
    int LAS[n][2];

    for(int i=0; i<n; i++)
    {
        LAS[i][0] = 1;
        LAS[i][1] = 1;

        for(int j=0; j<i; j++)
        {
            if(nums[j] < nums[i])
            {
                LAS[i][0] = max(LAS[i][0], 1 + LAS[j][1]);
            }

            else if(nums[j] > nums[i])
            {
                LAS[i][1] = max(LAS[i][1], 1 + LAS[j][0]);
            }
        }

        maxLen = max(maxLen, LAS[i][0]);
        maxLen = max(maxLen, LAS[i][1]);
    }

    return maxLen;
}



// Method-2 --> Time = O(n) | Space = O(1)

/*
    inc = Length of longest alternative subsequence so far with current value > previous value.
    dec = Length of longest alternative subsequence so far with current value < previous value.

The tricky part of this approach is to update these two values.

“inc” should be increased, if and only if the last element in the alternative sequence > previous element.
“dec” should be increased, if and only if the last element in the alternative sequence < previous element.

*/

int AlternatingaMaxLength(vector<int>&nums){

    int maxLen = 0;
    int n = nums.size();

    int inc = 1, dec = 1;

    for(int i=1; i<n; i++)
    {
        if(nums[i] < nums[i-1])
            dec = inc + 1;

        else if(nums[i] > nums[i-1])
            inc = dec + 1;
    }

    maxLen = max(inc,dec);
    return maxLen;
}
