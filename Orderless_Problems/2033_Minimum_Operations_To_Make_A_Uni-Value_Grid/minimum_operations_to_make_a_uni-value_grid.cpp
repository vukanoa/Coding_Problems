/*
    ==============
    === MEDIUM ===
    ==============

    =================================================
    2033) Minimum Operations to Make a Uni-Value Grid
    =================================================

    ============
    Description:
    ============

    You are given a 2D integer grid of size m x n and an integer x. In one
    operation, you can add x to or subtract x from any element in the grid.

    A uni-value grid is a grid where all the elements of it are equal.

    Return the minimum number of operations to make the grid uni-value. If it
    is not possible, return -1.

    ==============================================================
    FUNCTION: int minOperations(vector<vector<int>>& grid, int x);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,4],[6,8]], x = 2
    Output: 4
    Explanation: We can make every element equal to 4 by doing the following:
    - Add x to 2 once.
    - Subtract x from 6 once.
    - Subtract x from 8 twice.
    A total of 4 operations were used.

    --- Example 2 ---
    Input: grid = [[1,5],[2,3]], x = 1
    Output: 5
    Explanation: We can make every element equal to 3.

    --- Example 3 ---
    Input: grid = [[1,2],[3,4]], x = 2
    Output: -1
    Explanation: It is impossible to make every element equal.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    1 <= x, grid[i][j] <= 10^4

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive. Just sort it and find median. There's not much more to it.

*/

/* Time  Beats: 16.41% */
/* Space Beats: 34.95% */

/* Time  Complexity: O((N * M) * log(N * M)) */
/* Space Complexity: O(N * M)                */
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x)
    {
        const int N = grid.size();
        const int M = grid[0].size();

        int result = 0;

        vector<int> nums;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                nums.push_back(grid[i][j]);
            }
        }

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int R = nums.size() - 1;

        int mid = L + (R - L + 1) / 2; // upper-mid

        int target = nums[mid];

        for (int i = 0; i < nums.size(); i++)
        {
            if ((target - nums[i]) % x != 0)
                return -1;

            result += abs(target - nums[i]) / x;
        }

        return result;
    }
};
