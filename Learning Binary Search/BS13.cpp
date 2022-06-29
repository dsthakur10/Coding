// Search a 2D Matrix II

/*
Given an mxn 2D matrix & target value.

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

Return true if target is found.

Input: matrix = [[1,4,7,11,15],
                 [2,5,8,12,19],
                 [3,6,9,16,22],
                 [10,13,14,17,24],
                 [18,21,23,26,30]], target = 5
Output: true

*/

// m --> rows
// n --> columns



// Method-1     --> O(mlogn)

bool binarySearch(vector<int> row, int target)
{
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
        bool answer = false;

        if(target >= matrix[i][0] && target <= matrix[i][n-1])
            answer = binarySearch(matrix[i], target);

        if(answer)
            return true;
    }

    return false;

}



// Method-2 --> O(m+n)  --> Start the search from TOP-RIGHT
/*

We start the search from top-right corner matrix[0][n-1] --> 0th row | n-1th column

1. If target found, return true

2. Else If target > matrix[0][n-1], increment row since if target > last element of row,
    target will also be > ALL elements in that row --> delete this row

3. Else If target < matrix[0][n-1], decrement column since if target < first element of column,
    target will also be < All elements in that column --> delete this column

Search space will reduce from m+n to m+n-1 to m+n-2 to ....
*/


bool searchMatrix2(vector<vector<int>>& matrix, int target) {

    if (matrix.size() == 0 || matrix[0].size() == 0)
        return false;

    int m = matrix.size();
    int n = matrix[0].size();

    if(target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;

    int row = 0, column = n-1;

    while(row <= m-1 && column >= 0)
    {
        if(matrix[row][column] == target)
            return true;

        else if(matrix[row][column] < target)
            row++;

        else
            column--;
    }


    return false;
}


// Method-3 --> O(m+n)  --> Start the search from BOTTOM-LEFT

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();

    if(target < matrix[0][0] || target > matrix[m-1][n-1])
        return false;

    int row = m-1, col = 0;

    while(row >= 0 && col <=n-1)
    {
        if(target == matrix[row][col])
            return true;

        else if(target < matrix[row][col])
            row--;

        else
            col++;
    }

    return false;
}
