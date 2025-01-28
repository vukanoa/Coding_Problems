/*
    ==============
    === MEDIUM ===
    ==============

    ======================================
    2658) Maximum Number of Fish in a Grid
    ======================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D matrix grid of size m x n, where (r, c)
    represents:

        + A land cell if grid[r][c] = 0, or
        + A water cell containing grid[r][c] fish, if grid[r][c] > 0.

    A fisher can start at any water cell (r, c) and can do the following
    operations any number of times:

        + Catch all the fish at cell (r, c), or
        + Move to any adjacent water cell.

    Return the maximum number of fish the fisher can catch if he chooses his
    starting cell optimally, or 0 if no water cell exists.

    An adjacent cell of the cell (r, c), is one of the cells (r, c + 1),
    (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.

    =====================================================
    FUNCTION: int findMaxFish(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
    Output: 7
    Explanation: The fisher can start at cell (1,3) and collect 3 fish,
                 then move to cell (2,3) and collect 4 fish.

    --- Example 2 ---
    Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,1]]
    Output: 1
    Explanation: The fisher can start at cells (0,0) or (3,3) and collect a
                 single fish.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    0 <= grid[i][j] <= 10

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Very, very, very ambiguous Description.

    Since they've told us this:

        A fisher can start at any water cell (r, c) and can do the following
        operations any number of times:

            + Catch all the fish at cell (r, c), or
            + Move to any adjacent water cell.

    and especially this:

        Return the maximum number of fish the fisher can catch if HE CHOOSES
        HIS STARTING CELL OPTIMALLY, or 0 if no water cell exists.


    One could think it is very important to choose starting cell wisely.
    However, that's not true. You can literally start at non-land cell.

    The problem is with the "OR" in their Description. "OR" indeed isn't
    exclusive, meaning it's not "either or", just "or", however it's still
    unclear whether we can take the fish from the current cell and move at the
    same time.

    But then if we get pass this, the question is - Can we move to ALL of 4
    directions?
    Or do we have to choose just one way, therefore "choose wisely", i.e.
    choose optimally.

    It turns out that NONE of this matters. You can literally start at any
    non-land you want and do the most basic DFS where you collect all the fish
    in each cell you encounter.

*/

/* Time  Beats: 66.73% */
/* Space Beats: 56.04% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int findMaxFish(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] > 0 && ! visited[row][col])
                    result = max(result, dfs(grid, visited, row, col));
            }
        }

        return result;
    }

private:
    int dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int row, int col)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return 0;

        if (grid[row][col] == 0 || visited[row][col])
            return 0;

        int curr_fish = grid[row][col];
        visited[row][col] = true;

        int up   =  dfs(grid, visited, row-1, col  );
        int down =  dfs(grid, visited, row+1, col  );
        int left =  dfs(grid, visited, row  , col-1);
        int right = dfs(grid, visited, row  , col+1);

        // visited[row][col] = false;

        return curr_fish + up + down + left + right;
    }
};
