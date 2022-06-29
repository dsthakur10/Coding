#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
typedef pair<int, int> pi;





int main()
{
    vector<vector<int>> mat =
    {{1,1,0,0,0},
     {1,1,1,1,0},
     {1,0,0,0,0},
     {1,1,0,0,0},
     {1,1,1,1,1}};

     vector<int> index;

     index = kWeakestRows(mat, 3);

     for(int i=0; i<3; i++)
        cout << index[i] << " ";

     return 0;
}



int findEndIndexOfOne(vector<int> row)
{
    if(row[0] == 0)
        return -1;

    if(row[row.size()-1] == 1)
        return row.size()-1;

    int low = 0, high = row.size()-1;
    int mid;

    while(low <= high)
    {
        int mid = (low+high)/2;

        if(row[mid] == 1 && row[mid+1] == 0)
            return mid;

        else if(row[mid] == 0 && row[mid-1] == 1)
                return mid-1;

        else if(row[mid] == 1 && row[mid+1] == 1)
            low = mid+1;

        else if(row[mid] == 0 && row[mid-1] == 0)
            high = mid-1;
    }

    return low;
}



int findIndexOfOne2(vector<int>& v)
{
    int low = 0 , high = v.size()-1;

    while(low <= high)
    {
        int mid = low + (high-low) / 2;

        if(v[mid] == 0)
            high = mid-1;

        else
            low = mid+1;
    }

    return low;
}



// Min-heap --> Space = O(N)

vector<int> kWeakestRows(vector<vector<int>>& mat, int k)
{
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    vector<int> index;

    for(int i=0; i<mat.size(); i++)
    {
        int x = findEndIndexOfOne(mat[i]);

        pq.push(make_pair(x, i));
    }

    while(k > 0)
    {
        int x = (pq.top()).second;
        pq.pop();

        index.push_back(x);
        k--;
    }

    return index;
}



// Max-heap --> Space = O(k)

vector<int> kWeakestRows2(vector<vector<int>>& mat, int k)
{
    priority_queue<pi> pq;
    vector<int> index;

    for(int i=0; i<mat.size(); i++)
    {
        int x = findEndIndexOfOne(mat[i]);

        pq.push(make_pair(x, i));

        if(pq.size() > k)
            pq.pop();
    }

    while(!pq.empty())
    {
        int x = (pq.top()).second;
        pq.pop();

        index.insert(index.begin(), x);
    }


    return index;

}
