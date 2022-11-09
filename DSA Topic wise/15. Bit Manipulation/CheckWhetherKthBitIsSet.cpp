/*

Given a number N and a bit number K, check if Kth bit of N is set or not. A bit is called set if it is 1.

Position of set bit '1' should be indexed starting with 0 from LSB side in binary representation of the number

*/


bool checkKthBit(int n, int k)
{
    int one = 1 << k;

    return ((n & one) == 0) ? false : true;
}
