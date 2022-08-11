
// Sliding Window Maximum

/*

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left
of the array to the very right. You can only see the k numbers in the window.
Each time the sliding window moves right by one position.

Return the maximum element of every sliding window.

Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
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

Example 2:
Input: nums = [1], k = 1
Output: [1]

*/


// Method-1 --> Max-heap --> Time - O(nlogn) | Space - O(n)

// We will insert every element in max-heap with index & let the heap decide which is the maximum in current window
// Put a constraint to check if current top is actually a valid maximum (exist in the current window) is its index
// If index < i (window start) --> need to pop this element from heap & continue popping elements from heap
// if indices < i


vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    vector<int> maxWindow;
    priority_queue<pair<int, int>> pq;  // <element, index>

    int n = nums.size(), i=0, j=0;

    while(j < n)
    {
        pq.push({nums[j], j});

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            while(pq.top().second < i)
                pq.pop();

            maxWindow.push_back(pq.top().first);

            i++;
            j++;
        }
    }

    return maxWindow;
}



// Method-2 --> Multimap --> Time - O(nlogk) | Space - O(k)

// Drawback of max-heap can be solved by multimap. --> Delete element at any index, not just top(maximum)
// At a time, multimap contains only k elements (including duplicate) of current window.
// As soon as window is incremented, we remove that element from multimap.
// In case of duplicates, default tie-breaker is smaller value --> Hence element at smaller index will be selected

vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    vector<int> maxWindow;
    multimap<int, int, greater<int>> mp;  // <element, index>

    int n = nums.size(), i=0, j=0;

    while(j < n)
    {
        mp.insert({nums[j], j});

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            maxWindow.push_back(mp.begin()->first);

            mp.erase(mp.find(nums[i]));

            i++;
            j++;
        }
    }

    return maxWindow;
}



// Method-3 --> Monotonic deque --> Store only promising elements in deque --> helpful in future
// We insert every element in deque, but before inserting current element we check -->
// if last element of deque < current. If so keep on deleting elements from back until we get last >= current

// This way we keep removing elements from deque if we get any better(greater) element than current last element

vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    vector<int> maxWindow;
    deque<int> dq;

    int n = nums.size(), i=0, j=0;

    while(j < n)
    {
        while(!dq.empty() && nums[dq.back()] < nums[j])
            dq.pop_back();

        dq.push_back(j);

        if(j-i+1 < k)
            j++;

        else if(j-i+1 == k)
        {
            maxWindow.push_back(nums[dq.front()]);

            if(dq.front() == i)
                dq.pop_front();

            i++;
            j++;
        }
    }

    return maxWindow;
}
