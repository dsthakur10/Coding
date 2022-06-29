/*

Intuitively what this solution does is keeps tracks of lower bounds for the first and second element of the subsequence.
Initially we have first = INF and second = INF. Also I will simplify your test case to [1,0,2,0,-1,3]

Iteration One
first = 1 second = INF

Iteration Two
first = 0 second = INF

Iteration Three
first = 0 second = 2

Iteration Four (Nothing Changes)
first = 0 second = 2

Iteration Five (Confusing Part)
first = -1 second = 2

Iteration Six
return true; Since 3 > 2 && 3 > -1


Setting first = -1 is important, yet doesn't change the answer in this case since second = 2 implies that
there existed a value that was previously smaller than 2. Now if you find any value greater that 2 we know there exist
in an increasing triplet sub sequence. But notice if we had a test case like this [1,0,2,0,-1,0,1] we now could see the
importance of the updated lower bound for first = -1, so we we can have a correct lower bound for second = 0.
And also note this answer ask for existence, and not to construct the triplet, as this solution won't be able to in its current form


*/




// The question only asks whether it exists.
// The key to prove this solution is always correct is that there is always a number
// before c2 that is less than c2, which might or might not be c1 (otherwise, c2==INT_MAX and wont get updated).
// Now if a number is greater than c2, we can safely return true.

bool increasingTriplet(vector<int>& nums)
{
    if(nums.size() < 3)
        return false;

    int first = INT_MAX, second = INT_MAX;

    for(int x : nums)
    {
        if(x <= first)
            first = x;

        else if(x <= second)
            second = x;

        else
            return true;
    }

    return false;
}


