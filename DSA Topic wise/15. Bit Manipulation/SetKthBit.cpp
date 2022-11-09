
/*

Given a number N and a value K. From the right, set the Kth bit in the binary representation of N.
The position of Least Significant Bit(or last bit) is 0, the second last bit is 1 and so on

*/


int setKthBit(int N, int K)
{
    int one = 1 << K;

    N = N | one;

    return N;
}
