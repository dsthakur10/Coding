
// Time Based Key-Value Store

/*

Design a time-based key-value data structure that can store multiple values for the same key at different timestamps
and retrieve the key's value at a certain timestamp.

Implement the TimeMap class:

    - TimeMap()
        Initializes the object of the data structure.

    - void set(String key, String value, int timestamp)
        Stores the key key with the value value at the given time timestamp.

    - String get(String key, int timestamp)
        Returns a value such that set was called previously, with timestamp_prev <= timestamp.
        If there are multiple such values, it returns the value associated with the largest timestamp_prev.
        If there are no values, it returns "".


Example 1:

Input:
["TimeMap", "set", "get", "get", "set", "get", "get"]
[[], ["foo", "bar", 1], ["foo", 1], ["foo", 3], ["foo", "bar2", 4], ["foo", 4], ["foo", 5]]

Output:
[null, null, "bar", "bar", null, "bar2", "bar2"]

Explanation
TimeMap timeMap = new TimeMap();
timeMap.set("foo", "bar", 1);  // store the key "foo" and value "bar" along with timestamp = 1.
timeMap.get("foo", 1);         // return "bar"
timeMap.get("foo", 3);         // return "bar", since there is no value corresponding to foo at timestamp 3 and timestamp 2, then the only value is at timestamp 1 is "bar".
timeMap.set("foo", "bar2", 4); // store the key "foo" and value "bar2" along with timestamp = 4.
timeMap.get("foo", 4);         // return "bar2"
timeMap.get("foo", 5);         // return "bar2

*/



// Method-1 --> Map with  <time , {key, value}>
// Since timestamp is always unique, we can have map without any collison
// Find iterator to given timestamp & search all the way down to begin of map & return the first matching key value

class TimeMap {
public:
    map<int, pair<string, string>> mp;

    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        mp[timestamp] = {key, value};
    }

    string get(string key, int timestamp) {

        if(timestamp < mp.begin()->first)
            return "";

        auto it = mp.find(timestamp);

        if(it == mp.end())
            it--;

        for(; it != mp.begin(); it--)
        {
            if(it->first <= timestamp && it->second.first == key)
                return it->second.second;
        }

        if(it->first <= timestamp && it->second.first == key)
                return it->second.second;

        return "";
    }
};



// Method-2 --> Uses Hashmap of map --> Stores "key" as key & <timestamp, value> as map
// This way we can store multiple values corresponding to the same "key" value.
// Also, since timestamp is unique, we can have ordered values according to timestamp.
// Use inbuilt upper_bound function to get the first timestamp value <= given timestamp

class TimeMap {
public:
    unordered_map <string, map<int, string>> mp;
    //HashMap of <string, map>

    TimeMap() {

    }

    void set(string key, string value, int timestamp) {
        //mp[key].insert({timestamp, value});
        mp[key][timestamp] = value;
    }

    // find last occurrence of key-value below timestamp
    string get(string key, int timestamp) {

        auto it = mp[key].upper_bound(timestamp);       // gives the largest timestamp value <= given timestamp

        if(it == mp[key].begin())
            return "";

        it--;
        return it->second;
    }
};
