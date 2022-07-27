/*

KTH SMALLEST ELEMENT IN A SORTED MATRIX

Given an n x n matrix where each of the rows and columns is sorted in ascending order, return the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

You must find a solution with COMPLEXITY BETTER THAN O(n^2).

*/

#include<climits>
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

typedef std::pair<int, std::pair<int,int>> ppi;

int kthSmallest(std::vector<std::vector<int>>& matrix, int k);              // min-heap
int kthSmallest2(std::vector<std::vector<int>>& matrix, int k);             // min-heap
int kthSmallest3(std::vector<std::vector<int>>& matrix, int k);             // max-heap


int main()
{
    int n,k;
    std::vector<std::vector<int>> vec = {{1,7,16}, {4,9,24}, {10,20,50}};
    std::vector<int> myvec;

    n = vec.size();
/*
    std::cout << "Enter the size of a N*N array:";
    std::cin >> n;

    std::cout << "Enter array elements: \n";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n;j++)
        {
            std::cin >> k;
            myvec.push_back(k);
        }

        vec.push_back(myvec);
        myvec.clear();
    }
*/
    std::cout << "Given Array:\n";
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n;j++)
            std::cout << vec[i][j] << " ";
        std::cout << "\n";
    }

    std::cout << "Enter k value (kth-smallest): ";
    std::cin >> k;

    int res = kthSmallest2(vec,k);
    std::cout << "\n\n" << k << "th smallest element in sorted matrix = " << res;

    return 0;

}


// -------------------- Method-1 -----------------------
/*
    Use min-heap & store the elements until the count of pop() operations becomes k (kth smallest element).
    Idea is to store the elements in min-heap in smart way, i.e. store only necessary elements in heap.

    Necessary elements --> an element cannot be greater than its rightside & bottom elements. So no need to store all those elements unnecessarily.

    Once you pop ith smallest element from heap --> insert its immediate right & immediate bottom element.

*/


int kthSmallest(std::vector<std::vector<int>>& matrix, int k)
{
    std::priority_queue<ppi, std::vector<ppi>, std::greater<ppi>> pq;           // min-heap
    int i, j, n, current;
    n = matrix.size();

    pq.push(std::make_pair(matrix[0][0], std::make_pair(0,0)));
    matrix[0][0] = INT_MIN;

    while(k>0)
    {
        current = pq.top().first;
        i = pq.top().second.first;
        j = pq.top().second.second;

        pq.pop();
        k--;

        if(i+1 != n && j!= n && matrix[i+1][j] != INT_MIN)                                            // column neighbor
        {
            pq.push(std::make_pair(matrix[i+1][j], std::make_pair(i+1,j)));
            matrix[i+1][j] = INT_MIN;
        }


        if(i != n && j+1!= n && matrix[i][j+1] != INT_MIN)                                            // row neighbor
        {
            pq.push(std::make_pair(matrix[i][j+1], std::make_pair(i,j+1)));
            matrix[i][j+1] = INT_MIN;
        }

        std::cout << "\nCurrent popped = " << current;
    }

    return current;
}


// ------------------ Method-2 --------------------

/*

Since each of the rows in matrix are already sorted, we can understand the problem as finding the kth smallest element from amongst M sorted rows.

We start the pointers to point to the beginning of each rows, then we iterate k times, for each time ith, the top of the minHeap is the ith smallest element in the matrix.

We pop the top from the minHeap then add the next element which has the same row with that top to the minHeap.

#elements to be inserted in min-heap initially = min(n,k) ---> n = #rows


*/

int kthSmallest2(std::vector<std::vector<int>>& matrix, int k)
{
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;           // min-heap

    int r, c, n, current;
    n = matrix.size();

    for(int r=0; r<std::min(n,k); r++)              // initially push all the 1st elements of every row (If k < #rows, push only 1st k rows)
        pq.push({matrix[r][0],r,0});

    while(k>0)
    {
        current = pq.top()[0];                      // pop the minimum element & then push its immediate right neighbor.
        r = pq.top()[1];
        c = pq.top()[2];

        pq.pop();

        if(c+1 < n)
            pq.push({matrix[r][c+1], r, c+1});

        k--;
    }

    return current;
}
