
/*

An ugly number is a positive integer whose prime factors are limited to 2, 3, and 5.

Given an integer n, return the nth ugly number.

Input: n = 10
Output: 12
Explanation: [1, 2, 3, 4, 5, 6, 8, 9, 10, 12] is the sequence of the first 10 ugly numbers.

Example 2:
Input: n = 1
Output: 1
Explanation: 1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.

*/


/*

We have an array k of first n ugly number. We only know, at the beginning, the first one, which is 1. Then
We will maintain 3 pointers t2, t3, t5 corresponding to respective prime factors.

Initially, all these pointers points to 0. result contains "1"

k[1] = min( k[0]x 2, k[0]x3, k[0]x5). The answer is k[0]x2. So we move 2's pointer to 1.
Then we test: k[2] = min( k[1]x2, k[0]x3, k[0]x5). And so on.....

Be careful about the cases such as 6, in which we need to forward both pointers of 2 and 3.


// Second explanation

Let me try to explain this using an example. Let's say we have the first 3 ugly numbers 1, 2, 3.

What would be the next number? Given the definition, the next number has to be the the smallest number among
2*(1,2,3), 3*(1,2,3), 5*(1,2,3). Obviously, the smallest number is 2 * 1 = 2. But wait, 2 is already in there.

So precisely speaking, the next number has to be the the smallest number among all the existing numbers multiplied
by 2, 3,5 that isn't in the list already.

Now, we can traverse all numbers and maintain a hashset if we want, but it would become O(N^2).
Good news is that we can solve this in a DP-like approach.

First, we assume there is only one number in the list, which is 1.
The next number is Min(2 * 1, 3 * 1, 5 * 1)=2 and it is not in the list.
Because we have already considered 2*1 (we move the pointer to its next position, which is 2),
now we only need to consider 2 * 2, 3 * 1, 5 * 1 in the next iteration.

This way, we don't have to worry about finding a number that is already in the list.

*/

int nthUglyNumber(int n) {

    vector<int> result;
    result.push_back(1);

    int t2 = 0, t3 = 0, t5 = 0;
    while(result.size() < n)
    {
        int x = min(result[t2]*2, min(result[t3]*3, result[t5]*5));
        result.push_back(x);

        if(x == result[t2] * 2)
            t2++;

        if(x == result[t3] * 3)
            t3++;

        if(x == result[t5] * 5)
            t5++;
    }

    return result.back();
}
