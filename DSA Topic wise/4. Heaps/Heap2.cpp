/*
Find top k frequent elements.

    Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

    Constraints:
        - k is in the range [1, the number of unique elements in the array].
        - It is guaranteed that the answer is unique.

*/


#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
typedef std::pair<int,int> pi;


std::vector<int> topKFrequent(std::vector<int>& nums, int k);


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

    std::cout << "\nEnter K-value:";
    std::cin >> k;

    vec = topKFrequent(vec,k);

    std::cout << "\n : " << k << " frequent elements in array: ";

    for(int i=0;i<vec.size();i++)
        std::cout << vec[i] << " ";

    return 0;

}



// ------------------- Method-1 -------------------

/*
    Idea is to use heap. But how ?
    Taking reference from "k-largest numbers" problem, there we used min-heap of size k+1 & as soon as heap size became k+1, we popped of minimum/top element.
    In the end we just left with k-largest elements in the heap which is what we wanted.

    Here we cannot simply take any numbers in the beginning to start with. Need to modify the array to convert it to heap problem.

    It is clear that we want to have frequency counts of array elements alongside the element itself to be pushed into the heap. Min-heap is to be used to get last k elements
    with maximum counts. --> sorting is done based on frequency

    So we need a DS that can store array element alongside its frequency + which is efficient in calculating the frequency --> hash table --> unordered_map

    we will push unordered_map's content in heap with frequency as first element & array as second.

*/


std::vector<int> topKFrequent(std::vector<int>& nums, int k)
{
    std::vector<int> vec;
    std::priority_queue<pi, std::vector<pi>, std::greater<pi>> pq;
    std::unordered_map<int,int> mp;

    for(int i=0; i<nums.size(); i++)
        mp[nums[i]]++;                    // create an entry in map for the first time an array appears(key = array element).
                                            // Next time just increment the mapped value (i.e. frequency)


    for(auto it = mp.begin(); it != mp.end(); it++)             // it is the iterator for the unordered_map
    {
        pq.push(std::make_pair(it->second,it->first));          // heap is sorted by mapped element of unordered_map (i.e. frequency)

        if(pq.size() > k)
            pq.pop();
    }

    while(!pq.empty())
    {
        vec.push_back(pq.top().second);                         // map's second = heap's first & vice versa
        pq.pop();
    }

    return vec;
}
