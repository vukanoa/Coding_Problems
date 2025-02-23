/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3462) Maxium Sum With at Most K Elements
    ========================================

    ============
    Description:
    ============

    You are given a 2D integer matrix grid of size n x m, an integer array
    limits of length n, and an integer k. The task is to find the maximum sum
    of at most k elements from the matrix grid such that:

        The number of elements taken from the ith row of grid does not exceed
        limits[i].

    Return the maximum sum.

    ==================================================================================
    FUNCTION: long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k);
    ==================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
    Output: 7
    Explanation:
        From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
        The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.


    --- Example 2 ---
    Input: grid = [[5,3,7],[8,2,6]], limits = [2,2], k = 3
    Output: 21
    Explanation:
        From the first row, we can take at most 2 elements. The element taken is 7.
        From the second row, we can take at most 2 elements. The elements taken are 8 and 6.
        The maximum possible sum of at most 3 selected elements is 7 + 8 + 6 = 21.


    *** Constraints ***
    n == grid.length == limits.length
    m == grid[i].length
    1 <= n, m <= 500
    0 <= grid[i][j] <= 10^5
    0 <= limits[i] <= m
    0 <= k <= min(n * m, sum(limits))

*/

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Try to forget to code and ask yourself:"How would I determine what is the
    result if I'm doing it manually with only my eyes and hands?"

    And then you'll realize this is the most straight-forward solution.
    Simply sort each row and take top limits[i] elements from each row and put
    it in a vector "max_elements", from where we'll take min(total_limit, k)
    elements and we'll simply add those min_total_limit, k) elements up.

    That's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.74% */

/* Time  Complexity: O(N * logN + M * logM) */
/* Space Complexity: O(N)                   */
class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        long long result = 0;

        int total_limit = accumulate(limits.begin(), limits.end(), 0);

        vector<int> max_elements;
        for (int row = 0; row < ROWS; row++)
        {
            sort(grid[row].begin(), grid[row].end());

            for (int x = 0; x < limits[row]; x++)
            {
                max_elements.push_back(grid[row][COLS-1 - x]);
            }
        }

        sort(max_elements.begin(), max_elements.end(), greater<int>());

        int total = min(total_limit, k);
        for (size_t i = 0; i < total; i++)
            result += max_elements[i];;

        return result;
    }
};
