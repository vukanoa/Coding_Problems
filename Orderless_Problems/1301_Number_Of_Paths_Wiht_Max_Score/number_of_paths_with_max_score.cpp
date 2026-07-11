/*
    ============
    === HARD ===
    ============

    ====================================
    1301) Number of Paths with Max Score
    ====================================

    ============
    Description:
    ============

    You are given a square board of characters. You can move on the board
    starting at the bottom right square marked with the character 'S'.

    You need to reach the top left square marked with the character 'E'. The
    rest of the squares are labeled either with a numeric character 1, 2, ...,
    9 or with an obstacle 'X'. In one move you can go up, left or up-left
    (diagonally) only if there is no obstacle there.

    Return a list of two integers: the first integer is the maximum sum of
    numeric characters you can collect, and the second is the number of such
    paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

    In case there is no path, return [0, 0].

    ===============================================================
    FUNCTION: vector<int> pathsWithMaxScore(vector<string>& board);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board = ["E23","2X2","12S"]
    Output: [7,1]

    --- Example 2 ---
    Input: board = ["E12","1X1","21S"]
    Output: [4,2]

    --- Example 3 ---
    Input: board = ["E11","XXX","11S"]
    Output: [0,0]


    *** Constraints ***
    2 <= board.length == board[i].length <= 100

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.93% */
/* Space Beats: 58.19% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board)
    {
        const int MOD = 1e9 + 7;

        const int ROWS = board.size();
        const int COLS = board[0].size();

        vector<vector<int>> max_score(ROWS, vector<int>(ROWS, -1));
        vector<vector<int>> path_ways(ROWS, vector<int>(ROWS, 0));

        max_score[ROWS - 1][ROWS - 1] = 0;
        path_ways[ROWS - 1][ROWS - 1] = 1;

        for (int row = ROWS-1; row >= 0; row--)
        {
            for (int col = COLS-1; col >= 0; col--)
            {
                if (board[row][col] == 'X')
                    continue;

                if (row == ROWS-1 && col == COLS-1)
                    continue;

                int best_score = -1;
                long long total_ways = 0;

                if (row + 1 < ROWS && max_score[row + 1][col] != -1)
                {
                    if (max_score[row + 1][col] > best_score)
                    {
                        best_score = max_score[row + 1][col];
                        total_ways =      path_ways[row + 1][col];
                    }
                    else if (max_score[row + 1][col] == best_score)
                    {
                        total_ways = (total_ways + path_ways[row + 1][col]) % MOD;
                    }
                }

                if (col+1 < COLS && max_score[row][col+1] != -1)
                {
                    if (max_score[row][col + 1] > best_score)
                    {
                        best_score = max_score[row][col + 1];
                        total_ways =      path_ways[row][col + 1];
                    }
                    else if (max_score[row][col + 1] == best_score)
                    {
                        total_ways = (total_ways + path_ways[row][col + 1]) % MOD;
                    }
                }

                if (row+1 < ROWS && col+1 < COLS && max_score[row + 1][col + 1] != -1)
                {
                    if (max_score[row+1][col+1] > best_score)
                    {
                        best_score = max_score[row + 1][col + 1];
                        total_ways =      path_ways[row + 1][col + 1];
                    }
                    else if (max_score[row+1][col+1] == best_score)
                    {
                        total_ways = (total_ways + path_ways[row+1][col+1]) % MOD;
                    }
                }

                if (best_score == -1)
                    continue;

                int curr = 0;
                if (board[row][col] >= '1' && board[row][col] <= '9')
                    curr = board[row][col] - '0';

                max_score[row][col] = best_score + curr;
                path_ways[row][col] = total_ways % MOD;
            }
        }

        if (max_score[0][0] == -1)
            return {0, 0};

        return {max_score[0][0], path_ways[0][0]};
    }
};
