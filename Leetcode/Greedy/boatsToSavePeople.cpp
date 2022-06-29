
// Method-1 --> Sorting - O(nlogn) time

/*

If the heaviest person can share a boat with the lightest person, then do so. Otherwise, the heaviest person can't pair with anyone,
so they get their own boat.

The reason this works is because if the lightest person can pair with anyone, they might as well pair with the heaviest person.

*/

int numRescueBoats(vector<int>& people, int limit)
{
    sort(people.begin(), people.end());

    int i = 0, j = people.size()-1;
    int count=0;

    while(i < j)
    {
        if(people[i] + people[j] <= limit)
        {
            i++;
            j--;
        }

        else
        {
            j--;
        }

        count++;
    }

    if(i==j)
        count++;

    return count;
}

