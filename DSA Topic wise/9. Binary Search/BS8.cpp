// Count Negative Numbers in a Sorted Matrix

/*

Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise,
return the number of negative numbers in grid.

Example 1:
Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
Output: 8
Explanation: There are 8 negatives number in the matrix.

Example 2:
Input: grid = [[3,2],[1,0]]
Output: 0

*/


// O(m+n) solution --> Start from TOP-RIGHT corner
// If at certain cell, value < 0 --> all the cells below this cell will have < 0 --> add all of them

int countNegatives(vector<vector<int>>& grid) {

    int counter = 0;
    int m = grid.size(), n = grid[0].size();
    int row = 0, col = n-1;

    while(row <= m-1 && col >=0)
    {
        if(grid[row][col] < 0)
        {
            counter += (m - 1) - row + 1;
            col--;
        }

        else
            row++;
    }

    return counter;
}
