/*
Given an integer array nums and an integer k, return the kth largest element in the array.

Note: It is the kth largest element in the sorted order, not the kth distinct element.
*/


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

int findKthLargest(std::vector<int>& nums, int k);          // Time = O(nlogn) Space = O(1) - Sorting
int findKthLargest2(std::vector<int>& nums, int k);         // Time = O(nlogk) Space = O(k) - MinHeap
int findKthLargest3(std::vector<int>& nums, int k);



int main()
{
    //std::vector<int> vec = {3,2,3,1,2,4,5,5,6};
    std::vector<int> vec;
    int n,k;

    std::cout<< "Enter size of array: ";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0;i<n;i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }


    std::cout << "\nArray:\n";
    for(int i=0;i<n;i++)
        std::cout << vec[i] << " ";

    std::cout << "\nEnter k-value:";
    std::cin >> k;

    std::cout << "\n\n" << k << "th largest element = " << findKthLargest(vec,k);

    return 0;

}



int findKthLargest(std::vector<int>& nums, int k)
{
    std::sort(nums.begin(), nums.end(), std::greater<int>());

    return nums[k];
}



int findKthLargest2(std::vector<int>& nums, int k)
{
    std::priority_queue <int, std::vector<int>, std::greater<int>> pq;           // min-heap
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



int findKthLargest3(std::vector<int>& nums, int k)
{

}
