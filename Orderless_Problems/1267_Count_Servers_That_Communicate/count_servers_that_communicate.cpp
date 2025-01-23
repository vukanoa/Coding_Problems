/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1267) Count Servers that Communicate
    ====================================

    ============
    Description:
    ============

    You are given a map of a server center, represented as a m * n integer
    matrix grid, where 1 means that on that cell there is a server and 0 means
    that it is no server. Two servers are said to communicate if they are on
    the same row or on the same column.

    Return the number of servers that communicate with any other server.

    ======================================================
    FUNCTION: int countServers(vector<vector<int>>& grid);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0],[0,1]]
    Output: 0
    Explanation: No servers can communicate with others.

    --- Example 2 ---
    Input: grid = [[1,0],[1,1]]
    Output: 3
    Explanation: All three servers can communicate with at least one other
                 server.

    --- Example 3 ---
    Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
    Output: 4
    Explanation: The two servers in the first row can communicate with each
                 other. The two servers in the third column can communicate
                 with each other. The server at right bottom corner can't
                 communicate with any other server.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m <= 250
    1 <= n <= 250
    grid[i][j] == 0 or 1

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This seems weird to be marked as a MEDIUM problem. The Solution is using
    the common sense.

    First, go through every cell and mark its corresponding "row" in vector
    called "rows" that one additional server appears in that row specific row.

    Same for "col" in vector called "cols".

    Then iterate through every cell, again, in grid and for every server just
    check if that server is NOT the only one in its "row" and "col".

    If it's not the only one in its "row" or if it's not the only one in its
    "col", then that means it communicates with at least one other server,
    hence include it in "result", i.e. increment result.

    That's literally it.

*/

/* Time  Beats: 44.09% */
/* Space Beats: 59.58% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS + COLS) */
class Solution {
public:
    int countServers(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int result = 0;

        vector<int> rows(ROWS, 0);
        vector<int> cols(COLS, 0);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    rows[row]++;
                    cols[col]++;
                }
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1)
                {
                    if (rows[row] > 1 || cols[col] > 1)
                        result++;
                }
            }
        }

        return result;
    }
};
