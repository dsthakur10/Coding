/*

CAR POOLING

There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).

You are given the integer capacity and an array trips where trip[i] = [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi passengers and
locations to pick them up and drop them off are fromi and toi respectively. The locations are given as the number of kilometers due east from the car's initial location.

Return TRUE IF IT IS POSSIBLE TO PICK UP AND DROP OFF ALL PASSENGERS FOR ALL THE GIVEN TRIPS, or false otherwise.


Example 1:

Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false

Example 2:

Input: trips = [[2,1,5],[3,3,7]], capacity = 5
Output: true

Example 3:

Input: trips = [[2,1,5],[3,5,7]], capacity = 3
Output: true

Example 4:

Input: trips = [[3,2,7],[3,7,9],[8,3,9]], capacity = 11
Output: true


Constraints:

1 <= trips.length <= 1000
trips[i].length == 3
1 <= numPassengersi <= 100
0 <= fromi < toi <= 1000
1 <= capacity <= 105


*/


#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>

// N = number of trips , M = number of stops

bool carPooling(std::vector<std::vector<int>>& trips, int capacity);
bool carPooling2(std::vector<std::vector<int>>& trips, int capacity);       // Time = O(N + M)      Space = O(M)
bool carPooling3(std::vector<std::vector<int>>& trips, int capacity);       // Time = O(N)          Space = O(N)


int main()
{
    std::vector<std::vector<int>> trips1 = {{2,1,5},{3,3,7}};
    int capacity1 = 4;
    std::vector<std::vector<int>> trips2 = {{2,1,5},{3,3,7}};
    int capacity2 = 5;
    std::vector<std::vector<int>> trips3 = {{2,1,5},{3,5,7}};
    int capacity3 = 3;
    std::vector<std::vector<int>> trips4 = {{3,2,7},{3,7,9},{8,3,9}};
    int capacity4 = 11;

    bool flag = carPooling(trips4, capacity4);

    if(flag)
        std::cout << "TRUE";
    else
        std::cout << "FALSE";

    return 0;
}


bool sortcol(const std::vector<int>& v1, const std::vector<int>& v2)          // binary predicate
{
    return v1[1] < v2[1];
}




// ----------------- Method-1 ------------------

bool carPooling(std::vector<std::vector<int>>& trips, int capacity)
{

}




// ----------------- Method-2 ------------------

/*
Since we only have 1,001 stops, we can just figure out how many people get in and out at each location.

Process all trips, adding passenger count to the start location, and removing it from the end location.
After processing all trips, a positive value for the specific location tells that we are getting more passengers; negative - more empty seats.

Finally, scan all stops and check if we ever exceed our vehicle capacity. The moment capacity becomes < 0 --> return false


trips =  {3,2,7},
         {3,7,9},
         {8,3,9}

stops:      1   2   3   4   5   6   7   8   9   10  11  12  13  14

                +3                  -3
                                    +3=0    -3
                    +8                      -8=-11

capacity = 11 - 3 = 8 >= 0
         = 8 - 8 = 0 >= 0
         = 0 - 0 = 0 >= 0
         = 0 - (-11) = 11 >= 0

         return true

*/

bool carPooling2(std::vector<std::vector<int>>& trips, int capacity)
{
    int stops[1001];

    for(auto t:trips)                       // O(N)
    {
        stops[t[1]] += t[0];                        // adding & deleting passengers as & when required
        stops[t[2]] -= t[0];
    }

    for(int i=0; i<1001; i++)               // O(M)
    {
        capacity -= stops[i];
        if(capacity < 0)                            // number of passengers cannot fit in the car. return false
            break;
    }

    return (capacity >= 0);
}



// ----------------- Method-3 ------------------

/*
    Same as method-2 with the only difference of using map instead of array which is actually of M length. Saves time to not compute unnecessary stops which are never used.

*/

bool carPooling3(std::vector<std::vector<int>>& trips, int capacity)
{
    std::map<int,int> mp;               // <stop#, #passengers>

    for(auto t: trips)
    {
        mp[t[1]] += t[0];
        mp[t[2]] -= t[0];
    }

    for(auto m: mp)
    {
        capacity -= m.second;

        if(capacity < 0)
            return false;
    }

    return true;
}
