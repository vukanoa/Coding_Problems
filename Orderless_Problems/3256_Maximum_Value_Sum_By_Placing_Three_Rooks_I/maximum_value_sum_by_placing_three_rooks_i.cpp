/*
    ============
    === HARD ===
    ============

    ================================================
    3256) Maximum Value Sum by Placing Three Rooks I
    ================================================

    ============
    Description:
    ============

    You are given a m x n 2D array board representing a chessboard, where
    board[i][j] represents the value of the cell (i, j).

    Rooks in the same row or column attack each other. You need to place three
    rooks on the chessboard such that the rooks do not attack each other.

    Return the maximum sum of the cell values on which the rooks are placed.

    ================================================================
    FUNCTION: long long maximumValueSum(vector<vector<int>>& board);
    ================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: board = [[-3,1,1,1],[-3,1,-3,1],[-3,2,1,1]]
    Output: 4
    Explanation: We can place the rooks in the cells (0, 2), (1, 3), and (2, 1)
                 for a sum of 1 + 1 + 2 = 4.

    --- Example 2 ---
    Input: board = [[1,2,3],[4,5,6],[7,8,9]]
    Output: 15
    Explanation: We can place the rooks in the cells (0, 0), (1, 1), and (2, 2)
                 for a sum of 1 + 5 + 9 = 15.

    --- Example 3 ---
    Input: board = [[1,1,1],[1,1,1],[1,1,1]]
    Output: 3
    Explanation: We can place the rooks in the cells (0, 2), (1, 1), and (2, 0)
                 for a sum of 1 + 1 + 1 = 3.


    *** Constraints ***
    3 <= m == board.length <= 100
    3 <= n == board[i].length <= 100
    -10^9 <= board[i][j] <= 10^9

*/

#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Complexity: O(N * 3 * 3 * 3) --> O(N) */
/* Space Complexity: O(N * 3 * 3 * 3) --> O(N) */

/* Time  Beats: 33.06% */
/* Space Beats: 25.62% */
class Solution {
public:
    long long memo[101][102][102][3];

    long long maximumValueSum(vector<vector<int>>& board)
    {
        int ROWS = board.size();
        int COLS = board[0].size();

        memset(memo, -1, sizeof(memo));

        vector<vector<pair<int,int>>> nums(ROWS);
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < board[0].size(); j++)
                nums[i].push_back( {board[i][j], j} );

            sort(nums[i].rbegin(), nums[i].rend());

            while (nums[i].size() > 3)
                nums[i].pop_back();
        }

        return max_value_dfs(nums, 0, -1, -1, 0);
    }

private:
    long long max_value_dfs(vector<vector<pair<int,int>>>& nums, int idx, int col1, int col2, int k)
    {
        if (idx >= nums.size() || k >= 3)
            return k == 3 ? 0 : -1e18;

        if (memo[idx][col1+1][col2+1][k] != -1)
            return memo[idx][col1+1][col2+1][k];

        long long result = -1e18;
        for (int i = 0; i < nums[idx].size(); i++)
        {
            for (auto &it : nums[idx])
            {
                if (idx == 0 || (it.second != col1 && it.second != col2))
                    result = max(result, 1ll * it.first + max_value_dfs(nums, idx+1, it.second, col1, k+1));
            }
        }

        result = max(result, max_value_dfs(nums, idx+1, col1, col2, k));
        return memo[idx][col1+1][col2+1][k] = result;
    }
};
