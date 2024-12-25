/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3393) Count Paths With the Given XOR Value
    ==========================================

    ============
    Description:
    ============

    You are given a 2D integer array grid with size m x n. You are also given
    an integer k.

    Your task is to calculate the number of paths you can take from the
    top-left cell (0, 0) to the bottom-right cell (m - 1, n - 1) satisfying the
    following constraints:

    You can either move to the right or down. Formally, from the cell (i, j)
    you may move to the cell (i, j + 1) or to the cell (i + 1, j) if the target
    cell exists. The XOR of all the numbers on the path must be equal to k.

    Return the total number of such paths.

    Since the answer can be very large, return the result modulo 109 + 7.

    =======================================================================
    FUNCTION: int countPathsWithXorValue(vector<vector<int>>& grid, int k);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2, 1, 5], [7, 10, 0], [12, 6, 4]], k = 11
    Output: 3
    Explanation: 
    The 3 paths are:
        (0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2)
        (0, 0) → (1, 0) → (1, 1) → (1, 2) → (2, 2)
        (0, 0) → (0, 1) → (1, 1) → (2, 1) → (2, 2)

    --- Example 2 ---
    Input: grid = [[1, 3, 3, 3], [0, 3, 3, 2], [3, 0, 1, 1]], k = 2
    Output: 5
    Explanation:
    The 5 paths are:
        (0, 0) → (1, 0) → (2, 0) → (2, 1) → (2, 2) → (2, 3)
        (0, 0) → (1, 0) → (1, 1) → (2, 1) → (2, 2) → (2, 3)
        (0, 0) → (1, 0) → (1, 1) → (1, 2) → (1, 3) → (2, 3)
        (0, 0) → (0, 1) → (1, 1) → (1, 2) → (2, 2) → (2, 3)
        (0, 0) → (0, 1) → (0, 2) → (1, 2) → (2, 2) → (2, 3)


    --- Example 3 ---
    Input: grid = [[1, 1, 1, 2], [3, 0, 3, 2], [3, 0, 2, 2]], k = 10
    Output: 0


    *** Constraints ***
    1 <= m == grid.length <= 300
    1 <= n == grid[r].length <= 300
    0 <= grid[r][c] < 16
    0 <= k < 16

*/

#include <vector>
using namespace std;


class Solution_TLE {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int MOD = 1e9 + 7;

        int result = 0;
        dfs(grid, k, 0, 0, result, 0);

        return result % MOD;
    }

private:
    void dfs(vector<vector<int>>& grid, int k, int row, int col, int& result, int curr_xor)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row == ROWS || col == COLS)
            return;

        if (row == ROWS-1 && col == COLS-1)
        {
            if ((curr_xor ^ grid[row][col]) == k)
                result++;

            return;
        }

        dfs(grid, k, row  , col+1, result, curr_xor ^ grid[row][col]); // Right
        dfs(grid, k, row+1, col  , result, curr_xor ^ grid[row][col]); // Down
    }
};


/*
    ------------
    --- IDEA ---
    ------------

    If you've done a 2D Problem called "Unique Paths" from "Blind 75", you'd
    quickly realize that counting ways isn't doing the trick for this one.

    So what do we do?

    We are doing a 3D Dynamic Programming.

    Since nums[i] can be [0, 15], and since the operations is XOR, that means
    we will NEVER(!!!) go out of those bounds. No matter how many times you're
    XOR-ing them, it will never be a number greater than 15 or lower than 0.

    Therefore, we'll do a 2D DP with a vector of 16 elements for each value.

    What will each element in the vector represents, in each cell?

    For example in cell dp[1][2], we have this:

        {0, 0, 1, 0, 0, 0, 3, 0, 0, 0, ... 0}
         0  1  2  3  4  5  6  7  8  9     15

    It's important to knwo what is the VALUE of grid[1][2]. Let's say it was 4.

    What does, then, each number represents in this 16-sized vector?

    It represents the number of ways we could END UP in that cell (row=1, col=2
    in our case) so that the total XOR-ed path is X.

    This is clumsily worded, let me try again - dp[1][2][6] == 3
    So what is 3 here?

    3 is the NUMBER OF WAYS we could come to this very cell (row=1, col=2)
    where total XOR-ed values is equal to 6.

    Read that again.






*/

/* Time  Beats: 100.00% */
/* Space Beats:  50.00% */

/* Time  Complexity: O(M * N * 16) */
/* Space Complexity: O(M * N * 16) */
class Solution_3D_DP {
public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int MOD = 1e9 + 7;

        int max_xor = 16;

        // 3D DP array initialized with 0
        vector<vector<vector<int>>> dp(ROWS, vector<vector<int>>(COLS, vector<int>(max_xor, 0)));

        // Base case
        dp[0][0][grid[0][0]] = 1;

        // Populate the DP table
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                for (int x_or = 0; x_or < max_xor; ++x_or)
                {
                    if (row > 0)
                    {
                        dp[row][col][x_or] += dp[row - 1][col][x_or ^ grid[row][col]];
                        dp[row][col][x_or] %= MOD;
                    }

                    if (col > 0)
                    {
                        dp[row][col][x_or] += dp[row][col - 1][x_or ^ grid[row][col]];
                        dp[row][col][x_or] %= MOD;
                    }
                }
            }
        }

        // The result is the number of paths ending at the bottom-right corner with XOR value k
        return dp[ROWS - 1][COLS - 1][k] % MOD;
    }
};
