/*

Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.

Example 1:
Input: board = [["5","3",".",".","7",".",".",".","."],
                ["6",".",".","1","9","5",".",".","."],
                [".","9","8",".",".",".",".","6","."],
                ["8",".",".",".","6",".",".",".","3"],
                ["4",".",".","8",".","3",".",".","1"],
                ["7",".",".",".","2",".",".",".","6"],
                [".","6",".",".",".",".","2","8","."],
                [".",".",".","4","1","9",".",".","5"],
                [".",".",".",".","8",".",".","7","9"]]

Output:board = [["5","3","4","6","7","8","9","1","2"],
                ["6","7","2","1","9","5","3","4","8"],
                ["1","9","8","3","4","2","5","6","7"],
                ["8","5","9","7","6","1","4","2","3"],
                ["4","2","6","8","5","3","7","9","1"],
                ["7","1","3","9","2","4","8","5","6"],
                ["9","6","1","5","3","7","2","8","4"],
                ["2","8","7","4","1","9","6","3","5"],
                ["3","4","5","2","8","6","1","7","9"]]

Constraints:

board.length == 9
board[i].length == 9
board[i][j] is a digit or '.'

NOTE: It is guaranteed that the INPUT BOARD HAS ONLY ONE SOLUTION.

*/



// Method-1 -->

void solveSudoku(vector<vector<char>>& board) {

    solve(board);
}

bool solve(vector<vector<char>>& board)
{
    for(int i=0; i<9; i++)
    {
        for(int j=0; j<9; j++)
        {
            if(board[i][j] == '.')
            {
                for(char ch = '1'; ch <= '9'; ch++)
                {
                    if(isValid(board, ch, i, j))
                    {
                        board[i][j] = ch;

                        if(solve(board))        // found 1st solution --> return
                            return true;

                        board[i][j] = '.';      // restore original state
                    }

                }

                return false;               // no choice --> collision everywhere, return false & backtracks
            }
        }
    }
    return true;        // no empty place found. Sudoku is already solved
}


bool isValid(vector<vector<char>>& board, char ch, int row, int col)
{
    for(int i = 0; i < 9; i++)
    {
        if(board[row][i] == ch)     // check row
            return false;

        if(board[i][col] == ch)     // check column
            return false;

        int x = (3 * (row/3)) + i/3;
        int y = (3 * (col/3)) + i%3;

        if(board[x][y] == ch)       // check submatrix
            return false;
    }

    return true;
}
