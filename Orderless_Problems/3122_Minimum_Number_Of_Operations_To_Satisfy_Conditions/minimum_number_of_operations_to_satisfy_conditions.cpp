/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3122) Minimum Number of Operations to Satisfy Conditions
    ========================================================

    ============
    Description:
    ============

    You are given a 2D matrix grid of size m x n. In one operation, you can
    change the value of any cell to any non-negative number. You need to
    perform some operations such that each cell grid[i][j] is:

        + Equal to the cell below it, i.e. grid[i][j] == grid[i+1][j]
          (if it exists).

        + Different from the cell to its right, i.e. grid[i][j] != grid[i][j+1]
          (if it exists).

    Return the minimum number of operations needed.

    ===========================================================
    FUNCTION: int minimumOperations(vector<vector<int>>& grid);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0,2],[1,0,2]]
    Output: 0

    --- Example 2 ---
    Input: grid = [[1,1,1],[0,0,0]]
    Output: 3

    --- Example 3 ---
    Input: grid = [[1],[2],[3]]
    Output: 2


    *** Constraints ***
    1 <= n, m <= 1000
    0 <= grid[i][j] <= 9

*/

#include <algorithm>
#include <climits>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Memoization. Constraints are "screaming" Memoization.

    Memoization Time Complexity is always:

        O(number_of_states * work_per_state)

    Our "number_of_states" is COLS * 11, and "work_per_state" is 10.

    Therefore, it's:

        O(COLS * 11 * 10)

    Since "COLS" is bound by 1000(i.e. 10^3), in total this would be:

        O(10^3 * 11 * 10) which is O(10^5)

    And we know that we can have up to 10^7 Time Complexity.


    In other words, if N = 10^7, we're allowed to have O(N) Time Complexity.
    If N = 10^5, we can even do O(N * logN).
    etc.

*/

/* Time  Beats: 63.72% */
/* Space Beats: 75.35% */

/* Time  Complexity: O(ROWS * COLS + COLS * 11 * 10) */
/* Space Complexity: O(COLS)                         */
class Solution {
private:
    int memo[1001][11];

public:
    int minimumOperations(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int MAX_VALID_ELEMENT = 9;

        memset(memo, -1, sizeof(memo));

        vector<vector<int>>count(COLS, vector<int>(10,0));

        for (int col = 0; col < COLS; col++)
        {
            for (int row = 0; row < ROWS; row++)
            {
                count[col][grid[row][col]]++;
            }
        }

        return solve(0, MAX_VALID_ELEMENT + 1, count, ROWS, COLS);
    }

private:
    int solve (int idx, int prev, vector<vector<int>>& count, const int& ROWS, const int& COLS)
    {
        if (idx >= COLS)
            return 0;

        if (memo[idx][prev] != -1)
            return memo[idx][prev];

        int min_change = INT_MAX;
        for (int elem = 0; elem <= 9; elem++)
        {
            if (elem != prev)
                min_change = min(min_change, ROWS - count[idx][elem] + solve(idx+1, elem, count, ROWS, COLS));
        }

        return memo[idx][prev] = min_change;
    }
};
