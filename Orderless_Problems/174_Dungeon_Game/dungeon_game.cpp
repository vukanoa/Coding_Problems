/*
    ============
    === HARD ===
    ============

    ===========================
    174) Dungeon Game
    ===========================

    ============
    Description:
    ============

    The demons had captured the princess and imprisoned her in the bottom-right
    corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D
    grid. Our valiant knight was initially positioned in the top-left room and
    must fight his way through dungeon to rescue the princess.

    The knight has an initial health point represented by a positive integer.
    If at any point his health point drops to 0 or below, he dies immediately.

    Some of the rooms are guarded by demons (represented by negative integers),
    so the knight loses health upon entering these rooms; other rooms are
    either empty (represented as 0) or contain magic orbs that increase the
    knight's health (represented by positive integers).

    To reach the princess as quickly as possible, the knight decides to move
    only rightward or downward in each step.

    Return the knight's minimum initial health so that he can rescue the
    princess.

    Note that any room can contain threats or power-ups, even the first room
    the knight enters and the bottom-right room where the princess is
    imprisoned.

    ===============================================================
    FUNCTION: int calculateMinimumHP(vector<vector<int>>& dungeon); 
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    +-----+-----+-----+
    | -2 => -3 => 3\  |
    +-----+-----+--v--+
    | -5  | -10 |  1  |
    +-----+-----+-----+
    |  10 |  30 | -5  |
    +-----+-----+-----+

    Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
    Output: 7
    Explanation: The initial health of the knight must be at least 7 if he
    follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.


    --- Example 2 ---
    Input: dungeon = [[0]]
    Output: 1


    *** Constraints ***
    m == dungeon.length
    n == dungeon[i].length
    1 <= m, n <= 200
    -1000 <= dungeon[i][j] <= 1000

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.51% */
/* Space Beats: 92.75% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Memoization {
public:
    int ROWS;
    int COLS;
    int dp[201][201];

    int calculateMinimumHP(vector<vector<int>>& dungeon)
    {
        ROWS = dungeon.size();
        COLS = dungeon[0].size();

        memset(dp, -1, sizeof(dp));

        return dfs(0, 0, dungeon);
    }

private:
    int dfs(int i, int j, vector<vector<int>> &dungeon)
    {
        if (i >= ROWS || j >= COLS)
             return 1e9;

        if (i == ROWS-1 && j == COLS-1)
            return dungeon[i][j] > 0 ? 1 : 1 - dungeon[i][j];

        if(dp[i][j] != -1)
            return dp[i][j];

        int down  = dfs(i+1, j  , dungeon);
        int right = dfs(i  , j+1, dungeon);

        int result = std::min(down, right) - dungeon[i][j];

        return dp[i][j] = result > 0 ? result : 1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.41% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Bottom_Up {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon)
    {
        int ROWS = dungeon.size();
        int COLS = dungeon[0].size();

        vector<vector<int> > dp(ROWS+1, vector<int>(COLS+1, 1e9));
        dp[ROWS  ][COLS-1] = 1;
        dp[ROWS-1][COLS  ] = 1;

        for (int i = ROWS-1; i >= 0; i--) 
        {
            for (int j = COLS-1; j >= 0; j--) 
            {
                int need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];                

                // Store this value
                dp[i][j] = need <= 0 ? 1 : need;
            }
        }

        return dp[0][0];
    }
};
