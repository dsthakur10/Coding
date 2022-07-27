/*

Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest
element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

You must find a solution with a memory complexity better than O(n^2).

Example 1:
Input: matrix = [[1,5,9],[10,11,13],[12,13,15]], k = 8
Output: 13
Explanation: The elements in the matrix are [1,5,9,10,11,12,13,13,15], and the 8th smallest number is 13

Example 2:
Input: matrix = [[-5]], k = 1
Output: -5

*/


// Method-1 --> Use MaxHeap --> Time = O(n^2logk) | Space = O(k)

int kthSmallest(vector<vector<int>>& matrix, int k) {

    priority_queue<int> pq;
    int n = matrix.size();

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            pq.push(matrix[i][j]);

            if(pq.size() > k)
                pq.pop();
        }
    }

    return pq.top();
}



// Method-2 --> Use MinHeap --> Time = O(klog(n^2)) | Space = O(k)

typedef pair<int, pair<int, int>> ppi;

int kthSmallest(vector<vector<int>>& matrix, int k) {

    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;
    int n = matrix.size();

    // element which is getting pushed is changed to -INF so that it can never be pushed back again (duplicacy)
    pq.push({matrix[0][0], {0, 0}});
    matrix[0][0] = INT_MIN;

    int result;
    while(k > 0)
    {
        int row = pq.top().second.first;
        int col = pq.top().second.second;
        result = pq.top().first;
        pq.pop();
        k--;

        // push the neighbors of current popped element as they were next higher elements
        if(row != n-1 && matrix[row+1][col] != INT_MIN)
        {
            pq.push({matrix[row+1][col], {row+1, col}});
            matrix[row+1][col] = INT_MIN;
        }

        if(col != n-1 && matrix[row][col+1] != INT_MIN)
        {
            pq.push({matrix[row][col+1], {row, col+1}});
            matrix[row][col+1] = INT_MIN;
        }
    }

    return result;
}



// Method-3 --> Using minHeap --> O(kLogk) time
// < value , <rowIndex, colIndex> >
typedef pair<int, pair<int, int>> ppi;

int kthSmallest(vector<vector<int>>& matrix, int k) {

    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;
    int n = matrix.size();

    // initialize min-heap with first element of each row
    for(int i=0; i<min(k, n); i++)
        pq.push({matrix[i][0], {i, 0}});

    int result;
    while(k > 0)
    {
        int row = pq.top().second.first;
        int col = pq.top().second.second;
        result = pq.top().first;
        pq.pop();
        k--;

        // insert next element of row whose element is just get popped out of heap
        if(col != n-1)
            pq.push({matrix[row][col+1], {row, col+1}});
    }

    return result;
}
