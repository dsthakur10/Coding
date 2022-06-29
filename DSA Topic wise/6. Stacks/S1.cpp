// Daily Temperatures

/*
Given an array of integers temperatures represents the daily temperatures, return an array answer such that
answer[i] is the number of days you have to wait after the ith day to get a warmer temperature.
If there is no future day for which this is possible, keep answer[i] == 0 instead.

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:
Input: temperatures = [30,60,90]
Output: [1,1,0]

*/

// Next Greater to Right
vector<int> dailyTemperatures(vector<int>& temperatures)
{
    int n = temperatures.size();
    vector<int> result;
    stack<int> st;

    for(int i=n-1; i>=0; i--)
    {
        // warmer temperature --> strictly greater

            while(!st.empty() &&
                  temperatures[i] >= temperatures[st.top()])
                st.pop();

            if(st.empty())
                result.push_back(0);

            else
                result.push_back(st.top() - i);


        st.push(i);
    }

    reverse(result.begin(), result.end());
    return result;
}



// O(1) space

vector<int> dailyTemperatures(vector<int>& temperatures) {

    int n = temperatures.size();
    vector<int> result(n, 0);
    int hottest = 0, days;

    for(int i=n-1; i>=0; i--)
    {
        if(hottest <= temperatures[i])
        {
            hottest = temperatures[i];
            continue;
        }

        days = 1;
        while(i+days < n && temperatures[i+days] <= temperatures[i])
            days += result[i+days];

        result[i] = days;
    }

    return result;
}
