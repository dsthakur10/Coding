/*

Given a non-negative number N and two values L and R. The problem is to toggle the bits in the range L to R
in the binary representation of N, i.e, to toggle bits from the rightmost Lth bit to the rightmost Rth bit.
A toggle operation flips a bit 0 to 1 and a bit 1 to 0. Print N after the bits are toggled

Input:
N = 50 , L = 2 , R = 5
Output: 44

Explanation:
(50)10 = (110010)2.  After toggling all the bits from 2nd to 5th position we get (101100)2 = (44)10

*/


// XOR operation : x ^ 1 = x' | x ^ 0 = x

// If you want to toggle certain bits --> XOR them with 1
// If you want to keep certain bits as they are --> XOR them with 0

// LOGIC : Get a number with 1-bits in the range L - R & 0-bits everywhere else
/*
    eg: N = 101 10110 011   L = 4, R = 8

    x = 2^R - 1 --> 1111 1111
    y = 2^(L-1) - 1 --> 111

    x ^ y = 11111 000

    answer = N ^ (x ^ y)
*/


int toggleBits(int N , int L , int R)
{
    int x = (1 << R) - 1;
    int y = (1 << (L-1)) - 1;

    int temp = x ^ y;
    int ans = N ^ temp;

    return ans;
}
