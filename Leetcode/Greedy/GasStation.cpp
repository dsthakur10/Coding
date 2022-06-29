
/*

We know if we run out of fuel say at some ith gas station.
All the gas station between ith and starting point are bad starting point as well.

So, this means we can start trying at next gas station on the i + 1 station

*/


int canCompleteCircuit(vector<int>& gas, vector<int>& cost)
{

    int totalFuel = 0;      // to keep track of overall Fuel consumption(cost[]) Vs overall Fuel available[gas]
    int fuel = 0;           // to keep track of starting index. If at some point fuel becomes <0 --> modify start to next coming index
    int start = 0;          // starting index of gas station to finish journey

    for(int i=0; i<gas.size(); i++)
    {
        totalFuel += gas[i] - cost[i];
        fuel += gas[i] - cost[i];

        if(fuel < 0)
        {
            start = i+1;
            fuel = 0;
        }

    }

    return ((totalFuel < 0) ? -1 : start );
}
