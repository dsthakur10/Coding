/*

CONNECT ROPES TO MINIMISE THE COST

There are given N ropes of different lengths, we need to connect these ropes into one rope.
The COST TO CONNECT TWO ROPES is equal to the SUM OF THEIR LENGTHS. We need to connect the ropes with minimum cost.

NOTE:
    - Greedy approach - use 2 minimum length ropes at any time.
*/


#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>


int minCost(std::vector<int> len);


int main()
{
    //std::vector<int> vec = {3,2,3,1,2,4,5,5,6};
    std::vector<int> vec;
    int n,k;

    std::cout<< "Enter size of array: ";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0;i<n;i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }


    std::cout << "\nArray:\n";
    for(int i=0;i<n;i++)
        std::cout << vec[i] << " ";

    std::cout << "\n\nMINIMUM COST = "<< minCost(vec);

    return 0;

}



int minCost(std::vector<int> len)
{
    int first, second, sum=0, cost = 0;
    //std::priority_queue<int, std::vector<int>, std::greater<int>> pq;       // minheap

    std::make_heap(len.begin(), len.end(), std::greater<int>());                                  // converting vector into min-heap

    while(!len.empty())
    {
        if(sum != 0)
        {
            len.push_back(sum);
            std::push_heap(len.begin(), len.end(), std::greater<int>());
        }

        first = len.front();
        std::pop_heap(len.begin(), len.end(), std::greater<int>());
        len.pop_back();

        second = len.front();
        std::pop_heap(len.begin(), len.end(), std::greater<int>());
        len.pop_back();

        cost += first + second;

        sum = first + second;                       // push sum of 2 minimum elements & not the cost itself

/*
        len.push_back(sum);
        std::push_heap(len.begin(), len.end(), std::greater<int>());                // Cannot put in here because that would place an extra element(last) in heap
*/
        std::cout << "\nfirst = "<< first << " | second = " << second << " | COST = " << cost;
    }

    return cost;
}
