/*

You are given an array of integers stones where stones[i] is the weight of the ith stone.

We are playing a game with the stones. On each turn, we choose the heaviest two stones and smash them together.
Suppose the heaviest two stones have weights x and y with x <= y. The result of this smash is:

If x == y, both stones are destroyed, and
If x != y, the stone of weight x is destroyed, and the stone of weight y has new weight y - x.
At the end of the game, there is at most one stone left.

Return the smallest possible weight of the left stone. If there are no stones left, return 0

*/

#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>


int lastStoneWeight(std::vector<int>& stones);          // max-heap
int lastStoneWeight2(std::vector<int>& stones);         // bucket sort


int main()
{
    std::vector<int> vec;
    int n,k;

    std::cout << "Enter size of array: ";
    std::cin >> n;

    std::cout << "Enter array elements: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }

    int last = lastStoneWeight(vec);

    std::cout << "\nLast Stone weight: " << last;
    return 0;
}



int lastStoneWeight(std::vector<int>& stones)
{
    int y,x;
    std::priority_queue<int> pq(stones.begin(), stones.end());                // max heap

    /*
    for(int i=0; i<stones.size(); i++)
        pq.push(stones[i]);
    */

    while(!pq.empty() && pq.size() != 1)
    {
        y = pq.top();
        pq.pop();
        x = pq.top();
        pq.pop();

        if(x < y)
            pq.push(y-x);

    }

    return pq.empty() ? 0 : pq.top();
}


/*

But we can do better, right? If you have done a few of these problems you might know to use BucketSort with has constant access and no typical "sorting", we can do O(n) time.

However, it is more accurate to say the time would be O(n + maxStoneWeight) because we will build a bucket for every possible weight. And usually a O(n + 1000) would be a
great solution, but the test cases here have a very short input size. the number of stones goes only from 0 to 30, so this solution actually performs worse than O(n)
since n is at most 30! O(30) == O(1030) but 30 < 1030. Both have the same complexity, but the first runs faster, and you might have not noticed why unless you
check the inputs given in the tests.

*/


int lastStoneWeight2(std::vector<int>& stones)
{
    int[] buckets = new int[1001];

    for(int stone: stones)
      buckets[stone]++;

    int i = 1000;
    int j;

    while(i > 0)
    {
        if(buckets[i] == 0)
            i--;

        else
        {
            buckets[i] = buckets[i] % 2;
            if(buckets[i] != 0)
            {
                j = i-1;
                while(j > 0 && buckets[j] == 0)
                    j--;

                if(j == 0)
                    return i;

                buckets[i - j]++;
                buckets[j]--;
                i--;
            }
        }
    }

    return 0;
}
