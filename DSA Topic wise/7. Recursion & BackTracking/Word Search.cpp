
/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or
vertically neighboring. The same letter cell may not be used more than once.

Example 1:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]],
        word = "ABCCED"
Output: true

Example 2:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]],
        word = "SEE"
Output: true

Example 3:
Input: board = [["A","B","C","E"],
                ["S","F","C","S"],
                ["A","D","E","E"]],
        word = "ABCB"
Output: false

*/



// Logic is to keep traversing every cell in all 4 directions to get the given word.
// This is just hit & trial method.
// We start searching for required letters (consecutively that eventually forms the word) in given board.
// As soon as we first find the non-required word in the path, we backtrack to previous path in an attempt to find
// required word.
// False is returned in case every of the 4 direction of cell backtracks because of non-matching word

// We keep visited array to track if the cell has been traversed. If it is already traversed for current path,
// no need to traverse it again.


bool exist(vector<vector<char>>& board, string word) {

    int m = board.size(), n = board[0].size();
    vector<vector<int>> visited(m , vector<int> (n, 0));

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(!visited[i][j] && DFS(board, i, j, word, 0, visited))
                return true;
        }
    }
    return false;
}


bool DFS(vector<vector<char>>& board, int i, int j, string word, int index, vector<vector<int>>& visited)
{
    int k = word.size();

    int m = board.size(), n = board[0].size();

//         if(index == k)
//             return true;

    if(board[i][j] != word[index])          // 1st mismatch in the path & we backtracks with false value
        return false;

    if(board[i][j] == word[index] && index == k-1)      // index == k-1 --> word is found
        return true;

    visited[i][j] = 1;

    // checking boundary conditions
    if(i < m-1 && !visited[i+1][j] && DFS(board, i+1, j, word, index+1, visited))
        return true;

    if(i > 0 && !visited[i-1][j] && DFS(board, i-1, j, word, index+1, visited))
        return true;

    if(j < n-1 && !visited[i][j+1] && DFS(board, i, j+1, word, index+1, visited))
        return true;

    if(j > 0 && !visited[i][j-1] && DFS(board, i, j-1, word, index+1, visited))
        return true;

    visited[i][j] = 0;

    return false;
}



// Method-2 --> No Extra space

bool exist(vector<vector<char>>& board, string word) {

    int m = board.size(), n = board[0].size();

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(board[i][j] != '0' && DFS(board, i, j, word, 0))
                return true;
        }
    }
    return false;
}

bool DFS(vector<vector<char>>& board, int i, int j, string word, int index)
{
    int k = word.size();

    int m = board.size(), n = board[0].size();

//         if(index == k)
//             return true;

    if(board[i][j] != word[index])
        return false;

    if(board[i][j] == word[index] && index == k-1)
        return true;

    char ch = board[i][j];
    board[i][j] = '0';

    if(i < m-1 && board[i+1][j] != '0' && DFS(board, i+1, j, word, index+1))
        return true;

    if(i > 0 && board[i-1][j] != '0' && DFS(board, i-1, j, word, index+1))
        return true;

    if(j < n-1 && board[i][j+1] != '0' && DFS(board, i, j+1, word, index+1))
        return true;

    if(j > 0 && board[i][j-1] != '0' && DFS(board, i, j-1, word, index+1))
        return true;

    board[i][j] = ch;

    return false;
}


// Method-3 --> more readable code

bool exist(vector<vector<char>>& board, string word) {

    int m = board.size(), n = board[0].size();

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(board[i][j] != '0' && DFS(board, i, j, word, 0))
                return true;
        }
    }
    return false;
}

bool DFS(vector<vector<char>>& board, int i, int j, string word, int index)
{
    int k = word.size();

    int m = board.size(), n = board[0].size();

    if(i >= m || i < 0 || j >= n || j < 0)
        return false;

    if(board[i][j] != word[index])
        return false;

    if(board[i][j] == word[index] && index == k-1)
        return true;

    char ch = board[i][j];
    board[i][j] = '0';

    bool result =   DFS(board, i+1, j, word, index+1) ||
                    DFS(board, i-1, j, word, index+1) ||
                    DFS(board, i, j+1, word, index+1) ||
                    DFS(board, i, j-1, word, index+1);

    board[i][j] = ch;

    return result;
}
