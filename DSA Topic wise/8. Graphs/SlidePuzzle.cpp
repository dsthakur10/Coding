/*

On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0.
A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given the puzzle board board, return the least number of moves required so that the state of the board is solved.
If it is impossible for the state of the board to be solved, return -1.

Example 1:
Input: board = [[1,2,3],
                [4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.


Example 2:
Input: board = [[1,2,3],
                [5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.


Example 3:
Input: board = [[4,1,2],
                [5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]


Constraints:

board.length == 2
board[i].length == 3
0 <= board[i][j] <= 5
Each value board[i][j] is unique.

*/


// Logic
// First identify type of node in the graph --> Each state of board can be considered as separate node in graph.
// The most easy way to represent the state of board is via string.
// Target Node = "123450" | startNode = given state of board
// You have to find minimum #steps needed to move from startNode to TargetNode --> BFS/Dijkstra
// Since weight is not a concern here, we can simply go for BFS.
// 6 different numbers & therefore possible states = 6! = 720. But there is no need to create every state(node)
// of graph beforeHand.
// Dynamically prepare the node & store them in HashSet/HashMap as visited node so that if we ever bump into this
// same node again, we do not traverse it & continue with next nodes in queue.
// Keep track of levels & as soon as target node is found, return current level.
// If target Node is never met--> queue will be empty -> return -1

int slidingPuzzle(vector<vector<int>>& board) {

    // Premeditated Directions for each index of board (string)
    vector<vector<int>> DIR = {{1,3}, {0,2,4}, {1,5}, {0,4}, {1,3,5}, {2,4}};
    unordered_map<string, bool> mp;
    queue<string> q;

    string targetNode = "123450";
    string startNode;
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<3; j++)
            startNode += to_string(board[i][j]);
    }

    mp[startNode] = true;
    q.push(startNode);
    int ans = 0;

    while(!q.empty())
    {
        int n = q.size();
        ans++;
        while(n > 0)
        {
            string cur = q.front();
            q.pop();
            n--;

            if(cur == targetNode)
                return ans-1;

            int index = cur.find('0');

            // pushing all possible states that can be reached from current state after swapping 0 & its neighbor
            for(int x : DIR[index])
            {
                string str = cur;
                swap(str[index], str[x]);

                // if the node is not already visited, only then push it into queue & HashMap/HashSet
                if(mp.find(str) == mp.end())
                {
                    mp[str] = true;
                    q.push(str);
                }
            }
        }
    }

    return -1;
}
