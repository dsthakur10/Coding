/*

Given the array of integers nums, you will choose two different indices i and j of that array. Return the maximum value of (nums[i]-1)*(nums[j]-1).

Constraints:

2 <= nums.length <= 500
1 <= nums[i] <= 10^3

Example 1:

Input: nums = [3,4,5,2]
Output: 12
Explanation: If you choose the indices i=1 and j=2 (indexed from 0), you will get the maximum value, that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.
Example 2:

Input: nums = [1,5,4,5]
Output: 16
Explanation: Choosing the indices i=1 and j=3 (indexed from 0), you will get the maximum value of (5-1)*(5-1) = 16.
Example 3:

Input: nums = [3,7]
Output: 12

*/



#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>


int maxProduct(std::vector<int>& nums);             // min-heap
int maxProduct2(std::vector<int>& nums);            // linear time --> find greatest & 2nd greatest elements


int main()
{
    std::vector<int> vec;
    int n,k;

    std::cout << "Enter size of array: ";
    std::cin >> n;

    std::cout << "Enter array elements: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }

    int product = maxProduct2(vec);

    std::cout << "\nMaximum product = " << product;
    return 0;

}



int maxProduct(std::vector<int>& nums)
{
    int first, second;
    std::priority_queue<int,std::vector<int>,std::greater<int>> pq;

    for(int i=0; i<nums.size(); i++)
    {
        pq.push(nums[i]);

        if(pq.size() > 2)
            pq.pop();
    }

    first = pq.top();
    pq.pop();
    second = pq.top();
    pq.pop();

    return (first-1)*(second-1);
}



int maxProduct2(std::vector<int>& nums)
{
    int first=0, second=0;

    for(auto no: nums)
    {
        if(first < no)
        {
            second = first;
            first = no;
        }

        else
            second = std::max(no,second);
    }

    return (first-1)*(second-1);
}
