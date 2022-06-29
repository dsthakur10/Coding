/*

Greedy approach --> Store the differences between costA & costB for each person in decreasing order.

Select the MIN(costA[i], costB[i]) & increase the countA or countB accordingly.

        --> We are selecting smaller value of bigger differences because that will yield overall minimum costs. Picking smaller value
            from bigger difference is better than picking smaller value from smaller difference.

If either of countA or countB hits N --> select the other ones from next iterations onwards.

*/


int twoCitySchedCost(vector<vector<int>>& costs)
{
    multimap<int, int> mp;
    int sum = 0;
    int countA = 0;
    int countB = 0;
    int x, n = costs.size()/2;

    for(int i=0; i<costs.size(); i++)
        mp.insert(make_pair(abs(costs[i][0] - costs[i][1]), i));

    for(auto it = mp.rbegin(); it != mp.rend(); it++)
    {
        x = it->second;

        if(countA == n)
        {
            sum += costs[x][1];
            countB++;
        }

        else if(countB == n)
        {
            sum += costs[x][0];
            countA++;
        }


        else
        {
            if(costs[x][0] < costs[x][1])
            {
                sum += costs[x][0];
                countA++;
            }

            else
            {
                sum += costs[x][1];
                countB++;
            }
        }

    }

    return sum;

}


/*

We sort the costs array by the difference in cost of sending a person to a - cost of sending her/him to b

Clearly it will be profitable to send some one to a if the above difference is negative, because then cost of sending him to a is lower

The most profit we make by sending a person to a is the one having the most negative difference

Similiarly for b most profit = highest positive difference

Thus by sorting them in difference of their costs will give us the required results
The first n ( of 2n) goes to A the rest to b

*/


static bool comparator ( vector <int> &a, vector <int> &b )
{
    if( a[0] - a[1]  < b[0] - b[1])
        return true;                            // sort by difference in cost

    else
        return false;
}


int twoCitySchedCost2(vector<vector<int>>& costs)
{
    sort(costs.begin(), costs.end(), comparator);

    int n = costs.size()/2, ans = 0;

    for( int i = 0 ; i < n ; i++ )
        ans += costs[i][0] + costs[i+n][1];

    // send the first to a , rest to b

    return ans;
}
