/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1536) Minimum Swaps to Arrange a Binary Grid
    ============================================

    ============
    Description:
    ============

    Given an n x n binary grid, in one step you can choose two adjacent rows of
    the grid and swap them.

    A grid is said to be valid if all the cells above the main diagonal are
    zeros.

    Return the minimum number of steps needed to make the grid valid, or -1 if
    the grid cannot be valid.

    The main diagonal of a grid is the diagonal that starts at cell (1, 1) and
    ends at cell (n, n).

    ==================================================
    FUNCTION: int minSwaps(vector<vector<int>>& grid);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,0,1],[1,1,0],[1,0,0]]
    Output: 3

    --- Example 2 ---
    Input: grid = [[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
    Output: -1
    Explanation: All rows are similar, swaps have no effect on the grid.

    --- Example 3 ---
    Input: grid = [[1,0,0],[1,1,0],[1,1,1]]
    Output: 0


    *** Constraints ***
    n == grid.length == grid[i].length
    1 <= n <= 200
    grid[i][j] is either 0 or 1

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 23.97% */
/* Space Beats: 81.36% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid)
    {
        const int N = grid.size();
        unordered_set<int> uset;

        vector<int> zeroes;

        for (int row = 0; row < N; row++)
        {
            int count = 0; // Consectuive 0s from the right
            for (int col = N-1; col >= 0; col--)
            {
                if (grid[row][col] == 1)
                    break;

                count++;
            }

            while (uset.count(count))
                count--;

            if (count >= 0)
            {
                uset.insert(count);
                zeroes.push_back(count);
            }
        }

        if (uset.size() < N)
            return -1;


        int inversions = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (zeroes[i] < zeroes[j])
                    inversions++;
            }
        }

        return inversions;
    }
};
