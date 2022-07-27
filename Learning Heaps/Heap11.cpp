/*
Find 'k' largest elements in an array.
Note: It is different than finding kth largest element in array
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

std::vector<int> findKLargest(std::vector<int>& nums, int k);          // Time = O(nlogn) Space = O(1) - Sorting
std::vector<int> findKLargest2(std::vector<int>& nums, int k);         // Time = O(nlogk) Space = O(k) - MinHeap
std::vector<int> findKLargest3(std::vector<int>& nums, int k);



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

    std::cout << "\n\n" << k << " largest element are: ";
    vec = findKLargest2(vec,k);

    for(int i=0;i<vec.size();i++)
        std::cout << vec[i] << " ";

    return 0;

}



std::vector<int> findKLargest(std::vector<int>& nums, int k)
{
    std::sort(nums.begin(), nums.end(), std::greater<int>());

    std::vector<int> vec;

    for(int i=0; i<k;i++)
        vec.push_back(vec[i]);

    return vec;
}



std::vector<int> findKLargest2(std::vector<int>& nums, int k)
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

    nums.clear();

    while(!pq.empty())
    {
        nums.push_back(pq.top());
        pq.pop();
    }

    return nums;
}
