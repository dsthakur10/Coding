/*

You are given an array routes representing bus routes where routes[i] is a bus route that ith bus repeats forever.

For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence
1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

Return the least number of buses you must take to travel from source to target.
Return -1 if it is not possible.

Example 1:
Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
Output: 2
Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.

Example 2:
Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
Output: -1

*/


// LOGIC

/*

We are given routes of all buses that contains any number of stops in between
Our task is to find minimum #buses to reach from source stop to target stop.

First idea that is obvious to come is to create graph of every stop --> There are 10^6 stops, to create a graph,
it will take N^2 time which is not feasible.

Second idea that came was to track bus routes & find the target --> But this is also not feasible.

Third idea --> Instead of bus, keep track of stops & the buses that arrives at those stops.

    1. We will maintain 2 DS --> HashMap <stop, #buses that arrives at this stop> | HashSet --> store visited stops
    2. HashMap is static while HashSet is dynamic & is used to store visited stops as & when required.
    3. Initially, push source stop in queue.
    4. While(queue is not empty)
        a. Pop from front --> name it current stop
        b. if current == target --> return level of node
        c. Get all the buses that arrives on this stop. From those buses, get all the possible stops that bus travels
            current stop --> bus-i --> next stop-j of bus-i
        d. Push the next stop in HashSet & in queue ONLY IF it is not already visited.
            (this will avoid unnecessary traveling & TLE)
        e. Also, once a bus' route is visited, delete it to ensure no duplicate entries for the same bus.

*/

int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {

    // <stop, #buses to reach stop>
    queue<pair<int, int>> q;
    unordered_map<int, vector<int>> mp;
    unordered_set<int> us;

    // storing buses at each stop (buses that pass through this stop)
    for(int i=0; i<routes.size(); i++)
    {
        for(int x : routes[i])
            mp[x].push_back(i);
    }

    if(mp.find(source) == mp.end() || mp.find(target) == mp.end())
        return -1;

    if(source == target)
        return 0;

    q.push({source, 0});

    while(!q.empty())
    {
        int curStop = q.front().first;
        int numberOfBuses = q.front().second;
        us.insert(curStop);
        q.pop();

        if(curStop == target)
            return numberOfBuses;

        for(int x : mp[curStop])        // buses that comes at this stop
        {
            // stops that are covered by those buses (x) that comes at stop "curStop"
            for(int y : routes[x])
            {
                if(us.find(y) == us.end())
                {
                    us.insert(y);
                    q.push({y, numberOfBuses+1});
                }
            }
            routes[x].clear();
        }
    }

    return -1;
}


// optimization

int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {

    // <stop, #buses to reach stop>
    queue<int> q;
    unordered_map<int, vector<int>> mp;
    unordered_set<int> us;

    // storing buses at each stop (buses that pass through this stop)
    for(int i=0; i<routes.size(); i++)
    {
        for(int x : routes[i])
            mp[x].push_back(i);
    }

    if(mp.find(source) == mp.end() || mp.find(target) == mp.end())
        return -1;

    if(source == target)
        return 0;

    q.push(source);
    int numberOfBuses = 0;

    while(!q.empty())
    {
        int n = q.size();
        numberOfBuses++;
        while(n > 0)
        {
            int curStop = q.front();
            us.insert(curStop);
            q.pop();
            n--;

            if(curStop == target)
                return numberOfBuses-1;

            // buses that comes at this stop
            for(int x : mp[curStop])
            {
                // stops that are covered by those buses (x) that comes at stop "curStop"
                for(int y : routes[x])
                {
                    if(us.find(y) == us.end())
                    {
                        us.insert(y);
                        q.push(y);
                    }
                }
                routes[x].clear();      // optimization --> avoid looking for bus that is already checked
            }
        }
    }

    return -1;
}
