
/*

Given an m x n board of characters and a list of strings words, return all words on the board.

Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally
or vertically neighboring. The same letter cell may not be used more than once in a word.

Example 1:
Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
Output: ["eat","oath"]

Example 2:
Input: board = [["a","b"],["c","d"]], words = ["abcb"]
Output: []

*/


// Method-1 --> Find all the words one by one --> TLE

int DIR[5] = {1, 0, -1, 0, 1};

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {

    vector<string> result;
    int m = board.size(), n = board[0].size();
    //vector<vector<int>> visit;
    bool found;

    for(string str : words)
    {
        found = false;
        //visit = vector<vector<int>> (m, vector<int> (n, 0));
        vector<vector<int>> visit(m, vector<int> (n, 0));

        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(DFS(board, visit, i, j, str, 0))
                {
                    result.push_back(str);
                    found = true;
                    break;
                }
            }

            if(found)
                break;
        }
    }

    return result;
}

bool DFS(vector<vector<char>>& board, vector<vector<int>>& visit,
         int row, int col, string word, int index)
{
    int m = board.size(), n = board[0].size();
    visit[row][col] = 1;

    if(index == word.size()-1 && board[row][col] == word[index])
        return true;

    if(board[row][col] == word[index])
    {
        for(int k=0; k<4; k++)
        {
            int r = row + DIR[k];
            int c = col + DIR[k+1];

            if(r >= 0 && c >= 0 && r < m && c < n && !visit[r][c] &&
               DFS(board, visit, r, c, word, index+1))
                return true;
        }
    }

    visit[row][col] = 0;
    return false;
}



// Method-2
