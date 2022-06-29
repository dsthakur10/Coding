
// Rain Water Trapping


#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<climits>

using namespace std;

vector<int> maximumLeft(vector<int> arr);
vector<int> maximumRight(vector<int> arr);
vector<int> maximumLeft2(vector<int> arr);
vector<int> maximumRight2(vector<int> arr);

int trap(vector<int>& height);      // brute force --> O(n^2)
int trap2(vector<int>& height);     // Dynamic programming --> Finding leftMax[] & rightMax[] --> O(n)
int trap3(vector<int>& height);     // Stack
int trap4(vector<int>& height);     // Two pointers


int main()
{
    vector<int> vec = {0,1,0,2,1,0,1,3,2,1,2,1};
    //vector<int> vec = {4,2,3};
    //vector<int> vec = {4,2,0,3,2,5};

    int trapped = trap(vec);

    maximumLeft(vec);
    maximumRight(vec);
    cout << "\nMaximum water trapped = " << trapped;
}



// Method-1 --> Brute Force --> O(n^2) --> TLE

int trap(vector<int>& height)
{
    int trapped = 0, n = height.size();

    for(int i=0; i<n; i++)
    {
        int left_max = INT_MIN;
        int right_max = INT_MIN;
        // get max neighbor in left
        for(int j=i-1; j>=0; j--)
        {
            if(height[i] <= height[j])
                left_max = max(left_max, height[j]);
        }

        // get max neighbor in right
        for(int j=i+1; j<n; j++)
        {
            if(height[i] <= height[j])
                right_max = max(right_max, height[j]);
        }

        if(left_max != INT_MIN && right_max != INT_MIN)
            trapped += min(left_max, right_max) - height[i];
    }

    return trapped;
}


// Dynamic Programming

int trap2(vector<int>& height)
{
    int trapped = 0, n = height.size();
    vector<int> left = maximumLeft(height);
    vector<int> right = maximumRight(height);

    for(int i=0; i<n; i++)
    {
        if(left[i] != -1 && right[i] != -1)
            trapped += min(height[left[i]], height[right[i]]) - height[i];
    }

    return trapped;
}


vector<int> maximumLeft(vector<int> arr)
{
    int n = arr.size();
    vector<int> left(n,-1);
    stack<int> st;

    for(int i=0; i<n; i++)
    {
        if(st.empty())
            st.push(i);

        else if(arr[st.top()] > arr[i])
            left[i] = st.top();

        else
        {
            st.pop();
            st.push(i);
        }
    }


    cout << "\nLeft Maximum = ";
    for(int i=0; i<n; i++)
        cout << left[i] << " ";
    return left;
}


vector<int> maximumRight(vector<int> arr)
{
    int n = arr.size();
    vector<int> right(n,-1);
    stack<int> st;

    for(int i=n-1; i>=0; i--)
    {
        if(st.empty())
            st.push(i);

        else if(arr[st.top()] > arr[i])
            right[i] = st.top();

        else
        {
            st.pop();
            st.push(i);
        }
    }

    cout << "\nRight Maximum = ";
    for(int i=0; i<n; i++)
        cout << right[i] << " ";
    return right;
}



vector<int> maximumLeft2(vector<int> arr)
{
    int n = arr.size();
    vector<int> left(n,-1);

    int maxx = -1;
    for(int i=0; i<n; i++)
    {
        if(maxx == -1)
            maxx = i;

        else if(arr[maxx] > arr[i])
            left[i] = maxx;

        else
            maxx = i;
    }

    cout << "\nLeft Maximum = ";
    for(int i=0; i<n; i++)
        cout << left[i] << " ";
    return left;
}


vector<int> maximumRight2(vector<int> arr)
{
    int n = arr.size();
    vector<int> right(n,-1);

    int maxx = -1;
    for(int i=n-1; i>=0; i--)
    {
        if(maxx == -1)
            maxx = i;

        else if(arr[maxx] > arr[i])
            right[i] = maxx;

        else
            maxx = i;
    }

    cout << "\nRight Maximum = ";
    for(int i=0; i<n; i++)
        cout << right[i] << " ";
    return right;
}



int trap3(vector<int>& height)
{
    int trapped = 0, n = height.size();
    int left=0, right = n-1;
    int left_max = 0, right_max = 0;

    while(left < right)
    {

    }

    return trapped;
}
