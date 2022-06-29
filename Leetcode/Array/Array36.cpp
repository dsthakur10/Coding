// Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

// 1. Each row must contain the digits 1-9 without repetition.
// 2. Each column must contain the digits 1-9 without repetition.
// 3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

// NOTE: A Sudoku board (partially filled) could be valid but is not necessarily solvable.
//       Only the filled cells need to be validated according to the mentioned rules.

// Constraints:

// board.length == 9    |   board[i].length == 9    |   board[i][j] is a digit or '.'
// 9 sub-boxes each of size = 9


#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>


bool solution1(std::vector<std::vector<char>>& board);          // 3*O(n^2) - checking row, column & sub-box separately

bool solution2(std::vector<std::vector<char>>& board);          // 2*O(n^2) - checking row & column simultaneously

bool solution3(std::vector<std::vector<char>>& board);          // O(n^2) - checking all 3 simultaneously


int main()
{
    std::vector<std::vector<char>> sudoku1 =
    {    {'5','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','1','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}  };

    std::vector<std::vector<char>> sudoku2 =
    {    {'5','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','6','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}  };

    std::vector<std::vector<char>> sudoku3 =
    {    {'5','3','.','.','7','.','.','.','.'}
        ,{'6','.','.','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','5','9','.','.','5'}
        ,{'.','.','.','.','8','.','.','7','9'}  };

    std::vector<std::vector<char>> sudoku4 =
    {    {'5','3','.','.','7','.','.','.','.'}
        ,{'6','.','5','1','9','5','.','.','.'}
        ,{'.','9','8','.','.','.','.','6','.'}
        ,{'8','.','.','.','6','.','.','.','3'}
        ,{'4','.','.','8','.','3','.','.','1'}
        ,{'7','.','.','.','2','.','.','.','6'}
        ,{'.','6','.','.','.','.','2','8','.'}
        ,{'.','.','.','4','1','9','.','.','5'}
        ,{'.','.','.','.','8','.','8','7','9'}  };


    for(int i=0;i<sudoku3.size();i++)
    {
        for(int j=0;j<sudoku3[i].size();j++)
            std::cout<<sudoku3[i][j]<<"  ";

        std::cout<<"\n";
    }
    std::cout<<"\n----------------------------\n";

    bool valid = solution2(sudoku3);
    std::cout<<"\n\n\nThis sudoku is "<<std::boolalpha<<valid;

}

bool solution1(std::vector<std::vector<char>>& board)
{
    std::vector<int> counter(9,0);
    int x;

    for(int i=0;i<board.size();i++)                                     // checking duplicate in same row
    {
        for(int j=0;j<board[i].size();j++)
        {
            if(board[i][j] == '.')
                continue;

            x = (int)board[i][j] - 48;
            //std::cout<<x<<" ";

            counter[x-1]++;

            if(counter[x-1]==2)
                return false;
        }

        std::cout<<"\nrow["<<i<<"] = ";
        for(int num:counter)
            std::cout<<num<<" ";

        counter.assign(9,0);
    }

    std::cout<<"\n----------------------------\n";


    for(int i=0;i<board.size();i++)                                     // checking duplicate in same column
    {
        for(int j=0;j<board[i].size();j++)
        {
            if(board[j][i] == '.')
                continue;

            x = (int)board[j][i] - 48;
            //std::cout<<x<<" ";

            counter[x-1]++;

            if(counter[x-1]==2)
                return false;
        }

        std::cout<<"\ncolumn["<<i<<"] = ";
        for(int num:counter)
            std::cout<<num<<" ";

        counter.assign(9,0);
    }


    int iIndex=0,jIndex,countt;                                         // checking duplicate in same sub-box
    while(iIndex<9)
    {
        countt = 0;
        jIndex = 0;

        while(countt < 3)
        {
            //std::cout<<"\n\n";
            counter.assign(9,0);
            for(int i=iIndex; i<iIndex+3 ; i++)
            {
                for(int j=jIndex; j<jIndex+3; j++)
                {
                    if(board[i][j] == '.')
                        continue;

                    x = (int)board[i][j] - 48;
                    //std::cout<<x<<" ";

                    counter[x-1]++;

                    if(counter[x-1]==2)
                    {
                        std::cout<<"\n\nError is at index = "<<i<<j;
                        return false;
                    }


                    //std::cout<<board[i][j]<<"  ";
                }
                //std::cout<<"\n";
            }
            jIndex += 3;
            countt++;
        }

        iIndex += 3;
    }

    return true;
}



bool solution2(std::vector<std::vector<char>>& board)
{
    std::vector<int> row(9,0);
    std::vector<int> column(9,0);
    int x;

    for(int i=0;i<board.size();i++)                                     // checking duplicate in same row & column
    {
        for(int j=0;j<board[i].size();j++)
        {
            if(board[i][j] != '.')
            {
                x = (int)board[i][j] - 48;

                row[x-1]++;
                if(row[x-1]==2)
                    return false;
            }


            if(board[j][i] != '.')
            {
                x = (int)board[j][i] - 48;

                column[x-1]++;
                if(column[x-1]==2)
                    return false;
            }

        }

        std::cout<<"\nrow["<<i<<"] = ";
        for(int num:row)
            std::cout<<num<<" ";

        std::cout<<"\ncolumn["<<i<<"] = ";
        for(int num:column)
            std::cout<<num<<" ";

        row.assign(9,0);
        column.assign(9,0);
    }


    int iIndex=0,jIndex,countt;                                         // checking duplicate in same sub-box
    while(iIndex<9)
    {
        countt = 0;
        jIndex = 0;

        while(countt < 3)
        {
            //std::cout<<"\n\n";
            row.assign(9,0);
            for(int i=iIndex; i<iIndex+3 ; i++)
            {
                for(int j=jIndex; j<jIndex+3; j++)
                {
                    if(board[i][j] == '.')
                        continue;

                    x = (int)board[i][j] - 48;
                    //std::cout<<x<<" ";

                    row[x-1]++;

                    if(row[x-1]==2)
                    {
                        std::cout<<"\n\nError is at index = "<<i<<j;
                        return false;
                    }


                    //std::cout<<board[i][j]<<"  ";
                }
                //std::cout<<"\n";
            }
            jIndex += 3;
            countt++;

        }

        iIndex += 3;
    }

    return true;
}



bool solution3(std::vector<std::vector<char>>& board)
{


}
