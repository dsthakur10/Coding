
/*

Given two numbers M and N.
The task is to find the position of the rightmost different bit in the binary representation of numbers

*/


unsigned int getFirstSetBit(int n)
{
    if(n == 0)
        return 0;

    int one = 1;
    int counter = 1;

    while(!(n & one))
    {
        one = one << 1;
        counter++;
    }

    return counter;
}


int posOfRightMostDiffBit(int m, int n)
{
    if(m == n)
        return -1;

    int XOR = m ^ n;

    return getFirstSetBit(XOR);
}
