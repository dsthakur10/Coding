/*

Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.

A falling path starts at any element in the first row and chooses the element in the next row that is either
directly below or diagonally left/right.
Specifically, the next element from position (row, col) will be
    (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1)

*/

// TOP-DOWN

int dp[101][101];
int minFallingPathSum(vector<vector<int>>& matrix) {

    memset(dp, -1, sizeof(dp));
    int n = matrix.size();
    int minSum = INT_MAX;

    for(int j=0; j<n; j++)
        minSum = min(minSum, solve(matrix, n-1, j));

    return minSum;
}

int solve(vector<vector<int>>& matrix, int m, int n)
{
    if(dp[m][n] != -1)
        return dp[m][n];

    if(m == 0)
        return matrix[m][n];

    int leftUp = INT_MAX, up = INT_MAX, rightUp = INT_MAX;
    up = solve(matrix, m-1, n);

    if(n == 0)
    {
        rightUp = solve(matrix, m-1, n+1);
    }

    else if(n == matrix.size() - 1)
    {
        leftUp = solve(matrix, m-1, n-1);
    }

    else
    {
        leftUp = solve(matrix, m-1, n-1);
        rightUp = solve(matrix, m-1, n+1);
    }

    int minimum = min(leftUp, rightUp);
    minimum = min(minimum, up);

    dp[m][n] = matrix[m][n] + minimum;

    return dp[m][n];
}


// Better TOP-DOWN (in terms of readability)

int dp[101][101];
int minFallingPathSum(vector<vector<int>>& matrix) {

    memset(dp, -1, sizeof(dp));
    int n = matrix.size();
    int minSum = INT_MAX;

    for(int j=0; j<n; j++)
        minSum = min(minSum, solve(matrix, n-1, j));

    return minSum;
}

int solve(vector<vector<int>>& matrix, int m, int n)
{
    if(n < 0 || n >= matrix.size())
        return INT_MAX;

    if(m == 0)
        return matrix[m][n];

    if(dp[m][n] != -1)
        return dp[m][n];

    int leftUp, up, rightUp;

    leftUp = solve(matrix, m-1, n-1);
    up = solve(matrix, m-1, n);
    rightUp = solve(matrix, m-1, n+1);

    int minimum = min(leftUp, rightUp);
    minimum = min(minimum, up);

    dp[m][n] = matrix[m][n] + minimum;

    return dp[m][n];
}


// BOTTOM - UP

int minFallingPathSum(vector<vector<int>>& matrix) {

    int minSum = INT_MAX;
    int n = matrix.size();
    int dp[n][n];

    for(int i = n-1; i>=0; i--)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == n-1)
                dp[i][j] = matrix[i][j];

            else if(j == 0)
                dp[i][j] = matrix[i][j] + min(dp[i+1][j], dp[i+1][j+1]);

            else if(j == n-1)
                dp[i][j] = matrix[i][j] + min(dp[i+1][j], dp[i+1][j-1]);

            else
                dp[i][j] = matrix[i][j] +
                            min({dp[i+1][j-1], dp[i+1][j+1], dp[i+1][j]});
        }
    }

    for(int j=0; j<n; j++)
        minSum = min(minSum, dp[0][j]);

    return minSum;
}
