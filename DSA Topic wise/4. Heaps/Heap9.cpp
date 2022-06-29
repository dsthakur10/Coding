/*
You are given an m x n binary matrix mat of 1's (representing soldiers) and 0's (representing civilians). The soldiers are positioned in front of the civilians.
That is, all the 1's will appear to the left of all the 0's in each row.

A row i is weaker than a row j if one of the following is true:

    - The number of soldiers in row-i < the number of soldiers in row-j.
    - Both rows have the same number of soldiers and i < j.

Return the indices of the k weakest rows in the matrix ordered from weakest to strongest.

Example 1:

Input: mat =
[[1,1,0,0,0],
 [1,1,1,1,0],
 [1,0,0,0,0],
 [1,1,0,0,0],
 [1,1,1,1,1]],
k = 3
Output: [2,0,3]
Explanation:
The number of soldiers in each row is:
- Row 0: 2
- Row 1: 4
- Row 2: 1
- Row 3: 2
- Row 4: 5
The rows ordered from weakest to strongest are [2,0,3,1,4].

Example 2:

Input: mat =
[[1,0,0,0],
 [1,1,1,1],
 [1,0,0,0],
 [1,0,0,0]],
k = 2
Output: [0,2]
Explanation:
The number of soldiers in each row is:
- Row 0: 1
- Row 1: 4
- Row 2: 1
- Row 3: 1
The rows ordered from weakest to strongest are [0,2,3,1].

*/


#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>


std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k);    // O(nlogn) + O(nlogk) + O(k) --> matrix using binary search & max-heap & reverse sorting result
std::vector<int> kWeakestRows2(std::vector<std::vector<int>>& mat, int k);   // O(nlogn) + O(k) --> matrix using binary search & multimap & storing results in array.


int main()
{
    std::vector<std::vector<int>> matrix =
                                            {{1,1,0,0,0},
                                             {1,1,1,1,0},
                                             {1,0,0,0,0},
                                             {1,1,0,0,0},
                                             {1,1,1,1,1},} ;
    std::vector<int> row;
    int n,m,k;
/*
    std::cout << "Enter n*m matrix size: ";
    std::cin >> n >> m;

    std::cout << "\nEnter matrix elements: ";

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            std::cin >> k;
            row.push_back(k);
        }

        matrix.push_back(row);
        row.clear();
    }
*/
    std::cout << "\n\n";
    for(int i=0; i<matrix.size(); i++)
    {
        for(int j=0; j<matrix[i].size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }

        std::cout << "\n";
    }


    std::cout << "\nEnter weakest rows number: ";
    std::cin >> k;

    row = kWeakestRows2(matrix, k);

    std::cout << "\n\nRESULTS:";
    for(int i=0; i< row.size(); i++)
        std::cout << row[i] << " ";

    return 0;

}



std::vector<int> kWeakestRows(std::vector<std::vector<int>>& mat, int k)
{
    std::priority_queue<std::pair<int,int>> pq;             // max-heap
    std::vector<int> weakest;
    int counter;
    std::vector<int>::iterator low,up;


    for(int i=0; i<mat.size(); i++)                                             // O(n)
    {
        low = std::lower_bound(mat[i].begin(),mat[i].end(),1,std::greater<int>());          // O(logn)
        up = std::upper_bound(mat[i].begin(),mat[i].end(),1,std::greater<int>());

        counter = up - low;

        pq.push(std::make_pair(counter,i));

        if(pq.size() > k)                                                                   // O(logk)
            pq.pop();

        //std::cout << counter << " ";
    }

    while(!pq.empty())
    {
        weakest.push_back(pq.top().second);

        pq.pop();
    }

    std::reverse(weakest.begin(), weakest.end());                               // O(k)
    return weakest;

}



std::vector<int> kWeakestRows2(std::vector<std::vector<int>>& mat, int k)
{
    std::multimap<int,int> mp;
    std::vector<int> weakest;
    int counter;
    std::vector<int>::iterator low,up;


    for(int i=0; i<mat.size(); i++)                                             // O(n)
    {
        low = std::lower_bound(mat[i].begin(),mat[i].end(),1,std::greater<int>());          // O(logn)
        up = std::upper_bound(mat[i].begin(),mat[i].end(),1,std::greater<int>());

        counter = up - low;

        mp.insert(std::pair<int,int>(counter,i));                               // O(logn)

    }

    for(std::multimap<int,int>::iterator it = mp.begin(); it!=mp.end(); it++)
        std::cout << it->first << " " << it->second << "\n";

    for(std::multimap<int,int>::iterator it = mp.begin(); k>0 ; it++)           // O(k)
    {
        weakest.push_back(it->second);
        k--;
    }

    return weakest;
}
