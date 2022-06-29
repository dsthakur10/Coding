/*

Greedy approach --> We try to divide target by 2 whenever its even & target > startValue
                --> We add 1 to target otherwise.


Instead of multiplying by 2 or subtracting 1 from startValue, we could divide by 2 (when target is even) or add 1 to target.

The motivation for this is that it turns out we always greedily divide by 2:

If say target is EVEN, then if we perform 2 additions and 1 division,
we could instead perform 1 division and 1 addition for less operations -->  [(target + 2) / 2 VS target / 2 + 1].

If say target is ODD, then if we perform 3 additions and 1 division,
we could instead perform 1 addition, 1 division, and 1 addition for less operations --> [(target + 3) / 2 VS (target + 1) / 2 + 1].

*/


int brokenCalc(int startValue, int target)
{
    int x = target;
    int count = 0;

    while(x != startValue)
    {
        if(x > startValue && x%2 == 0)
            x = x/2;

        else
            x = x+1;

        count++;
    }

    return count;
}




int brokenCalc2(int startValue, int target)
{
    int x = target;
    int count = 0;

    while(x > startValue)
    {
        if(x%2 == 0)
            x = x/2;

        else
            x = x+1;

        count++;
    }

    return startValue - x + count;
}
