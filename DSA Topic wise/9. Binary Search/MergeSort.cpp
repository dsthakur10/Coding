#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> mergeSort(vector<int>& arr, int low, int high);
vector<int> mergeArrays(vector<int> left, vector<int> right);

void mergeSort2(vector<int>& arr, int low, int high);
vector<int> mergeArrays2(vector<int>& arr, int low, int mid, int high);

int main()
{
    vector<int> nums = {38, 27, 43, 3, 100, 9, 82, -6};
    //vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
    //vector<int> nums = {38, 27};
    //vector<int> nums = {7};

    vector<int> result = mergeSort(nums, 0, nums.size()-1);
    for(int x : result)
        cout << x << " ";

    cout << "\n\n";
    mergeSort2(nums, 0, nums.size()-1);
    for(int x : nums)
        cout << x << " ";


}



vector<int> mergeSort(vector<int>& arr, int low, int high)
{
    if(low == high)
        return {arr[low]};

    int mid = (low+high)/2;

    vector<int> left = mergeSort(arr, low, mid);
    vector<int> right = mergeSort(arr, mid+1, high);

    vector<int> result = mergeArrays(left, right);

    return result;
}


vector<int> mergeArrays(vector<int> left, vector<int> right)
{
    int m = left.size();
    int n = right.size();

    vector<int> result(m+n);

    int i=0, j=0, k=0;

    while(i < m && j < n)
    {
        if(left[i] <= right[j])
        {
            result[k] = left[i];
            i++;
            k++;
        }

        else
        {
            result[k] = right[j];
            j++;
            k++;
        }
    }

    while(i < m)
    {
        result[k] = left[i];
        k++;
        i++;
    }

    while(j < n)
    {
        result[k] = right[j];
        j++;
        k++;
    }

    return result;
}




void mergeSort2(vector<int>& arr, int low, int high)
{
    if(low == high)
        return;

    int mid = low + (high-low)/2;

    mergeSort2(arr, low, mid);
    mergeSort2(arr, mid+1, high);

    mergeArrays2(arr, low, mid, high);
}


vector<int> mergeArrays2(vector<int>& arr, int low, int mid, int high)
{
    // mid is counted with left array

    int m = mid-low+1;
    int n = high-mid;

    vector<int> left(m);
    vector<int> right(n);

    for(int i=0; i<m; i++)
        left[i] = arr[low + i];

    for(int j=0; j<n; j++)
        right[j] = arr[mid+j+1];

    int i=0, j=0, k=low;

    while(i < m && j < n)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
            k++;
        }

        else
        {
            arr[k] = right[j];
            j++;
            k++;
        }
    }

    while(i < m)
    {
        arr[k] = left[i];
        k++;
        i++;
    }

    while(j < n)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}
