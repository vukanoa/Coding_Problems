/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3418) Maximum Amount of Money Robot Can Earn
    ============================================

    ============
    Description:
    ============

    You are given an m x n grid. A robot starts at the top-left corner of the
    grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1). The
    robot can move either right or down at any point in time.

    The grid contains a value coins[i][j] in each cell:

        + If coins[i][j] >= 0, the robot gains that many coins.
        + If coins[i][j] < 0, the robot encounters a robber, and the robber
          steals the absolute value of coins[i][j] coins.

    The robot has a special ability to neutralize robbers in at most 2 cells on
    its path, preventing them from stealing coins in those cells.

    Note: The robot's total coins can be negative.

    Return the maximum profit the robot can gain on the route.

    ========================================================
    FUNCTION: int maximumAmount(vector<vector<int>>& coins);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]
    Output: 8
    Explanation:
    An optimal path for maximum coins is:
        Start at (0, 0) with 0 coins (total coins = 0).
        Move to (0, 1), gaining 1 coin (total coins = 0 + 1 = 1).
        Move to (1, 1), where there's a robber stealing 2 coins. The robot uses one neutralization here, avoiding the robbery (total coins = 1).
        Move to (1, 2), gaining 3 coins (total coins = 1 + 3 = 4).
        Move to (2, 2), gaining 4 coins (total coins = 4 + 4 = 8).


    --- Example 2 ---
    Input: coins = [[10,10,10],[10,10,10]]
    Output: 40
    Explanation:
    An optimal path for maximum coins is:
        Start at (0, 0) with 10 coins (total coins = 10).
        Move to (0, 1), gaining 10 coins (total coins = 10 + 10 = 20).
        Move to (0, 2), gaining another 10 coins (total coins = 20 + 10 = 30).
        Move to (1, 2), gaining the final 10 coins (total coins = 30 + 10 = 40)


    *** Constraints ***
    m == coins.length
    n == coins[i].length
    1 <= m, n <= 500
    -1000 <= coins[i][j] <= 1000

*/

#include <climits>
#include <cstdlib>
#include <vector>
using namespace std;

/*

     [[0,1,-1],[1,-2,3],[2,-3,4]]


    +-----+-----+-----+
    |  0  |  1  | -1  |
    +-----+-----+-----+
    |  1  | -2  |  3  |
    +-----+-----+-----+
    |  2  | -3  |  4  |
    +-----+-----+-----+


    +---------+---------+---------+
    |  0 - -  |  1 - -  |  - 1 -  |
    +---------+---------+---------+
    |  1 - -  |  - 1 -  |  - 4 -  |
    +---------+---------+---------+
    |  3 - -  |  - 3 1  |  - 8 5  |
    +---------+---------+---------+

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.71% */
/* Space Beats:  5.10% */

/* Time  Complexity: O(3 * ROWS * COLS) */
/* Space Complexity: O(3 * ROWS * COLS) */
class Solution_2 {
public:
    int maximumAmount(vector<vector<int>>& coins)
    {
        const int ROWS = coins.size();
        const int COLS = coins[0].size();
        const int STATES = 3;

        vector<vector<vector<int>>> dp(ROWS, vector<vector<int>>(COLS, vector<int>(3, INT_MIN)));

        for (int count = 0; count < STATES; count++)
        {
            for (int row = ROWS-1; row >= 0; row--)
            {
                for (int col = COLS-1; col >= 0; col--)
                {
                    if (row == ROWS-1 && col == COLS-1)
                    {
                        dp[row][col][count] = count > 0 ? max(0, coins[row][col]) : coins[row][col];
                        continue;
                    }

                    int max_profit = INT_MIN;

                    if (row+1 < ROWS)
                    {
                        max_profit = max(max_profit, coins[row][col] + dp[row+1][col][count]);

                        if (count > 0)
                            max_profit = max(max_profit, dp[row+1][col][count-1]);
                    }

                    if (col+1 < COLS)
                    {
                        max_profit = max(max_profit, coins[row][col] + dp[row][col+1][count]);

                        if (count > 0)
                            max_profit = max(max_profit, dp[row][col+1][count-1]);
                    }

                    dp[row][col][count] = max_profit;
                }
            }
        }

        return dp[0][0][2];
    }
};
