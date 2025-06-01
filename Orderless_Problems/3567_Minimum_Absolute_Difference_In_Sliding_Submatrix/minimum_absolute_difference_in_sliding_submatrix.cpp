/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    3567) Minimum Absolute Difference in Sliding Submatrix
    ======================================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid and an integer k.

    For every contiguous k x k submatrix of grid, compute the minimum absolute
    difference between any two distinct values within that submatrix.

    Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is
    the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.

    =====
    Note: If all elements in the submatrix have the same value, the answer will
          be 0. A submatrix (x1, y1, x2, y2) is a matrix that is formed by
          choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2
    =====

    ===========================================================================
    FUNCTION: vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,8],[3,-2]], k = 2
    Output: [[2]]
    Explanation:
        There is only one possible k x k submatrix: [[1, 8], [3, -2]].
        Distinct values in the submatrix are [1, 8, 3, -2].
        The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus,
        the answer is [[2]].


    --- Example 2 ---
    Input: grid = [[3,-1]], k = 1
    Output: [[0,0]]
    Explanation:
        Both k x k submatrix has only one distinct element.
        Thus, the answer is [[0, 0]].


    --- Example 3 ---
    Input: grid = [[1,-2,3],[2,3,5]], k = 2
    Output: [[1,2]]
    Explanation:
        There are two possible k × k submatrix:
            Starting at (0, 0): [[1, -2], [2, 3]].
                Distinct values in the submatrix are [1, -2, 2, 3].
                The minimum absolute difference in the submatrix is |1 - 2| = 1.
            Starting at (0, 1): [[-2, 3], [3, 5]].
                Distinct values in the submatrix are [-2, 3, 5].
                The minimum absolute difference in the submatrix is |3 - 5| = 2.
        Thus, the answer is [[1, 2]].


    *** Constraints ***
    1 <= m == grid.length <= 30
    1 <= n == grid[i].length <= 30
    -10^5 <= grid[i][j] <= 10^5
    1 <= k <= min(m, n)

*/

#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Brute-Force.

*/

/* Time  Beats: 25.33% */
/* Space Beats:  5.55% */

/* Time  Complexity: O((ROWS − k + 1) * (COLS − k + 1) * k^2 * logk) */
/* Space Complexity: O((ROWS − k + 1) * (COLS − k + 1) * k^2)        */
class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int ANS_ROWS = grid.size()    - k + 1;
        const int ANS_COLS = grid[0].size() - k + 1;

        vector<vector<int>> answer(ANS_ROWS, vector<int>(ANS_COLS, 0));

        if (k == 1)
            return answer;

        for (int row = 0; row < ANS_ROWS; row++)
        {
            for (int col = 0; col < ANS_COLS; col++)
            {
                vector<int> magic;
                for (int i = row; i < row + k; i++)
                {
                    for (int j = col; j < col + k; j++)
                    {
                        magic.push_back(grid[i][j]);
                    }
                }

                unordered_set<int> uset(magic.begin(), magic.end());
                vector<int> tmp(uset.begin(), uset.end());

                /* Sort */
                magic = tmp;
                sort(magic.begin(), magic.end());

                int diff = abs(magic[1] - magic[0]);

                for (int x = 2; x < magic.size(); x++)
                    diff = min(diff, abs(magic[x] - magic[x-1]));

                answer[row][col] = diff;
            }
        }

        return answer;
    }
};
