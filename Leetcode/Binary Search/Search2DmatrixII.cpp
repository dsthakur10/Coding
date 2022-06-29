
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



// Method-2 --> O(m+n)

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
