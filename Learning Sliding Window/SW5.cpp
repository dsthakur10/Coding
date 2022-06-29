/*

Given an array containing N POSITIVE - integers and an integer K.
Your task is to find the length of the longest Sub-Array with the sum of the elements equal to the given value K.

eg.

Input : {4, 1, 1, 1, 2, 3, 5}
Output : 4

*/



int lenOfLongSubarr(int A[],  int N, int K)
{
    int i=0, j=0, sum = 0, count = 0;

    while(j < N)
    {
        sum += A[j];

        if(sum == K)
        {
            count = max(count, j-i+1);
            j++;
        }

        else if(sum < K)
            j++;

        else
        {
            while(sum > K)
            {
                sum -= A[i];
                i++;
            }

            j++;
        }
    }

    return count;
}


