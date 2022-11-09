
/*

Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.

Return any possible rearrangement of s or return "" if not possible.

Example 1:
Input: s = "aab"
Output: "aba"

Example 2:
Input: s = "aaab"
Output: ""

*/


// LOGIC :
/*
    --> Our goal is to rearrange the string such that no 2 adjacent letters are same.
    --> This will require greedy approach --> Start placing letters of string according to the order of frequency
        (High -> low) one at a time.
    --> In every iteration, cover all the unique letters (if not exhausted)
    --> This will make sure that no 2 letters will get placed adjacently.

    --> When will we not able to fulfill our goal ?
        When any letter's freq > (n+1)/2 --> a letter appears more than 50% of times in a string

    --> We can use Max-Heap for this. every element of heap will contain <freq, letter>
    --> Heap will be ordered according to frequency (High -> Low) [mandatory ordering]
    --> In case the letter's having same frequency, we might choose secondary ordering (lexicographical) to get
        perfect answer [optional/secondary ordering]

    --> Even if we do not follow secondary ordering, result won't get impacted because heap internally uses its own
        ordering mechanism in case there is a tie in 1st element comparison.

    Type-1 PQ --> Using custom comparator
              --> This will perform ordering Highest frequency first.
              --> If frequency is same, lowest lexicographical order first

    Type-2 PQ --> Using default
              --> This will perform ordering Highest frequency first.
              --> If frequency is same, highest lexicographical order first (default mechanism of PQ)

*/


typedef pair<int, char> pic;

struct myComparator
{
    bool operator()(pic const& p1, pic const& p2)
    {
        if(p1.first < p2.first)
            return true;

        else if(p1.first == p2.first)
            return p1.second > p2.second;

        return false;
    }
};


string reorganizeString(string s) {

    int n = s.size();
    string ans;
    unordered_map<char, int> mp;    // <char, freq>
    //priority_queue< pic, vector<pic>, myComparator > pq;
    priority_queue< pic > pq;

    // HashMap to store frequency
    for(char ch : s)
    {
        mp[ch]++;

        if(mp[ch] > (n+1)/2)
            return "";
    }

    for(auto it: mp)
        pq.push({it.second, it.first});

    while(!pq.empty())
    {
        // pop the top element (Element having highest freq)

        int freq1 = pq.top().first;
        char ch1 = pq.top().second;
        pq.pop();

        // Case-1 --> Last letter & current letter are NOT equal.

        if(ans.empty() || ans.back() != ch1)
        {
            ans.push_back(ch1);
            freq1--;

            if(freq1 != 0)              // push it back into heap if there are more occurrences (after DEC)
                pq.push({freq1, ch1});
        }

        // Case-2 --> Last letter & current letter are EQUAL
        //        --> You need some other letter, i.e. next most frequent letter (Greedy approach)

        else
        {
            // POP 2nd most frequenct element
            int freq2 = pq.top().first;
            char ch2 = pq.top().second;
            pq.pop();

            ans.push_back(ch2);
            freq2--;

            if(freq2 != 0)              // push it back into heap if there are more occurrences (after DEC)
                pq.push({freq2, ch2});

            pq.push({freq1, ch1});      // push the top element back without DEC as it was never used.
        }
    }

    return ans;
}
