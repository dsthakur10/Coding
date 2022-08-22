/*

Given an unsorted array of integers, return the length of the longest consecutive elements sequence.

You must write an algorithm that runs in O(n) time.

Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9

*/



class UnionFind {

private:
    vector<int> root;
    vector<int> rank;
    vector<int> size;

public:
    UnionFind(int sz) : root(sz), rank(sz), size(sz)
    {
        for (int i = 0; i < sz; i++)
        {
            root[i] = i;
            rank[i] = 1;
            size[i] = 1;
        }
    }


    int find(int x) {
        if (x == root[x])
            return x;

        return root[x] = find(root[x]);
    }


    void unionSet(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
                root[rootY] = rootX;

            else if (rank[rootX] < rank[rootY])
                root[rootX] = rootY;

            else
            {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }

        size[rootX] += size[rootY];
        size[rootY] = size[rootX];
    }


    bool connected(int x, int y) {
        return find(x) == find(y);
    }


    int getLargestComponentSize()
    {
        int maxSize = 0;
        for(int i=0; i<root.size(); i++)
        {
            if(root[i] == i && maxSize < size[i])
                maxSize = size[i];
        }

        return maxSize;
    }

};



int longestConsecutive(vector<int>& nums) {

    int N = nums.size();
    UnionFind uf(N);
    unordered_map<int, int> mp;     // <int, int> --> <value, index>

    for(int i=0; i<N; i++)
    {
        if(mp.find(nums[i]) != mp.end())
            continue;

        if(mp.find(nums[i]) == mp.end())
        {
            if(mp.find(nums[i]-1) != mp.end())
                uf.unionSet(i, mp[nums[i]-1]);

            if(mp.find(nums[i]+1) != mp.end())
                uf.unionSet(i, mp[nums[i]+1]);
        }

        mp[nums[i]] = i;
    }

    return uf.getLargestComponentSize();
}

