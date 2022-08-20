/*

Given an integer an N. The task is to return the position of first set bit found from the right side in the
binary representation of the number.

Note: If there is no set bit in the integer N, then return 0 from the function.

*/

// Method-1 : Decimal method

unsigned int getFirstSetBit(int n)
{
    int one = 1;
    int rem, counter = 1;

    while(n > 0)
    {
        if(n % 2 == 1)
            return counter;

        n = n/2;
        counter++;
    }

    return 0;
}


// Method-2 : Bit manipulation

unsigned int getFirstSetBit(int n)
{
    int one = 1;
    int counter = 1;

    while(one > 0)
    {
        if((n & one) == one)
            return counter;

        one = one << 1;
        counter++;
    }

    return 0;
}


    // OR


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
