/*

Given two equally sized 1-D arrays A, B containing N integers each.
A sum combination is made by adding one element from array A and another element of array B.

Return the maximum C valid sum combinations from all the possible sum combinations.

*/

// TLE

vector<int> Solution::solve(vector<int> &A, vector<int> &B, int C) {

    int n = A.size();
    vector<int> result;
    priority_queue<int, vector<int>, greater<int>> pq;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int sum = A[i] + B[j];
            pq.push(sum);

            if(pq.size() > C)
                pq.pop();
        }
    }

    while(!pq.empty())
    {
        result.push_back(pq.top());
        pq.pop();
    }

    reverse(result.begin(), result.end());
    return result;
}


// Method-2 --> O(nlogn)

typedef pair< int, pair<int, int>> ppi;

vector<int> Solution::solve(vector<int> &A, vector<int> &B, int C) {

    int n = A.size();
    vector<int> result;
    priority_queue<ppi> pq;

    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end(), greater<int>());

    // each row added {0th column of each row}
    for(int i=0; i<n; i++)
        pq.push({A[i] + B[0], {i, 0}});

    while(!pq.empty() && C > 0)
    {
        int sum = pq.top().first;
        int u = pq.top().second.first;      // row
        int v = pq.top().second.second;     // column
        pq.pop();
        C--;
        result.push_back(sum);

        // update column# of popped element
        if(v != n-1)
            pq.push({A[u] + B[v+1], {u, v+1}});
    }
    return result;
}
