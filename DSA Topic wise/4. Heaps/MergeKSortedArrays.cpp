/*

You have been given ‘K’ different arrays/lists, which are sorted individually (in ascending order).
You need to merge all the given arrays/list such that the output array/list should be sorted in ascending order.

*/


// < value, < array number, element number in given array >>

typedef pair<int, pair<int, int>> ppi;

vector<int> mergeKSortedArrays(vector<vector<int>>& kArrays, int k)
{
    vector<int> result;
    priority_queue<ppi, vector<ppi>, greater<ppi>> pq;

    for(int i=0; i<k; i++)
    {
        if(!kArrays[i].empty())
            pq.push({kArrays[i][0], {i, 0}});
    }

    while(!pq.empty())
    {
        int value = pq.top().first;
        int arrayIndex = pq.top().second.first;
        int elementIndex = pq.top().second.second;

        pq.pop();

        result.push_back(value);

        if(elementIndex + 1  !=  kArrays[arrayIndex].size())
            pq.push({kArrays[arrayIndex][elementIndex+1], {arrayIndex, elementIndex+1}});
    }

    return result;
}
