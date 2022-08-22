

/*

We first initialize result to 0. We then iterate from 0 to 31 (an integer has 32 bits).

In each iteration:
    1. We first shift result to the left by 1 bit.
    2. Then, if the last digit of input n is 1, we add 1 to result.
    3. To find the last digit of n, we just do: (n & 1)
        Example, if n=5 (101), n&1 = 101 & 001 = 001 = 1;
        however, if n = 2 (10), n&1 = 10 & 01 = 00 = 0).
    4. Finally, we update n by shifting it to the right by 1 (n >>= 1). This is because the last digit is already
       taken care of, so we need to drop it by shifting n to the right by 1.

At the end of the iteration, we return result.

*/


uint32_t reverseBits(uint32_t n)
{
    unsigned int NO_OF_BITS = sizeof(n) * 8;

    uint32_t ans = 0;
    int bit = 0;

    while(bit < 32)
    {
        ans = ans << 1;         // left shift answer        (so that bits of number get reversed)

        if((n & 1) == 1)
            ans++;

        n = n >> 1;             // right shift number       (to remove last visited bit)
        bit++;
    }

    return ans;
}
