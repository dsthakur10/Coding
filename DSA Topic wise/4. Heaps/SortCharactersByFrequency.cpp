
/*

Given a string s, sort it in decreasing order based on the frequency of the characters.
The frequency of a character is the number of times it appears in the string.

Return the sorted string. If there are multiple answers, return any of them.

*/


typedef pair<int, char> pic;

string frequencySort(string s) {

    // <number, frequency>
    unordered_map<char, int> freq;
    priority_queue<pic> pq;

    for(char x : s)
        freq[x]++;

    for(auto it : freq)
        pq.push({it.second, it.first});

    string result;
    while(!pq.empty())
    {
        int freq = pq.top().first;
        char ch = pq.top().second;
        pq.pop();

        for(int counter = 0; counter < freq; counter++)
            result.push_back(ch);
    }

    return result;
}
