/*

There are given N ropes of different lengths, we need to connect these ropes into one rope.
The cost to connect two ropes is equal to sum of their lengths. The task is to connect the ropes with minimum cost.

*/


long long minCost(long long arr[], long long n) {

    priority_queue<long long, vector<long long>, greater<long long>> pq;

    for(long long i=0; i<n; i++)
        pq.push(arr[i]);

    long long sum = 0;
    while(pq.size() > 1)
    {
        long long first = pq.top();
        pq.pop();
        long long second = pq.top();
        pq.pop();

        sum += first + second;
        pq.push(first + second);
    }

    return sum;
}
