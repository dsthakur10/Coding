/*

Given an array of strings words and an integer k, return the k most frequent strings.

Return the answer sorted by the frequency from highest to lowest. Sort the words with the same frequency by their
lexicographical order.

Example 1:
Input: words = ["i","love","leetcode","i","love","coding"], k = 2
Output: ["i","love"]
Explanation: "i" and "love" are the two most frequent words.
Note that "i" comes before "love" due to a lower alphabetical order.

Example 2:
Input: words = ["the","day","is","sunny","the","the","the","sunny","is","is"], k = 4
Output: ["the","is","sunny","day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
with the number of occurrence being 4, 3, 2 and 1 respectively.

*/


// Method-1

typedef pair<int, string> pis;

struct compare
{
    bool operator()(const pis& a, const pis& b)
    {
        if(a.first == b.first)
            return a.second < b.second;

        return a.first > b.first;
    }
};


vector<string> topKFrequent(vector<string>& words, int k) {

    vector<string> result;
    unordered_map<string, int> mp;
    priority_queue<pis, vector<pis>, compare> pq;
    int n = words.size();

    for(int i=0; i<n; i++)
        mp[words[i]]++;

    for(auto it = mp.begin(); it != mp.end(); it++)
    {
        pq.push({it->second, it->first});

        if(pq.size() > k)
            pq.pop();
    }

    while(!pq.empty())
    {
        result.push_back(pq.top().second);
        pq.pop();
    }

    reverse(begin(result), end(result));
    return result;
}



// Method-2

typedef pair<int, string> pis;

struct compare
{
    bool operator()(const pis& a, const pis& b)
    {
        if(a.first == b.first)
            return a.second < b.second;

        return a.first > b.first;
    }
};


static bool comp2(const pis &a, pis &b) {
    if(a.first == b.first)
        return a.second < b.second;
    return a.first > b.first;
}


vector<string> topKFrequent(vector<string>& words, int k) {

    vector<string> result;
    unordered_map<string, int> mp;
    priority_queue<pis, vector<pis>, compare> pq;
    int n = words.size();

    for(int i=0; i<n; i++)
        mp[words[i]]++;

    for(auto it = mp.begin(); it != mp.end(); it++)
    {
        pq.push({it->second, it->first});

        if(pq.size() > k)
            pq.pop();
    }

    while(!pq.empty())
    {
        result.push_back(pq.top().second);
        pq.pop();
    }

    sort(begin(result), end(result), comp2);
    vector<string> ans;
    for(pis &p : result)
         ans.push_back(p.second);
    return result;
}



// Method-3

