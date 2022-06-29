// Search in 2D matrix

/*
Given an mxn 2D matrix & target value.

Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.

Return true if target is found.

Input: matrix =[[1,3,5,7],
                [10,11,16,20],
                [23,30,34,60]], target = 3
Output: true

*/



// Method-1 --> O(mlogn) in worst case

bool binarySearch(vector<int> row, int target){

    int low=0, high = row.size()-1;
    int mid;

    while(low <= high)
    {
        mid = (low+high)/2;

        if(row[mid] == target)
            return true;

        else if(row[mid] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return false;
}



bool searchMatrix(vector<vector<int>>& matrix, int target) {

    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    int m = matrix.size();
    int n = matrix[0].size();

    if(target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;

    for(int i=0; i<m; i++)
    {
        if(target >= matrix[i][0] && target <= matrix[i][n-1])
            return binarySearch(matrix[i], target);

    }

    return false;
}



// Method-2 --> O(log(m*n))

// Treat a 2D array as single sorted list & perform binary search over whole 2D array from index(0) to index(m*n-1)

/*
    1. row_num * col_num might cause overflow.

    2. / and % are expensive operations.

*/

bool searchMatrix2(vector<vector<int>>& matrix, int target) {

    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    int m = matrix.size();
    int n = matrix[0].size();

    if(target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;

    int low = 0, high = m*n - 1;
    int mid;

    while(low <= high)
    {
        //mid = (low+high)/2;
        mid = low + (high-low)/2;           // to avoid overflow

        int i = mid / n;
        int j = mid % n;

        if(matrix[i][j] == target)
            return true;

        else if(matrix[i][j] < target)
            low = mid+1;

        else
            high = mid-1;
    }

    return false;
}



// Method-3 --> 2 binary search --> O(logm) + O(logn) == O(logmn)

// 1st binary search to get the probable row which can have our target variable.    --> O(logm)
// 2nd binary search to get the target in this row                                  --> O(logn)


bool searchMatrix3(vector<vector<int>>& matrix, int target)
{
    int m = matrix.size();
    int n = matrix[0].size();

    if(target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;

    // search row
    int row;
    int low = 0, high = m-1;

    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(matrix[mid][0] <= target && matrix[mid][n-1] >= target)
        {
            row = mid;
            break;
        }

        else if(matrix[mid][0] > target)
            high = mid-1;

        else if(matrix[mid][n-1] < target)
            low = mid+1;
    }

    // search column
    low = 0, high = n-1;
    while(low <= high)
    {
        int mid = low + (high-low)/2;

        if(matrix[row][mid] == target)
            return true;

        else if(matrix[row][mid] > target)
            high = mid-1;

        else if(matrix[row][mid] < target)
            low = mid+1;
    }

    return false;
}
