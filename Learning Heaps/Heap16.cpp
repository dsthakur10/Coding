/*

Given an array of integers and two numbers k1 and k2.
Find the sum of all elements between given two k1’th and k2’th smallest elements of the array.

Constraints:
    - 1 <= k1 < k2 <= n
    - all elements of array are distinct.

Examples:
    Input : arr[] = {20, 8, 22, 4, 12, 10, 14},  k1 = 3,  k2 = 6
    Output : 26
         - 3rd smallest element is 10. 6th smallest element is 20. Sum of all element between k1 & k2 is 12 + 14 = 26

*/


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>


int findKthSmallest(std::vector<int>& nums, int k);
int findSum(std::vector<int>& nums, int k1, int k2);

int main()
{
    std::vector<int> vec;
    int n,k1,k2,x,sum=0;

    std::cout<< "Enter size of array: ";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0;i<n;i++)
    {
        std::cin >> x;
        vec.push_back(x);
    }


    std::cout << "\nArray:\n";
    for(int i=0;i<n;i++)
        std::cout << vec[i] << " ";

    std::cout << "\nEnter k1 & k2 values:";
    std::cin >> k1 >> k2;

    if(k1 > k2)
        return 0;

    std::cout << "\n\nSum = " << findSum(vec,k1,k2);

    return 0;

}



int findKthSmallest(std::vector<int>& nums, int k)
{
    std::priority_queue<int> pq;           // max-heap
    int i=0;

    while(i < nums.size())
    {
        pq.push(nums[i]);

        if(pq.size() > k)
            pq.pop();

        i++;
    }

    return pq.top();
}



int findSum(std::vector<int>& nums, int k1, int k2)
{
    int sum = 0;
    k1 = findKthSmallest(nums,k1);
    k2 = findKthSmallest(nums,k2);

    for(int i=0; i<nums.size(); i++)
    {
        if((nums[i] > k1) && (nums[i] < k2))
            sum += nums[i];
    }

    return sum;
}
