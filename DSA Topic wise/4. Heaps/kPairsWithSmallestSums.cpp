/*

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.

Define a pair (u, v) which consists of one element from the first array and one element from the second array.

Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.

Example 1:
Input: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
Output: [[1,2],[1,4],[1,6]]
Explanation: The first 3 pairs are returned from the sequence: [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:
Input: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
Output: [[1,1],[1,1]]
Explanation: The first 2 pairs are returned from the sequence: [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]

Example 3:
Input: nums1 = [1,2], nums2 = [3], k = 3
Output: [[1,3],[2,3]]
Explanation: All possible pairs are returned from the sequence: [1,3],[2,3]

*/



// Method-1 --> O(klogn) time --> In worst case min-heap will contain all 1 element from each row. --> size = n

// <sum, <index1, index2>>
typedef pair< int, pair<int, int>> ppi;

vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {

    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> result;
    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;

    // each row added {0th column of each row} --> initialization
    for(int i=0; i<min(m, k); i++)
        pq.push({nums1[i] + nums2[0], {i, 0}});

    while(!pq.empty() && k > 0)
    {
        int sum = pq.top().first;
        int u = pq.top().second.first;      // row
        int v = pq.top().second.second;     // column
        pq.pop();
        k--;
        result.push_back({nums1[u], nums2[v]});

        // update column# of popped element
        if(v != n-1)
            pq.push({nums1[u] + nums2[v+1], {u, v+1}});

    }

    return result;
}
