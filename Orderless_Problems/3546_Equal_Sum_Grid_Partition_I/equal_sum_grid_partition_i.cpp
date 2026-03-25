/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3546) Equal Sum Grid Partition I
    ================================

    ============
    Description:
    ============

    You are given an m x n matrix grid of positive integers. Your task is to
    determine if it is possible to make either one horizontal or one vertical
    cut on the grid such that:

        + Each of the two resulting sections formed by the cut is non-empty.

        + The sum of the elements in both sections is equal.

    Return true if such a partition exists; otherwise return false.

    ===========================================================
    FUNCTION: bool canPartitionGrid(vector<vector<int>>& grid);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    nput: grid = [[1,4],[2,3]]
    Output: true
    Explanation:
    A horizontal cut between row 0 and row 1 results in two non-empty sections,
    each with a sum of 5. Thus, the answer is true.

    --- Example 2 ---
    Input: grid = [[1,3],[2,4]]
    Output: false
    Explanation:
    No horizontal or vertical cut results in two non-empty sections with equal
    sums. Thus, the answer is false.


    *** Constraints ***
    1 <= m == grid.length <= 10^5
    1 <= n == grid[i].length <= 10^5
    2 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 45.68% */
/* Space Beats: 99.28% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(1)           */
class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        long long total_sum = 0;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
                total_sum += grid[row][col];
        }

        long long prefix = 0;

        /* Horizontal cuts */
        for (int row = 0; row < ROWS-1; row++)
        {
            for (int col = 0; col < COLS; col++)
                prefix += grid[row][col];

            if (prefix == total_sum - prefix)
                return true;
        }

        prefix = 0; // Reset

        /* Vertical cuts */
        for (int col = 0; col < COLS-1; col++)
        {
            for (int row = 0; row < ROWS; row++)
                prefix += grid[row][col];

            if (prefix == total_sum - prefix)
                return true;
        }

        return false;
    }
};
