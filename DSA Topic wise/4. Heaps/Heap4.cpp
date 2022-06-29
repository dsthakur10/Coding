/*
K-CLOSEST POINT TO ORIGIN

Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane and an integer k, return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance (i.e., √((x1 - x2)^2 + (y1 - y2)^2)).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order that it is in).

*/


#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
typedef std::pair<int,std::pair<int,int>> ppi;

std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k);


int main()
{
    std::vector<std::vector<int>> points = {{3,3},{5,-1},{-2,4}};
    int k;

    std::cout << "\nArray:\n";
    for(int i=0;i<points.size();i++)
    {
        for(int j=0; j<2; j++)
            std::cout << points[i][j] << " ";
        std::cout << "\n";
    }

    std::cout << "\nEnter k-value:";
    std::cin >> k;

    points = kClosest(points,k);

    std::cout << "\nk-closest points to origin(0,0):\n";
    for(int i=0;i<points.size();i++)
    {
        for(int j=0; j<2; j++)
            std::cout << points[i][j] << " ";
        std::cout << "\n";
    }

}



std::vector<std::vector<int>> kClosest(std::vector<std::vector<int>>& points, int k)
{
    std::vector<std::vector<int>> closest;
    std::priority_queue<ppi> pq;

    std::cout << "\nChecking";

    for(int i=0;i<points.size();i++)
    {
        pq.push(std::make_pair(points[i][0]*points[i][0] + points[i][1]*points[i][1], std::make_pair(points[i][0], points[i][1])));

        if(pq.size() > k)
            pq.pop();
    }

    std::cout << "\nChecking";

    while(!pq.empty())
    {
        closest.push_back({pq.top().second.first, pq.top().second.second});
        pq.pop();
    }

    return closest;
}
