/*
Sort nearly sorted (k-sorted) array.

    - Given an array of n elements, where each element is at most k away from its target position.
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

std::vector<int> sortK(std::vector<int>& nums, int k);          // Time = O(nlogn) Space = O(1) - Sorting
std::vector<int> sortK2(std::vector<int>& nums, int k);         // Time = O(nlogk) Space = O(k) - MinHeap
std::vector<int> sortK3(std::vector<int>& nums, int k);



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

    std::cout << "\n\nSorting nearly sorted (" << k << " sorted) array : ";
    vec = sortK2(vec,k);

    for(int i=0;i<vec.size();i++)
        std::cout << vec[i] << " ";

    return 0;

}



std::vector<int> sortK(std::vector<int>& nums, int k)
{
    std::sort(nums.begin(), nums.end(), std::greater<int>());

    std::vector<int> vec;

    for(int i=0; i<k;i++)
        vec.push_back(vec[i]);

    return vec;
}



//---------------- Method-2 ----------------

/*
    For k-sorted array, create a min-heap of (k+1) size. Since every element can be k positions away from its original position in sorted order, by storing (k+1) elements in
    min-heap at any time will ensure that topmost (root) element in min-heap is minimum of all (k+1) elements --> Thus can be popped & stored in an array at correct position.

*/

std::vector<int> sortK2(std::vector<int>& nums, int k)
{
    std::priority_queue <int, std::vector<int>, std::greater<int>> pq;           // min-heap
    int i=0;
    int counter = 0;

    while(i < nums.size())
    {
        pq.push(nums[i]);

        if(pq.size() == k+1)
        {
            nums[counter++] = pq.top();
            pq.pop();
        }

        i++;
    }

    while(!pq.empty())
    {
        nums[counter++] = pq.top();
        pq.pop();
    }

    return nums;
}
