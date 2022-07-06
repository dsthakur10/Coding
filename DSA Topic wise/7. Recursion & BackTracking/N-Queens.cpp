
/*

The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack
each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate
a queen and an empty space, respectively.

Example 1:
Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:
Input: n = 1
Output: [["Q"]]

Constraints:

1 <= n <= 9

*/



// LOGIC
/*
    Requirements :
        1. Every row must have exactly 1 Queen
        2. Every column must have exactly 1 Queen

    Consider placing queen column-wise.
    For a given column c, check for every row if it can be placed in this row.
        --> If YES, change the state of board & move onto NEXT column.
        --> If NO, return false & backtracks for some other way.
    We use a function isSafe() to check if queen can be placed in this cell.
    Store the answer when all the columns have been visited

    "isSafe()"
        --> We don't need to traverse every direction
        --> Our algorithm progresses in TOP->BOTTOM & LEFT->RIGHT manner.
        --> No need to check cells below & in the right of given cell --> Since they haven't yet traversed.

        We have 8 directions of which 4 are useless.
        1. Bottom
        2. Right
        3. Top-Right
        4. Bottom-Right

        5. Top
        --> Of the remaining 4, Top direction is also not needed. WHY ? --> If it had Queen, we would not have
            come down to current cell.

        Directions to check:
        6. Left
        7. Top-Left
        8. Bottom-Left
*/



// Method-1: isSafe() taking O(n) time in every iteration

// Storing chess board in the form of 2D vector of characters
vector<vector<string>> result;
vector<vector<char>> board;

vector<vector<string>> solveNQueens(int n) {

    board = vector<vector<char>> (n, vector<char> (n, '.'));
    solve(0, n);

    return result;
}


void solve(int col, int n)
{
    // every column has got 1 queen in safe position --> Store the current state of board as answer
    if(col == n)
    {
        // convert every row into string
        // convert all rows into string vector & push it in final result

        vector<string> output;
        for(int i=0; i<n; i++)
        {
            string str;
            for(char ch : board[i])
                str += ch;
            output.push_back(str);
        }

        result.push_back(output);
        return;
    }


    for(int row=0; row<n; row++)            // check every row in given column
    {
        if(isSafe(row, col, n))
        {
            board[row][col] = 'Q';
            solve(col+1, n);
            board[row][col] = '.';          // backtracks & restore the original state
        }
    }
}

bool isSafe(int row, int col, int n)
{
    // check for collision in only 3 directions --> left, top-left, bottom-left
    int r,c;

    // checking top-left
    r = row, c = col;
    while(r >= 0 && c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        r--;
        c--;
    }

    // checking left
    r = row, c = col;
    while(c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        c--;
    }

    // checking bottom-left
    r = row, c = col;
    while(r <= n-1 && c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        r++;
        c--;
    }

    return true;
}



// Storing chess board in the form of 1D vector of strings
vector<vector<string>> result;
vector<string> board;

vector<vector<string>> solveNQueens(int n) {

    board = vector<string>(n, string (n, '.'));
    solve(0, n);

    return result;
}


void solve(int col, int n)
{
    // every column has got 1 queen in safe position --> Store the current state of board as answer
    if(col == n)
    {
        result.push_back(board);
        return;
    }


    for(int row=0; row<n; row++)            // check every row in given column
    {
        if(isSafe(row, col, n))
        {
            board[row][col] = 'Q';
            solve(col+1, n);
            board[row][col] = '.';          // backtracks & restore the original state
        }
    }
}


// Time --> 3 * O(n)

bool isSafe(int row, int col, int n)
{
    // check for collision in only 3 directions --> left, top-left, bottom-left
    int r,c;

    // checking top-left
    r = row, c = col;
    while(r >= 0 && c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        r--;
        c--;
    }

    // checking left
    r = row, c = col;
    while(c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        c--;
    }

    // checking bottom-left
    r = row, c = col;
    while(r <= n-1 && c >= 0)
    {
        if(board[r][c] == 'Q')
            return false;

        r++;
        c--;
    }

    return true;
}



// Method-2 --> Using Hashing to increase the efficiency & solving safe cell in constant time

// We can check if any cell diagonally topLeft, diagonally bottom-left or horizontally left is covered earlier
// using hashing --> Take help of 3 separate arrays for this.
// Identify the pattern.

vector<vector<string>> result;
vector<string> board;
vector<int> topLeft, bottomLeft, left;


vector<vector<string>> solveNQueens(int n) {

    board = vector<string>(n, string (n, '.'));
    topLeft = vector<int>(2*n-1, 0);
    bottomLeft = vector<int>(2*n-1, 0);
    left = vector<int>(n, 0);

    solve(0, n);

    return result;
}


void solve(int col, int n)
{
    if(col == n)
    {
        result.push_back(board);
        return;
    }


    for(int row=0; row<n; row++)  // check every row in given column
    {
        if(left[row] == 0 && topLeft[row+col] == 0 && bottomLeft[n-1+col-row] == 0)
        {
            left[row] = 1;                          // marking the position of queen
            topLeft[row+col] = 1;
            bottomLeft[n-1+col-row] = 1;
            board[row][col] = 'Q';

            solve(col+1, n);

            board[row][col] = '.';                  // restore the original state after backtracking
            left[row] = 0;
            topLeft[row+col] = 0;
            bottomLeft[n-1+col-row] = 0;
        }
    }
}
