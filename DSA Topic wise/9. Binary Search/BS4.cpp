
// Capacity To Ship Packages Within D Days

/*

A conveyor belt has packages that must be shipped from one port to another within days days.

The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages
on the conveyor belt (in the order given by weights).

NOTE: We do NOT load more weight than the maximum weight capacity of the ship.

Return the LEAST WEIGHT CAPACITY of the ship that will result in all the packages on the conveyor belt
being shipped within days "days"

Example 1:
Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
Output: 15

Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
1st day: 1, 2, 3, 4, 5
2nd day: 6, 7
3rd day: 8
4th day: 9
5th day: 10

    NOTE: cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages
    into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.

Example 2:
Input: weights = [3,2,2,4,1,4], days = 3
Output: 6

Explanation: A ship capacity of 6 is the minimum to ship all the packages in 3 days like this:
1st day: 3, 2
2nd day: 2, 4
3rd day: 1, 4

Example 3:
Input: weights = [1,2,3,1,1], days = 4
Output: 3

Explanation:
1st day: 1
2nd day: 2
3rd day: 3
4th day: 1, 1

*/



// Same as Allocate Minimum #pages

/*
    // weights[] = pages[]
    // packages = books
    // #days = #students
    // Distribute packages/books in consecutive manner
    // DONOT overload a day/student
    // least weight capacity of ship = minimum(maximum weight loaded in a day)= minimum(maximum pages for a student)
*/


int shipWithinDays(vector<int>& weights, int days) {

    if(days > weights.size())
        return -1;

    int low = INT_MIN, high = accumulate(weights.begin(), weights.end(), 0);

    for(int i=0; i<weights.size(); i++)
        low = max(weights[i], low);

    if(days == 1)
        return high;

    int leastMaxCapacity = -1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(validShipment(weights, days, mid))
        {
            high = mid-1;
            leastMaxCapacity = mid;
        }

        else
            low = mid+1;
    }

    return leastMaxCapacity;
}


bool validShipment(vector<int>& weights, int days , int maxLimit)
{
    int totalDays = 1, sum=0;

    for(int x : weights)
    {
        sum += x;

        if(sum > maxLimit)
        {
            sum = x;
            totalDays++;
        }

        if(totalDays > days)
            return false;
    }

    return true;
}
