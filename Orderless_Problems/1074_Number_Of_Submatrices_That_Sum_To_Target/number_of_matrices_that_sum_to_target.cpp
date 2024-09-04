#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    ============================================
    1074) Number of Matrices That Sum To Target
    ============================================

    ============
    Description:
    ============

    Given a matrix and a target, return the number of non-empty submatrices
    that sum to target.

    A submatrix x1, y1, x2, y2 is the set of all cells matrix[x][y] with x1 <=
    x <= x2 and y1 <= y <= y2.

    Two submatrices (x1, y1, x2, y2) and (x1', y1', x2', y2') are different if
    they have some coordinate that is different: for example, if x1 != x1'.

    =============================================================================
    FUNCTION: int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
    Output: 4
    Explanation: The four 1x1 submatrices that only contain 0.

    --- Example 2 ---
    Input: matrix = [[1,-1],[-1,1]], target = 0
    Output: 5
    Explanation: The two 1x2 submatrices, plus the two 2x1 submatrices, plus
                 the 2x2 submatrix.

    --- Example 3 ---
    Input: matrix = [[904]], target = 0
    Output: 0


    *** Constraints ***
    1 <= matrix.length <= 100
    1 <= matrix[0].length <= 100
    -1000 <= matrix[i][j] <= 1000
    -10^8 <= target <= 10^8

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.01% */
/* Space Beats: 50.85% */

/* Time  Complexity: O(ROWS * COLS^2) */
/* Space Complexity: O(ROWS)          */
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target)
    {
        const int ROWS = matrix.size();
        const int COLS = matrix[0].size();

        for (auto& row : matrix)
        {
            for (int col = 1; col < COLS; col++)
                row[col] += row[col-1];
        }

        int sum_cnt = 0;

        for (int left = 0; left < COLS; left++)
        {
            for (int right = left; right < COLS; right++)
            {
                int curr_pref_sum = 0;

                unordered_map<int, int> sum_freq;
                sum_freq[0]++;

                for (int r = 0; r < ROWS; r++)
                {
                    int pref_sum_curr_row = matrix[r][right] - ((left-1 > -1) ? matrix[r][left - 1] : 0);

                    curr_pref_sum += pref_sum_curr_row;

                    if (sum_freq.count(curr_pref_sum-target))
                        sum_cnt += sum_freq[curr_pref_sum - target];

                    sum_freq[curr_pref_sum]++;
                }
            }
        }

        return sum_cnt;
    }
};
