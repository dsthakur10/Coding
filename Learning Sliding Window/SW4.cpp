/*

Given an array and an integer K, find the maximum for each and every contiguous subarray of size k. Return them as an array.

Examples :

Input: nums = [1,3,-1,-3,5,3,6,7],  K = 3

Output: [3,3,5,5,6,7]

Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

*/


#include<climits>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<string>
#include<unordered_map>
#include<map>
#include<list>

typedef std::pair<int,int> pi;

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k);       // MAX-HEAP --> Time = O(nlogn) | Space = O(n) --> IN worst case, heap grows to n size

std::vector<int> maxSlidingWindow2(std::vector<int>& nums, int k);      // Multimap (decreasing order) --> Time = O(nlogk) | Space = O(k);

std::vector<int> maxSlidingWindow3(std::vector<int>& nums, int k);


int main()
{
    int n,k;
    std::vector<int> nums;

    std::cout << "Enter size of vector: ";
    std::cin >> n;

    std::cout << "Enter the array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        nums.push_back(k);
    }

    std::cout << "\nEnter the size of subarray: ";
    std::cin >> k;

    std::vector<int> maxWindow = maxSlidingWindow3(nums,k);

    std::cout << "\nMaximum sliding window for each subarray of size " << k << ": ";

    for(int i=0; i<maxWindow.size(); i++)
        std::cout << maxWindow[i] << " ";

    return 0;
}


// ---------------- Method-1 -----------------

/*
    Idea is to store every element of the current window in the max-heap which can be a potential contender for maximum element
    of some other window in future.

    Keep popping top(maximum element) from heap if it lies outside the current window (index < i)

    Append the top element in the vector. This will be the max element of that particular window. HOW ??
    --> All the top elements from outside window has previously been removed.

*/

std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k)
{
    //int first = INT_MIN, second = INT_MIN;
    int n = nums.size();
    std::priority_queue<pi> pq;
    std::vector<int> vec;

    int i=0,j=0;

    while(j < n)
    {
        pq.push(std::make_pair(nums[j],j));

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            while(i > pq.top().second)                  // this will make sure no elements(maximum element in past) from outside the window interfere in the
                pq.pop();                               // calculation of current window.

            vec.push_back(pq.top().first);

            if(i == pq.top().second)                    // Undo the work done at ith index. --> remove the top element before sliding IF it's index == i
                pq.pop();
            // this is redundant work. Already checked in the while loop above.

            i++;
            j++;
        }
    }

    return vec;

}



// ------------------ Method-2 ----------------------

std::vector<int> maxSlidingWindow2(std::vector<int>& nums, int k)
{

    int n = nums.size(), i, j;
    std::multimap<int,int,std::greater<int>> mp;                    // orders the map in decreasing sequence of key value. TIE breaker --> mapped value in increasing order
    std::vector<int> vec;

    i = 0;
    j = 0;

    while(j < n)
    {
        mp.insert(std::make_pair(nums[j],j));

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            vec.push_back(mp.begin()->first);                       // first element will always be maximum element of that particular window.

            mp.erase(mp.find(nums[i]));                             // find() will locate ith element of array which is to be removed during the sliding of window.
                                                                    // nums[i] can be a duplicate key value, but smaller index value will always appear first. So deletion
                                                                    // will be of element with lower index value --> ith value , the index which is to be removed after sliding
            i++;
            j++;
        }
    }

    return vec;
}



// ------------------ Method-3 ----------------------

/*
    Store only those elements in doubly LL which can be potential candidate for maximum in upcoming sliding window, but in a MORE PRECISE way compared to map & heap

    For any element nums[j] in array ,

        ...X X X X   nums[j]   Y Y Y Y...

        All the elements smaller than nums[j] && left of 'j' can never be potential candidate for maximum for any window. --> delete them

        Some of the elements smaller than nums[j] && right of 'j' can be potential candidate for maximum when nums[j] is removed from sliding window. Store them.

    Before inserting nums[j], perform necessary cleaning of doubly LL to limit the size by K

    Greatest element of the window will always be at front of the doubly LL. Push it in vector.

    While sliding the window, check if the front element == nums[i] --> if YES, delete it to undo the calculation done at ith index.

*/


std::vector<int> maxSlidingWindow3(std::vector<int>& nums, int k)
{
    int n = nums.size(), i, j;
    std::list<int> l;
    std::vector<int> vec;

    i=0;
    j=0;

    while(j < n)
    {
        if(j != 0)
        {
            while(!l.empty() && l.back() < nums[j])         // delete the element from doubly LL if it is smaller than nums[j] until list becomes empty
                l.pop_back();
        }

        l.push_back(nums[j]);

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            vec.push_back(l.front());                       // front of the doubly LL will always contain maximum element of the window

            if(nums[i] == l.front())                        // undo the work done at ith index
                l.pop_front();

            i++;
            j++;
        }
    }

    return vec;
}



vector <int> max_of_subarrays(int *arr, int n, int k)
{
    vector<int> result;
    deque<int> store;

    int i=0, j=1;
    store.push_back(0);

    while(j<n)
    {
        while(!store.empty() && arr[j] > arr[store.back()])
            store.pop_back();

        store.push_back(j);

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            result.push_back(arr[store.front()]);

            if(store.front() == i)
                store.pop_front();

            i++;
            j++;

        }
    }

    return result;
}
