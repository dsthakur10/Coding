
/*


*/


// Method-1 --> MinHeap --> TLE

int Solution::findMedian(vector<vector<int> > &A) {

    int m = A.size(), n = A[0].size();
    int flag;

    if((m*n % 2) == 0)
        flag = 2;
    else
        flag = 1;

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    for(int i=0; i<m; i++)
        pq.push({A[i][0], i, 0});

    if(flag == 1)
    {
        int counter = 0, x = 0;
        int target = (m*n+1)/2;
        while(counter < target)
        {
            x = pq.top()[0];
            int row = pq.top()[1];
            int col = pq.top()[2];
            pq.pop();
            counter++;

            if(col < n-1)
                pq.push({A[row][col+1], row, col+1});
        }

        return x;
    }

    else
    {
        int counter = 0, x = 0, y = 0;
        int target = ((m*n)/2)+1;
        while(counter < target)
        {
            x = y;
            y = pq.top()[0];
            int row = pq.top()[1];
            int col = pq.top()[2];
            pq.pop();
            counter++;

            if(col < n-1)
                pq.push({A[row][col+1], row, col+1});
        }

        return (x+y)/2;
    }
}
