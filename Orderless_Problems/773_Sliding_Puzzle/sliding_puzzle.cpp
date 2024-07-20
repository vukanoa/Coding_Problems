#include <iostream>
#include <vector>
#include <stack>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ===========================
    774) Sliding Puzzle
    ===========================

    ============
    Description:
    ============

    On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty
    square represented by 0. A move consists of choosing 0 and a
    4-directionally adjacent number and swapping it.

    The state of the board is solved if and only if the board is
    [[1,2,3],[4,5,0]].

    Given the puzzle board board, return the least number of moves required so
    that the state of the board is solved. If it is impossible for the state of
    the board to be solved, return -1.

    =======================================================
    FUNCTION int slidingPuzzle(vector<vector<int>>& board);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    Input: board = [[1,2,3],[4,0,5]]
    Output: 1
    Explanation: Swap the 0 and the 5 in one move.


    --- Example 2 ---
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+
    |     |     |     |
    +-----+-----+-----+

    Input: board = [[1,2,3],[5,4,0]]
    Output: -1
    Explanation: No number of moves will make the board solved.


    --- Example 3 ---
    Input: board = [[4,1,2],[5,0,3]]
    Output: 5
    Explanation: 5 is the smallest number of moves that solves the board.
    An example path:
    After move 0: [[4,1,2],[5,0,3]]
    After move 1: [[4,1,2],[0,5,3]]
    After move 2: [[0,1,2],[4,5,3]]
    After move 3: [[1,0,2],[4,5,3]]
    After move 4: [[1,2,0],[4,5,3]]
    After move 5: [[1,2,3],[4,5,0]]

    *** Constraints ***
    board.length == 2
    board[i].length == 3
    0 <= board[i][j] <= 5
    Each value board[i][j] is unique.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.72% */
/* Space Beats: 43.86% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board)
    {
        string target = "123450";
        string s      = "";

        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 3; j++)
                s += to_string(board[i][j]);
        }

        set<string> stack;
        queue<pair<string,int>> queue;
        queue.push({s,0});

        while(!queue.empty())
        {
            string t     = queue.front().first;
            int    steps = queue.front().second;
            queue.pop();

            stack.insert(t);

            if (t == target)
                return steps;

            int index = -1;
            for (int i = 0; i < t.size(); i++)
            {
                if (t[i] == '0')
                {
                    index = i;
                    break;
                }
            }

            // Up
            if (index-3 >= 0)
            {
                string tmp = t;
                swap(tmp[index],tmp[index-3]);

                if(stack.find(tmp) == stack.end())
                    queue.push({tmp,steps+1});
            }

            // Down
            if(index+3 <= 5)
            {
                string tmp = t;
                swap(tmp[index],tmp[index+3]);

                if(stack.find(tmp) == stack.end())
                    queue.push({tmp, steps+1});
            }

            // Right
            if (index != 2 && index != 5)
            {
                string tmp = t;
                swap(tmp[index],tmp[index+1]);

                if(stack.find(tmp) == stack.end())
                    queue.push({tmp,steps+1});
            }

            // Left
            if(index != 0 && index != 3)
            {
                string tmp = t;
                swap(tmp[index],tmp[index-1]);

                if(stack.find(tmp) == stack.end())
                    queue.push({tmp,steps+1});
            }
        }

        return -1;
    }
};
