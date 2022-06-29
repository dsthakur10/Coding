/*
You are given an integer array score of size n, where score[i] is the score of the ith athlete in a competition. All the scores are guaranteed to be unique.

The athletes are placed based on their scores, where the 1st place athlete has the highest score, the 2nd place athlete has the 2nd highest score, and so on.
The placement of each athlete determines their rank:

The 1st place athlete's rank is "Gold Medal".
The 2nd place athlete's rank is "Silver Medal".
The 3rd place athlete's rank is "Bronze Medal".
For the 4th place to the nth place athlete, their rank is their placement number (i.e., the xth place athlete's rank is "x").

Return an array answer of size n where answer[i] is the rank of the ith athlete.

Input: score = [5,4,3,2,1]
Output: ["Gold Medal","Silver Medal","Bronze Medal","4","5"]
Explanation: The placements are [1st, 2nd, 3rd, 4th, 5th].
Example 2:

Input: score = [10,3,8,9,4]
Output: ["Gold Medal","5","Bronze Medal","Silver Medal","4"]
Explanation: The placements are [1st, 5th, 3rd, 2nd, 4th].

*/


#include<iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
#include<string>

typedef std::pair<int,int> pi;

std::vector<std::string> findRelativeRanks(std::vector<int>& score);            // max-heap
std::vector<std::string> findRelativeRanks2(std::vector<int>& score);           // map


int main()
{
    std::vector<int> vec;
    std::vector<std::string> strvec;
    int n,k;

    std::cout << "Enter size of array: ";
    std::cin >> n;

    std::cout << "Enter array elements: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }

    strvec = findRelativeRanks2(vec);

    std::cout << "\n";
    for(int i=0; i<strvec.size(); i++)
        std::cout << strvec[i] << " ";

    return 0;

}



std::vector<std::string> findRelativeRanks(std::vector<int>& score)
{
    std::priority_queue<pi> pq;
    std::vector<std::string> vec(score.size(),"\0");
    std::pair<int,int> p;

    for(int i=0; i<score.size(); i++)
        pq.push(std::make_pair(score[i],i));

    int counter = 1;
    std::vector<std::string>::iterator it;

    while(!pq.empty())
    {
        it = vec.begin();
        p = pq.top();

        if(counter==1)
        {
            //vec.insert(it+pq.top().second,"Gold Medal");              // this will increase the vector size by 1.
            vec[p.second] = "Gold Medal";
        }

        else if(counter==2)
        {
            //vec.insert(it+pq.top().second,"Silver Medal");
            vec[p.second] = "Silver Medal";
        }

        else if(counter==3)
        {
            //vec.insert(it+pq.top().second,"Bronze Medal");
            vec[p.second] = "Bronze Medal";
        }

        else
        {
            //vec.insert(it+pq.top().second,std::to_string(counter));
            vec[p.second] = std::to_string(counter);
        }

        counter++;
        pq.pop();
    }

    return vec;
}



std::vector<std::string> findRelativeRanks2(std::vector<int>& score)
{
    std::vector<std::string> vecstr(score.size(),"\0");
    std::map<int,int,std::greater<int>> mp;
    std::map<int,int>::iterator it;

    for(int i=0; i<score.size(); i++)
    {
        mp[score[i]] = i;
    }

    for (it=mp.begin(); it!=mp.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    int counter = 1;
    for(it=mp.begin(); it!=mp.end(); ++it)
    {
        if(counter==1)
        {
            vecstr[it->second] = "Gold Medal";
        }

        else if(counter==2)
        {
            vecstr[it->second] = "Silver Medal";
        }

        else if(counter==3)
        {
            vecstr[it->second] = "Bronze Medal";
        }

        else
        {
            vecstr[it->second] = std::to_string(counter);
        }

        counter++;
    }

    return vecstr;
}
