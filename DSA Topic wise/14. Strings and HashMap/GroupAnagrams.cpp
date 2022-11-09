/*

Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]

Example 2:
Input: strs = [""]
Output: [[""]]

Example 3:
Input: strs = ["a"]
Output: [["a"]]

*/


vector<vector<string>> groupAnagrams(vector<string>& strs) {

    vector<vector<string>> result;
    unordered_map<string, vector<string>> mp;

    for(string str : strs)
    {
        string temp = str;
        sort(temp.begin(), temp.end());
        mp[temp].push_back(str);
    }

    for(auto it : mp)
        result.push_back(it.second);

    return result;
}
