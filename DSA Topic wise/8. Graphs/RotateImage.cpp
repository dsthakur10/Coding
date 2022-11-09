/*
You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).

You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
DO NOT allocate another 2D matrix and do the rotation.

Example 1:

Input: [[1,2,3],
        [4,5,6],
        [7,8,9]]

Output:[[7,4,1],
        [8,5,2],
        [9,6,3]]

Example 2:

Input: [[5,1,9,11],
        [2,4,8,10],
        [13,3,6,7],
        [15,14,12,16]]

Output:[[15,13,2,5],
        [14,3,4,1],
        [12,6,8,9],
        [16,7,10,11]]

*/


// Rotate 90 degree Clockwise: Transpose the matrix --> reverse each row of matrix

void rotate(vector<vector<int>>& matrix) {

    int n = matrix.size();

    // transpose
    for(int i=0; i<n; i++)
    {
        for(int j=i; j<n; j++)
            swap(matrix[i][j], matrix[j][i]);
    }

    // reverse each row
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n/2; j++)
            swap(matrix[i][j], matrix[i][n-1-j]);
    }
}
