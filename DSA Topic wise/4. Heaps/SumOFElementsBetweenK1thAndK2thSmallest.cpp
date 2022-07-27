
/*

Given an array A[] of N positive integers and two positive integers K1 and K2.
Find the sum of all elements between K1th and K2th smallest elements of the array.
It may be assumed that (1 <= k1 < k2 <= n).

*/


long long sumBetweenTwoKth( long long A[], long long N, long long K1, long long K2)
{
    priority_queue<long long> pq;

    for(long long i=0; i<N; i++)
    {
        pq.push(A[i]);

        if(pq.size() > K2)
            pq.pop();
    }

    long long sum = 0;
    pq.pop();                       // Ignore k2th smallest
    while(pq.size() > K1)
    {
        sum += pq.top();
        pq.pop();
    }

    return sum;
}
